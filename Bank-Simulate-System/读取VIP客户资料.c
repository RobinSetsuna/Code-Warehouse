#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char name[20];
	char ID[20];
	int money;
}VIPDATA;
main()
{
	VIPDATA d;
	int n;
	int i;
	FILE* vipfp;
	if((vipfp=fopen("vip.dat","r"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
    }
    else
    {
    	fread(&d,sizeof(VIPDATA),1,vipfp);
    	while(!feof(vipfp))
    	{
    		printf("%s\n",d.name);
    		printf("%s\n",d.ID);
    		printf("%d\n",d.money);
			fread(&d,sizeof(VIPDATA),1,vipfp);
    	//	if(feof(vipfp) == 0)
    	//		break;
		}
	}
    
	 fclose(vipfp);
	 system("pause");
	 return 0; 
}
