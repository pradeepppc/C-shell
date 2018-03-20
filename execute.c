#include "os.h"
#ifndef __VAR345__
#define __VAR345__
   
    bgcom *head=NULL;
#endif
void pri()
{
    int flag,status;
     bgcom *tmp2,*tmp;
     tmp2=head;
    while(tmp2!=NULL)
    {
        flag=0;


        if(waitpid(tmp2->pid,&status,WNOHANG))
        {
            printf("%s with pid %ld exited normally\n",tmp2->name,tmp2->pid);
            tmp=head;
            while(((tmp->nxt)!=tmp2) && ((tmp->nxt)!=NULL) && (tmp!=tmp2)) 
            {
                tmp=tmp->nxt;
            }
            if(tmp==tmp2 && tmp2->nxt==NULL)
            {
                head=tmp2->nxt;
                flag=2;
                tmp2=tmp2->nxt;
                free(tmp);

            }
            else if(tmp==tmp2)
            {
                flag=2;

                head=tmp2->nxt;
                tmp2=tmp2->nxt;
                free(tmp);
            }
            else if((tmp->nxt)==tmp2)
            {
                tmp->nxt=tmp2->nxt;
                flag=1;
            }
            if(flag==1)
            {

                free(tmp2);
                tmp2=tmp->nxt;
            }
            //         }
        }
        if(flag==0)
            tmp2=tmp2->nxt;
    }

}

