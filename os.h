#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<ctype.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<grp.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>

 typedef struct jobs{
		char name[1000];
		long int pid;
		struct jobs *nxt;
		int type;
	}bgcom;

void var_env(int argc, char *argv[]);
int execute(char *a,char *CWD,char *PWD);
char *dir(char *CWD);
void echo(char **aa);
void ls(char **aa,int i);
int split(char *tt,char **aa);
void pinf(char *ss);
void sig_br(int sig);
void sighand(int sig);
void sig_bg(int sig);
int execute2(char *s2,char *CWD,char *PWD,int fin,int fout,int fd_input,int flag2);
void pipecmd(char *s2,char *CWD,char *PWD);
int redir(char *s2,char *CWD,char *PWD,int type,int fd_input,int cond);
void pri();