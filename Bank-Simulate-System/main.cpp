#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"

//Variable Define
int MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,v_extraorder, p_extraorder, sum_p, wait_p, sum_v, wait_v, n, servepnumber, servevnumber,pause_order,waitpn, waitvn,flag3[8],sum,quit = 1,strategy = 1,check_linenump = 0,check_linenumv = 0;
char order,viporder[5] ,str1[20] = {0} , str2[20] = {0};
int change =0;
int quit1 =0;
time_t start,recordtime,rtime,rest_time_p[6],rest_time_v[2];
RECORD record[8];
serve_v servev[2];   //两个VIP窗口     
serve_p servep[6];   //六个普通窗口 
Linkqueue *Q;        //普通客户的队列 
Linkqueue *U;        //VIP客户的队列 
IMAGE img3,img,img1,cover1,cover2,cover3,cover4,cover5,cover6,cover7,cover8,baycover1,baycover2,baycover3,baycover4,VIPA,VIPA2,pu1,pu2,pause1,pause2,VIPG1,VIPG2,C1,C2;
IMAGE linecover1,linecover2,timecover;
MOUSEMSG m; 
char s6[] = "定向服务策略";
char  s7[] = "顺便服务策略";
char s8[] ="正在等待下班";
HWND initial;
time_t tt;
struct tm *t;
char ss[100];

int main()
{

    HANDLE hThreadi;
	HANDLE hThreadin;
	int i, j, k;
	
	printf("请输入服务时间最小时长:");
	scanf("%d", &MinSec);
	fflush(stdin);
	printf("请输入服务时间最长时长:");
	scanf("%d", &MaxSec);
	fflush(stdin);
	printf("请输入休息时间最短时长:");
	scanf("%d", &MinRestSec);
	fflush(stdin);
	printf("请输入休息时间最长时长:");
	scanf("%d", &MaxRestSec);
	fflush(stdin);
	printf("请输入VIP队列等待最长时长:");
	scanf("%d", &VIPSERVLen);
	fflush(stdin);

			
	//参数初始化
	wait_p = 0; wait_v = 0; sum_p = 0; wait_v = 0; n = 10; rtime = 0; sum_v = 0; servepnumber = 0; servevnumber = 0;
	p_extraorder = 0; v_extraorder = 0; recordtime = 0; pause_order = 0; waitpn = 0; waitvn = 0;strategy = 1;
	quit = 1;

	//初始化普通顾客队列 
	Q = Initqueue();
	//初始化VIP客户队列
	U = Initqueue();                  

	for (i = 0; i <= 7; i++)
	{
		flag3[i] = 0;
	}
	//初始化各普通窗口状态 
	for (i = 0; i <= 2; i++)
	{
		servep[i].state = 0;
		servep[i].endwork = 0;
		servep[i].servenum = 0;
	}
	for (j = 3; j <= 5; j++)
	{
		servep[j].state = 3;
		servep[j].endwork = 0;
		servep[j].servenum = 0;
	}
	//初始化VIP窗口状态 
	servev[0].state = 0;
	servev[0].endwork = 0;
	servev[0].servenum = 0;
	servev[1].state = 3;
	servev[1].endwork = 0;
	servev[1].servenum = 0;
	//初始化记录参数
	for (k = 0; k <= 7; k++)
	{
		record[k].totalnum = 0;
		record[k].totaltime = 0;
	}

	
		printf("***************************欢迎使用银行模拟系统*********************************\n");
		newwin();						//欢迎界面初始化
		winimg();						//银行主界面初始化
		

		time(&start);   //开业时间
		hThreadi = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)input, NULL, 0, NULL);//开启输入线程 
		hThreadin = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)output, NULL, 0, NULL);//开启定时将银行营业状况输出到输出文件内的线程


		//主循环
		while ((quit != 0) || (wait_p != 0) || (wait_v != 0) || def() != 0)
		{
			state_change();
			if(suretime()%5==0&&suretime>0)
			{
				putimage(540,0,&timecover);
	            time(&tt);
            	t = localtime(&tt);
			   setcolor(RED);
	        sprintf(ss,"%4d年%02d月%02d日%02d:%02d:%02d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
            outtextxy(565,0,ss);
	        setcolor(WHITE);
			}
			//changeBay();
		}

		//输出退出界面动画
		closeimg();
		printf("系统已经关闭,欢迎下次使用\n\n\n");
		closegraph();
	
		system("pause");		
		return 0;
}




