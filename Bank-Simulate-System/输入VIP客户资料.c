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
	if((vipfp=fopen("vip.dat","w"))==NULL)
	{
		printf("can not open the file\n");
		exit(0);
    };
    printf("请输入VIP客户的人数"); 
    scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
	 getchar();
	 gets(d.name);
	 gets(d.ID);
	 
	 scanf("%d",&d.money);
	 
	 fwrite(&d,sizeof(VIPDATA),1,vipfp);
	}
	 
	 fclose(vipfp);
	 return 0; 
}
