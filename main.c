#include "os.h"


int flag2;
void sig_br(int sig)
{
    signal(SIGTSTP,SIG_IGN);
  //  printf("\n");
    return;
}

void sighand(int sig)
{
    flag2=1;
    switch(sig)
    {
        case SIGINT:
            printf("\n");
            fflush(stdout);
            break;
    }
    return;
}

int main()
{
		register struct passwd *pw;
		register uid_t uid;
		uid = geteuid ();
		pw = getpwuid (uid); //get username
		struct utsname uts;
		int k=uname(&uts);  //for getting sysname
		char CWD[10000];
		getcwd(CWD,sizeof(CWD));



		int i;
		while(1)
		{
				pri();
				char a[10000];
				char *PWD;
				PWD=dir(CWD);
				printf("<%s@%s:%s>",pw->pw_name,uts.sysname,PWD); //command prompt
				signal(SIGTSTP,sig_br);
      			signal(SIGINT,sighand);
				fgets(a,10000,stdin);

				a[strlen(a)-1]='\0';
				if(a[0]!='\0')
				{
					char *ww[10000];
					int i=0;
					ww[i]=strtok(a,";");    //tokenising with ;
					while(ww[i]!=NULL)
					{
						i++;
						ww[i]=strtok(NULL,";");        
					}
					int j=0;
					for(j=0;j<i;j++)
					{

						execute(ww[j],CWD,PWD);
					}
				}
					
		}
		return 0;
}
