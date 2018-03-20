#include "os.h"


//tokenising the give input into tokens
int split(char *tt,char **aa)
{
		if(!strcmp(aa[0],"echo"))
		{
				*aa++;
				*aa=strtok(NULL,"");
				*aa++;
				*aa='\0';
				return 1;
		}

		*aa++;
		tt=strtok(NULL," \t\n\0");
		int i=1;
		while(tt)
		{
				*aa++ =tt;
				i++;
				tt=strtok(NULL," \t\0\n");
		}
		*aa='\0';
		return i;
}

