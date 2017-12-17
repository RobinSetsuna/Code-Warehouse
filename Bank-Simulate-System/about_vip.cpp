#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"



void vipchange(FILE* vipfp)
{
	char s6[] = "点我下班";
	char s1[] = "普通客户取号";
	char s2[] = "VIP客户取号";
	char s3[] = "暂停窗口";
	char s4[] = "策略转换";
	char s5[] = "VIP管理";

	VIPDATA blanklist = { "", "", 0 };
	VIPDATA newlist, s[20], h;
	char del[20];			//读取要删除的ID号 

	int i, L, flag;
	char order, o1;

	fread(&s[0], sizeof(VIPDATA), 1, vipfp);
	for (i = 1; !feof(vipfp); i++)
	{
		fread(&s[i], sizeof(VIPDATA), 1, vipfp);

	}
	L = i - 1;

	order = viporder[0];

	while (order != 'E')
	{	//读取V之后的字符 
		o1 = viporder[1];
		fflush(stdin);
		switch (o1)
		{
		case '-':
			i = 0;
			flag = 0;
			InputBox(del,20,"请输入要删除的VIP的ID号","VIP管理");
			while (i <= L&&flag == 0)
			{
				if (strcmp(s[i].ID, del) == 0)
					flag = 1;

				i++;
			}
			i = i - 1;			//帮助fseek找到要删除VIP文件的位置 （往前回滚1） 

			rewind(vipfp);
			//删除操作 
			if (flag == 0)
			{
				//printf("没有该客户的信息，无法删除!\n");
				//动画弹窗
				MessageBox (NULL, TEXT ("没有该客户的信息，无法删除\n: )"), TEXT("注意"), 0);
				//system("pause");
			}

			else
			{
				fseek(vipfp, i*sizeof(VIPDATA), SEEK_CUR);
				fwrite(&blanklist, sizeof(VIPDATA), 1, vipfp);
			}

			rewind(vipfp);
			fread(&s[0], sizeof(VIPDATA), 1, vipfp);
			for (i = 1; !feof(vipfp); i++)
			{
				fread(&s[i], sizeof(VIPDATA), 1, vipfp);
			}
			L = i - 1;
			rewind(vipfp);
			break;


		case '+':
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入新增VIP的名字","VIP管理");
			strcpy(h.name,del);
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入新增VIP的ID","VIP管理");
			strcpy(h.ID,del);
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入新增VIP的存款","VIP管理");
			sscanf(del, "%d", &h.money);


			fseek(vipfp, 0, SEEK_END);
			fwrite(&h, sizeof(VIPDATA), 1, vipfp);
			rewind(vipfp);
			fread(&s[0], sizeof(VIPDATA), 1, vipfp);
			for (i = 1; !feof(vipfp); i++)
			{
				fread(&s[i], sizeof(VIPDATA), 1, vipfp);
			}
			L = i - 1;
			rewind(vipfp);
			break;

		case '/':
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入要更新VIP的ID","VIP管理");
			strcpy(h.ID,del);
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入VIP的名字","VIP管理");
			strcpy(h.name,del);
			memset(del,0,20*sizeof(char));
			InputBox(del,20,"请输入VIP的存款","VIP管理");
			sscanf(del, "%d", &h.money);
	
			i = 0;
			flag = 0;

			while (i <= L&&flag == 0)
			{
				if (strcmp(s[i].ID, h.ID) == 0)
					flag = 1;

				i++;
			}
			strcpy(newlist.name, h.name);
			strcpy(newlist.ID, h.ID);
			i = i - 1;
			newlist.money = h.money;

			rewind(vipfp);
			if (flag == 0)
				//动画弹窗
				MessageBox (NULL, TEXT ("没有该客户的信息，无法更改\n: )"), TEXT("注意"), 0);
			else
			{
				fseek(vipfp, i*sizeof(VIPDATA), SEEK_CUR);
				fwrite(&newlist, sizeof(VIPDATA), 1, vipfp);
			}

			rewind(vipfp);
			fread(&s[0], sizeof(VIPDATA), 1, vipfp);
			for (i = 1; !feof(vipfp); i++)
			{
				fread(&s[i], sizeof(VIPDATA), 1, vipfp);
			}
			L = i - 1;
			rewind(vipfp);
			break;
		default:break;
		}
		InputBox(viporder,5,"输入E			退出维护状态\n输入V+			增加VIP\n输入V-			删除VIP\n输入V/			更新VIP","VIP管理");
		order = viporder[0];	
	}
	fclose(vipfp);
}


void checkvip(char s[ ])
{
	VIPDATA Constant;
	FILE* ftp;
	//判断变量
	int judge = 0;

	if ((ftp = fopen("vip.dat", "r")) == NULL)
	{
		printf("无法打开文件！\n");
		exit(0);
	}

	//此时判断是否为vip，是则judge=0，否则不改变 
	while (!feof(ftp) && judge == 0)
	{
		fread(&Constant, sizeof(VIPDATA), 1, ftp);
		if (strcmp(Constant.ID, s) == 0)
		{
			judge = 1;
			order = 'V';
		}
	}
	if(judge == 0)
		order = 'G';
	fclose(ftp);
}
