#include<stdio.h>


typedef struct
{
	int data;
}CONFIG;

main()
{
	FILE *fp;
	CONFIG config;
	int i;

    if ( (fp=fopen("config.dat","w"))==NULL ) /*打开文件*/
    	printf("File could not be opened\n");
    else
    {
		printf("请依次输入MinSex,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen:");
		for(i = 0;i <= 4;i++)
		{
			scanf("%d", &config.data);
			fwrite(&config.data,sizeof(CONFIG),1,fp);
			
		}
   		fclose(fp);

    }
    
    return 0;
}


 
