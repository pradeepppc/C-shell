#include "os.h"


//ls with all types

void ls(char **aa,int i)
{
		char CWD[10000];
		getcwd(CWD,sizeof(CWD));
		int flag;
		if(i==1)
		{
				flag=0;
		}
		else if(i==2)
		{
				if(!strcmp(aa[1],"\0"))
						flag=0;
				else if(!strcmp(aa[1],"-a"))
						flag=1;
				else if(!strcmp(aa[1],"-l"))
						flag=2;
				else if(!strcmp(aa[1],"-al")||!strcmp(aa[1],"-la"))
						flag=3;
				else
				{
						int yy=chdir(aa[1]);
						if(yy!=0)
						{
								printf("This directory does not exist\n");
								return;
						}
						else
								flag=0;
				}
		}
		else if(i==3)
		{
				if(!strcmp(aa[2],"-a")||!strcmp(aa[2],"-l"))
						flag=3;
				else
				{
						int yy=chdir(aa[2]);
						if(yy!=0)
						{
								printf("This directory does not exist\n");
								return;
						}
						else
						{
								if(!strcmp(aa[1],"-a"))
										flag=1;
								else if(!strcmp(aa[1],"-l"))
										flag=2;
								else
										flag=3;
						}
				}
		}
		else
		{
				int yy=chdir(aa[3]);
				if(yy!=0)
				{
						printf("This directory does not exist\n");
						return;
				}

				else
						flag=3;
		}


		char PWD[10000];
		getcwd(PWD,sizeof(PWD));


		DIR *mydir;
		struct dirent *myfile;
		struct stat mystat;

		char buf[512];
		mydir=opendir(PWD);
		int sum=0;
		while((myfile=readdir(mydir))!=NULL)
		{
				if(!((flag==2 && myfile->d_name[0]=='.')))
				{
						struct stat filestat;
						stat(myfile->d_name,&filestat);
						double hh= (filestat.st_size/1024.00);
						long int dd=filestat.st_size/1024;
						if(dd%4==0)
						{
								if(dd<hh)
										sum+=dd+4;
								else
										sum+=dd;
						}
						else
						{
								sum+=dd+(4-dd%4);
						}}
		}
		closedir(mydir);
		if(flag==2 || flag==3)
				printf("total %d\n",sum);

		mydir = opendir(PWD);
		while((myfile = readdir(mydir)) != NULL)
		{
				stat(buf, &mystat);
				struct stat attr;
				stat(myfile->d_name, &attr);
				char *aa;
				aa=ctime(&attr.st_mtime);
				char *pp[5];
				int oo=0;
				pp[oo]=strtok(aa," ");
				while(pp[oo]!=NULL)
				{
						oo++;
						pp[oo]=strtok(NULL," ");
				}


				struct stat fileStat;
				stat(myfile->d_name,&fileStat);
				struct passwd *p;
				struct group *g;
				p=getpwuid(fileStat.st_uid);
				g=getgrgid(fileStat.st_gid);
				if(flag==2 ||flag==3)
				{


						if(!((flag==2) && (myfile->d_name[0]=='.')))
						{
								printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
								printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
								printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
								printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
								printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
								printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
								printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
								printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
								printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
								printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
								printf("  %lu",fileStat.st_nlink);
								printf("  %s  ",p->pw_name);
								printf("%s",g->gr_name);
								printf("  %ld",fileStat.st_size);
								printf("\t%s  %s  %s",pp[1],pp[2],pp[3]);
						}
				}
				if(flag==0 || flag==2)
				{
						if(myfile->d_name[0]!='.')
						{
								if(S_ISDIR(fileStat.st_mode))
										printf("\x1b[34m  %s\x1b[0m\n",myfile->d_name);
								else if(fileStat.st_mode & S_IXUSR)
										printf("\x1b[32m  %s\x1b[0m\n",myfile->d_name);
								else
										printf("  %s\n",myfile->d_name);

								//	printf("  %s \n", myfile->d_name);
						}
				}
				else
				{
						if(S_ISDIR(fileStat.st_mode))
								printf("\x1b[34m  %s\x1b[0m\n",myfile->d_name);
						else if(fileStat.st_mode & S_IXUSR)
								printf("\x1b[32m  %s\x1b[0m\n",myfile->d_name);
						else
								printf("  %s\n",myfile->d_name);

					//	printf("  %s \n", myfile->d_name);
				}

		}
		closedir(mydir);
		chdir(CWD);
}

