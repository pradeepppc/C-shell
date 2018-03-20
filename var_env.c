#include "os.h"

void var_env(int argc, char *argv[])
{
	if(argc<=1 && argc>3)
	{
		printf("Usage of command is wrong\n");
		return;
	}
	if(argc == 2 && argv[0] != "setenv")
	{

		int x = unsetenv(argv[1]);
	}
	else if(argc == 3 && argv[0] != "unsetenv")
	{
		int x = setenv(argv[1], argv[2],1);
		char *p;
		p = getenv(argv[1]);
		printf("Created env variable %s\n",p);

	}
	else
	{
		printf("Usage of command is wrong\n");
	}
	
	return;
}