#include "os.h"


//echo command
void echo(char **aa)
{
		int i=0;
		int flag1=0,flag2=0,flag3=0;
		while(aa[1][i])
		{
				if(aa[1][i]==34)
				{
						if(flag1==0 && flag2==0)
								flag1=1;
						else if(flag1==1)
								flag1=0;
						else
								printf("%c",aa[1][i]);
				}
				else if(aa[1][i]==39)
				{
						if(flag1==0 && flag2==0)
								flag2=1;
						else if(flag2==1)
								flag2=0;
						else
								printf("%c",aa[1][i]);
				}
				else if(aa[1][i]==' ')
				{
						if(flag1==1 || flag2==1)
								printf("%c",aa[1][i]);
						else if(flag1==0 && flag2==0 && flag3==0)
						{
								printf(" ");
								flag3=1;
						}


				}
				else
				{
						printf("%c",aa[1][i]);
						flag3=0;
				}
				i++;
		}
		return;

}

