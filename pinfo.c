#include "os.h"

// pinfo command
void pinf(char *ss)
{
		char dd[10000],ee[10000],*ff[1000];
		strcpy(dd,"/proc/");
		strcat(dd,ss);
		strcat(dd,"/stat");
		FILE *fd;
		fd=fopen(dd,"r");
		fscanf(fd,"%[^\n]",ee);
		int z=0;
		ff[0]=strtok(ee," \t");
		while(ff[z])
		{
				z++;
				ff[z]=strtok(NULL," \t");
		}
		printf("pid--%s\nProcess status--%s\nmemory -%s\nExecutable path --%s\n",ff[0],ff[2],ff[8],ff[1]);
}