int id;
char temp[1024];
void sig_bg(int sig)
{
    bgcom *tmp,*tmp2;
    tmp2=head;
    if(tmp2!=NULL)
    {
        while(tmp2->nxt!=NULL)
        {
            tmp2=tmp2->nxt;
        }
    }
    tmp=malloc(sizeof(bgcom));
    strcpy(tmp->name,temp);
    tmp->pid=id;
    tmp->type=1;
    if(head==NULL)
    {
        tmp->nxt=NULL;
        head=tmp;

    }
    else
    {
        tmp2->nxt=tmp;
        tmp->nxt=NULL;
    }

    printf("\n");
    signal(SIGTSTP,SIG_IGN);
    return;
}
int execute(char *a,char *CWD,char *PWD)
{
    int i;
    i=0;
    int count,len,flag,pos,status;
    int eid=0;
    int dfg,ef;
    dfg=0;
    flag=0;
    strcpy(temp,a);
    char *array[1000];
    char *seperate;
    bgcom *tmp,*tmp2;
    flag=0;
    id=strlen(a);
    for(i=0;i<id;i++)
    {
        if(a[i]=='|')
        {
            pipecmd(a,CWD,PWD);
            dfg=2;
            break;
        }
    }
    if(dfg==2)
    {
        return 0;
    }

    for(i=0;i<id;i++)
    {
        if(a[i]=='<'||a[i]=='>')
        {
            redir(a,CWD,PWD,0,0,0);
            dfg=1;
            break;
        }
    }
    if(dfg==1)
        return 0;
    seperate=strtok(a," ");
    i=0;
    signal(SIGTSTP,sig_bg);
    while(seperate!=NULL)
    {
        array[i]=seperate;
        if((array[i][strlen(array[i])-1]=='&') || (strcmp(array[i],"&")==0))
        {
            if(array[i][strlen(array[i])-1]=='&' && (strcmp(array[i],"&")!=0))
            {
                array[i][strlen(array[i])-1]='\0';
                i++;
            }
            flag=1;
            break;
        }
        i++;
        seperate=strtok(NULL," ");
    }
    tmp2=head;
    if(tmp2!=NULL)
    {
        while((tmp2->nxt)!=NULL)
            tmp2=tmp2->nxt;
    }

    count=i;
    if(count>0)
        strcpy(temp,array[0]);
    for(i=1;i<count;i++)
    {
        strcat(temp," ");
        strcat(temp,array[i]);
    }

    if(flag==1)
    {
        tmp=malloc(sizeof(bgcom));
        if(count>0)
        {
            strcpy(tmp->name,array[0]);
            for(i=1;i<count;i++)
            {
                strcat(tmp->name," ");
                strcat(tmp->name,array[i]);
            }
        }
        tmp->type=0;
     //   tmp->stop="Running"

    }
    array[i]=NULL;
    if(count==0)
        return 1;
    if(strcmp(array[0],"pwd")==0)
    {
        //exec_pwd(array,count,flag);
        char CCC[1000];
        getcwd(CCC,sizeof(CCC));
        printf("%s\n",CCC);
    }
    else if(!strcmp(array[0],"setenv") || !strcmp(array[0],"unsetenv"))
    {
        var_env(count,array);
    }
    else if(strcmp(array[0],"cd")==0)
    {
       // exec_cd(array,count,startdir,lastdir,flag);
        if(array[1]=='\0')
           chdir(CWD);
        else if(!strcmp(array[1],"~"))
        {
            chdir(CWD);
        }
        else
        {
            int o=chdir(array[1]);
            if(o!=0)
            printf("stderr:%sDirectory does not exist\n",array[1]);
        }
                                
    }
    else if(!strcmp(array[0],"echo"))
    {
       // exec_echo(temp,count,array,startdir,flag);
        echo(array);
        printf("\n");
    }
    else if(strcmp(array[0],"pinfo")==0)
    {
       // pinfo(startdir,array);
       if(array[1]=='\0')
       {
            int ff=getpid();
            char xx[1000];
            sprintf(xx,"%d",ff);
            pinf(xx);
       }
       else
             pinf(array[1]); 
    }
    else if(strcmp(array[0],"quit")==0 && count==1)
    {
        int pid=getpid();
            kill(pid,SIGKILL);
            exit(0);

    }
    else if(strcmp(array[0],"jobs")==0)
    {
        eid=1;
        tmp2=head;
        while(tmp2!=NULL)
        {   if(tmp2->type==0)
                printf("[%d] Running %s [%ld]\n",eid,tmp2->name,tmp2->pid);
            else
                printf("[%d] Stopped %s [%ld]\n",eid,tmp2->name,tmp2->pid);
            eid++;
            tmp2=tmp2->nxt;
        }
    }
    else if(strcmp(array[0],"overkill")==0)
    {
        eid=0;
        tmp2=head;
        while(tmp2!=NULL)
        {
            tmp=tmp2;
            head=tmp2->nxt;
            tmp2=tmp2->nxt;
            kill(tmp->pid,SIGKILL);
            free(tmp);

        }
    }
    else if(strcmp(array[0],"fg")==0)
    {
        if(count<2)
        {
            fprintf(stderr,"invalid input\n");
            return 0;
        }
        eid=0;
        ef=0;
        id=strlen(array[1]);
        for(ef=0;ef<id;ef++)
        {
            eid=eid*10+(array[1][ef]-'0');
        }
        tmp2=head;
        ef=1;
        while(tmp2!=NULL)
        {
            if(eid==ef)
                break;
            tmp2=tmp2->nxt;
            ef++;
        }
        if(tmp2!=NULL)
        {
           // printf("%d\n",tmp2->type);
            if(tmp2->type==0)
                waitpid(tmp2->pid,&status,0);
            else
            {
                kill(tmp2->pid,SIGCONT);
                waitpid(tmp2->pid,&status,0);
                //             waitpid(tmp2->pid,&status,0);
            }
        }

        else
            perror("invalid input");

    }

    else if(!strcmp(array[0],"bg"))
    {
         if(count<2)
        {
            fprintf(stderr,"invalid input\n");
            return 0;
        }
        eid=0;
        ef=0;
        id=strlen(array[1]);
        for(ef=0;ef<id;ef++)
        {
            eid=eid*10+(array[1][ef]-'0');
        }
        tmp2=head;
        ef=1;
        while(tmp2!=NULL)
        {
            if(eid==ef)
                break;
            tmp2=tmp2->nxt;
            ef++;
        }
        if(tmp2!=NULL)
        {
            if(tmp2->type!=0)
            {
                tmp2->type=0;
                kill(tmp2->pid,SIGCONT);
            }
        }

    }
    else if(strcmp(array[0],"kjob")==0)
    {
        if(count==3)
        {

            eid=0;
            ef=0;
            id=strlen(array[1]);
            for(ef=0;ef<id;ef++)
            {
                eid=eid*10+(array[1][ef]-'0');
            }
            tmp2=head;
            ef=1;
            while(tmp2!=NULL)
            {
                if(eid==ef)
                    break;
                tmp2=tmp2->nxt;
                ef++;
            }
            if(tmp2!=NULL)
            {
                eid=0;
                id=strlen(array[2]);
                for(ef=0;ef<id;ef++)
                {
                    eid=eid*10+(array[2][ef]-'0');
                }

                if(kill(tmp2->pid,eid)==-1)
                    fprintf(stderr,"invalid input\n");
            }

            else
                fprintf(stderr,"invalid input\n");

        }
        else
            fprintf(stderr,"invalid input\n");
    }

    else if(count>0)
    {

        if((id=fork())<0)
            perror("error while forking");
        else if(id==0)
        {
            if(execvp(*array,array)<0)
            {
                perror("ERROR in exec function");
                exit(0);
            }

        }
        else if(flag==0)
            waitpid(id,&status,WUNTRACED);
        else if(flag==1)
        {
            tmp->pid=id;
            if(head==NULL)
            {
                tmp->nxt=NULL;
                head=tmp;

            }
            else
            {
                tmp2->nxt=tmp;
                tmp->nxt=NULL;
            }

        }

    }
    return 1;
}