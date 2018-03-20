#include "os.h"



//Finding the current path of directory
char *dir( char *CWD)
{
		static char PWD[10000];
		getcwd(PWD,sizeof(PWD));
		int yes=strcmp(PWD,CWD);
		if(yes==0)
		{	
				static char p[10000];
				p[0]='~';
				return p;
		}
		else
		{
				if(strlen(PWD)<strlen(CWD))
						return PWD;
				static char p[10000];
				p[0]='~';
				int j=1;
				int i;
				for(i=strlen(CWD);i<strlen(PWD);i++)
				{
						p[j++]=PWD[i];
				}
				return p;
		}
}
