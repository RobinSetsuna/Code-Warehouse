#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"


//欢迎界面
void newwin()
{
	// 绘图环境初始化
	initgraph(1024, 600);
	// 设置背景色为蓝色
	setbkcolor(WHITE);
	// 用背景色清空屏幕
	cleardevice();
	// 读取图片至绘图窗口
	loadimage(NULL, "欢迎界面.gif",1024,600);
		
	getch();
	closegraph();

}

void winimg()
{
	initial = initgraph(1366, 768);		// 初始化 1366 x 768 的绘图窗

	IMAGE img2;
	char s[] = "点我下班";
	char s1[] = "普通客户取号";
	char s2[] = "VIP客户取号";
	char s3[] = "暂停窗口";
	char s4[] = "策略转换";
	char s5[] = "VIP管理";
	char info[10] = {0};
	
	// 设置背景色为白色
	setbkcolor(WHITE);
	// 用背景色清空屏幕
	cleardevice();
	//载入背景图
	loadimage(NULL,"1.gif",1366,768);
	//预读取覆盖图
	getimage(&img, 0, 0, 280, 70);
	getimage(&img3,0, 0, 100, 55);
	getimage(&cover1, 50, 330, 150, 55);
	getimage(&cover2, 200, 330, 150, 55);
	getimage(&cover3, 350, 330, 150, 55);
	getimage(&cover4, 500, 330, 150, 55);
	getimage(&cover5, 680, 330, 150, 55);
	getimage(&cover6, 840, 330, 150, 55);
	getimage(&cover7, 1000, 330, 150, 55);
	getimage(&cover8, 1200, 330, 150, 55);
	getimage(&baycover1, 173,  120 ,187, 210);
	getimage(&baycover2, 833, 120, 168, 210);
	getimage(&baycover3, 1000, 120, 168, 210);
	getimage(&baycover4, 1170, 120, 168, 210);
	getimage(&linecover1, 579, 605, 144, 37);
	getimage(&linecover2, 579, 555, 266, 37);
	getimage(&timecover,560,0,290,40);;
	//字体输出模式为透明
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	// 设置输出效果为抗锯齿
	LOGFONT f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 30;                      // 设置字体高度为 48
	strcpy(f.lfFaceName, "微软雅黑");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);   // 设置字体样式
	outtextxy(1270, 0, s);				//输出点我下班
    
    loadimage(&pu1,"普通1.jpg",160,40);
	putimage(0,730,&pu1);
	loadimage(&pu2,"普通2.jpg",160,40);

    loadimage(&VIPA,"VIP1.jpg",160,40);
	putimage(0,690,&VIPA);
	loadimage(&VIPA2,"VIP2.jpg",160,40);

	loadimage(&pause1,"暂停窗口1.jpg",160,40);
	putimage(0,650,&pause1);
	loadimage(&pause2,"暂停窗口2.jpg",160,40);

	loadimage(&VIPG1,"VIP管理1.jpg",160,40);
	putimage(1210,690,&VIPG1);
	loadimage(&VIPG2,"VIP管理2.jpg",160,40);

	loadimage(&C1,"策略转换1.jpg",160,40);
	putimage(1210,730,&C1);
	loadimage(&C2,"策略转换2.jpg",160,40);


    setcolor(YELLOW);
	outtextxy(580, 600, s7);				//输出暂停窗口
	setcolor(WHITE);

	//以宋体输出欢迎来到大白银行
	LOGFONT y;
	getfont(&y);                          // 获取当前字体设置
	y.lfHeight = 40;                      // 设置字体高度为 48
	strcpy(y.lfFaceName, "华文彩云");         // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&y);                          // 设置字体样式
	outtextxy(525,405,"欢 迎 来 到 大 白 银 行"); //输出欢迎来到大白银行
	
	// 设置输出效果为抗锯齿
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 30;                      // 设置字体高度为 48
	strcpy(f.lfFaceName, "微软雅黑");     // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	setfont(&f);                          // 设置字体样式
    //loadimage(NULL, "VIP窗口CLOSE状态.gif",220,240);
    setcolor(RED);
	
    time(&tt);
	t = localtime(&tt);
	sprintf(ss,"%4d年%02d月%02d日%02d:%02d:%02d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    outtextxy(565,0,ss);
	setcolor(WHITE);

	setbkmode(TRANSPARENT);
	setbkcolor(BLACK);

	setorigin(20,140);
	loadimage(NULL, "VIP窗口FREE状态大白.gif",150,180);
	setorigin(160,100);
	loadimage(NULL, "VIP窗口CLOSE状态.gif",220,240);
	setorigin(364,140);
	loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
	setorigin(520,140);
	loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
	setorigin(680,140);
	loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
	setorigin(630,20);
	loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
	setorigin(798,20);
	loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
	setorigin(968,20);
	loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
	//VIP
	setorigin(50,70);
	loadimage(NULL, "Free.gif",100,55);

	setorigin(200,70);
	loadimage(NULL, "close.gif",100,55);

	setorigin(390,70);
	loadimage(NULL, "Free.gif",100,55);

	setorigin(550,70);
	loadimage(NULL, "Free.gif",100,55);

	setorigin(700,70);
	loadimage(NULL, "Free.gif",100,55);

	setorigin(870,70);
	loadimage(NULL, "close.gif",100,55);

	setorigin(1030,70);
	loadimage(NULL, "close.gif",100,55);

	setorigin(1200,70);
	loadimage(NULL, "close.gif",100,55);
    
	setorigin(0,0);
	//输出默认排队信息
	linenum();
}

void linenum()
{
	setorigin(0,0);
	setaspectratio(1, 1); 
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	sprintf(str1,"当前普通客户排队人数:%d",wait_p);
	outtextxy(0,0, str1);
	sprintf(str2,"当前VIP客户排队人数:%d",wait_v);
	outtextxy(0,33, str2);
}

void closeimg()
{	
	setorigin(0,0);
	BeginBatchDraw();
	// 设置背景色为蓝色
	setbkcolor(WHITE);
	// 用背景色清空屏幕
	cleardevice();
	// 读取图片至绘图窗口
	loadimage(NULL, "结束界面.gif",1366,768);
	EndBatchDraw();

	getch();
}

void draw(int winnum,int wis)
{
		switch(wis)
		{
			case FREE:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(400,60,&img3);
					setorigin(390,70);
					loadimage(NULL, "Free.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(550,60,&img3);
					setorigin(550,70);
					loadimage(NULL, "Free.gif",100,55);
					setorigin(0,0);
					break;

					case 2:
					setorigin(0,0);
					putimage(700,60,&img3);
					setorigin(700,70);
					loadimage(NULL, "Free.gif",100,55);
					setorigin(0,0);
					break;

					case 3:
					setorigin(0,0);
					putimage(860,60,&img3);
					setorigin(870,70);
					loadimage(NULL, "free.gif",100,55);
					setorigin(0,0);
					break;

					case 4:
					setorigin(0,0);
					putimage(1030,60,&img3);
					setorigin(1030,70);
					loadimage(NULL, "free.gif",100,55);
					setorigin(0,0);
					break;

					case 5:
					setorigin(0,0);
					putimage(1200,60,&img3);
					setorigin(1200,70);
					loadimage(NULL, "free.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;

			case BUSY:
					switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(400,60,&img3);
					setorigin(390,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(550,60,&img3);
					setorigin(550,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 2:
					setorigin(0,0);
					putimage(700,60,&img3);
					setorigin(700,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 3:
					setorigin(0,0);
					putimage(860,60,&img3);
					setorigin(870,70);
					loadimage(NULL, "busy.gif",100,55);
					break;

					case 4:
					setorigin(0,0);
					putimage(1030,60,&img3);
					setorigin(1030,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 5:
					setorigin(0,0);
					putimage(1200,60,&img3);
					setorigin(1200,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;		

			case PAUSED:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(400,60,&img3);
					setorigin(390,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(550,60,&img3);
					setorigin(550,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 2:
					setorigin(0,0);
					putimage(700,60,&img3);
					setorigin(700,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 3:
					setorigin(0,0);
					putimage(860,60,&img3);
					setorigin(870,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 4:
					setorigin(0,0);
					putimage(1030,60,&img3);
					setorigin(1030,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 5:
					setorigin(0,0);
					putimage(1200,60,&img3);
					setorigin(1200,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;
			
			case CLOSED:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(400,60,&img3);
					setorigin(390,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(550,60,&img3);
					setorigin(550,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 2:
					setorigin(0,0);
					putimage(700,60,&img3);
					setorigin(700,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 3:
					setorigin(0,0);
					putimage(860,60,&img3);
					setorigin(870,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 4:
					setorigin(0,0);
					putimage(1030,60,&img3);
					setorigin(1030,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 5:
					setorigin(0,0);
					putimage(1200,60,&img3);
					setorigin(1200,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
				}
			break;
		}
}

void draw2(int winnum,int wist)
{
	switch(wist)
		{
			case FREE:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(50,60,&img3);
					setorigin(50,70);
					loadimage(NULL, "Free.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(200,60,&img3);
					setorigin(200,70);
					loadimage(NULL, "Free.gif",100,55);
					setorigin(0,0);
					break;

				}
			break;

				case BUSY:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(50,60,&img3);
					setorigin(50,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(200,60,&img3);
					setorigin(200,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;		

			case PAUSED:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(50,60,&img3);
					setorigin(50,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(200,60,&img3);
					setorigin(200,70);
					loadimage(NULL, "pause.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;
			
			case CLOSED:
				switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(50,60,&img3);
					setorigin(50,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(200,60,&img3);
					setorigin(200,70);
					loadimage(NULL, "close.gif",100,55);
					setorigin(0,0);
					break;
				}
			break;


				case PBUSY:
					switch(winnum)
				{
					case 0:
					setorigin(0,0);
					putimage(50,60,&img3);
					setorigin(50,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					case 1:
					setorigin(0,0);
					putimage(200,60,&img3);
					setorigin(200,70);
					loadimage(NULL, "busy.gif",100,55);
					setorigin(0,0);
					break;

					
				}
			break;		
		}
}

void drawservenumv(int mark,int ty)
{						
			setorigin(0,0);
			setcolor(WHITE);
			if(ty == 1)
			{
					if(servev[mark].servenum == 0)
					{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(50, 330, &cover1);
									EndBatchDraw(); 
									break;
								case 1:
									BeginBatchDraw();
									putimage(200, 330, &cover2);
									EndBatchDraw();
									break;
							}
						}
						else
						{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(50, 330, &cover1);
									sprintf(str2,"%服务号码:V%d",servev[mark].servenum);
									outtextxy(50,330, str2);
									EndBatchDraw();
									break;
								case 1:
									BeginBatchDraw();
									putimage(200, 330, &cover2);
									sprintf(str2,"V%d",servev[mark].servenum);
									outtextxy(200,330, str2);
									EndBatchDraw();
									break;
							}
						}
						
					}
					

					if(ty == 2)
					{
						setorigin(0,0);
						if(servev[mark].servenum == 0)
						{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(50, 330, &cover1);
									EndBatchDraw(); 
									break;
								case 1:
									BeginBatchDraw();
									putimage(200, 330, &cover2);
									EndBatchDraw();
									break;
							}
							 
						}
						else
						{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(50, 330, &cover1);
									sprintf(str2,"%服务号码:%d",servev[mark].servenum);
									outtextxy(50,330, str2);
									EndBatchDraw();
									break;
								case 1:
									BeginBatchDraw();
									putimage(200, 330, &cover2);
									sprintf(str2,"%服务号码:%d",servev[mark].servenum);
									outtextxy(200,330, str2);
									EndBatchDraw();
									break;
							}
						}
					}					
}

void drawservenump(int mark)
{	
						
						setorigin(0,0);
						setcolor(WHITE);
						if(servep[mark].servenum == 0)
						{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(350, 330, &cover3);
									EndBatchDraw(); 
									break;
								case 1:
									BeginBatchDraw();
									putimage(500, 330, &cover4);
									EndBatchDraw();
									break;
								case 2:
									BeginBatchDraw();
									putimage(680, 330, &cover5);
									EndBatchDraw();
									break;

								case 3:
									BeginBatchDraw();
									putimage(840, 330, &cover6);
									EndBatchDraw();
									break;

								case 4:
									BeginBatchDraw();
									putimage(1000, 330, &cover7);
									EndBatchDraw();
									break;

								case 5:
									BeginBatchDraw();
									putimage(1200, 330, &cover8);
									EndBatchDraw();
									break;

							}
							 
						}
						else
						{
							switch(mark)
							{
								case 0:
									BeginBatchDraw();
									putimage(350, 330, &cover3);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(350,330, str2);
									EndBatchDraw();
									break;
								case 1:
									BeginBatchDraw();
									putimage(500, 330, &cover4);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(500,330, str2);
									EndBatchDraw();
									break;
								case 2:
									BeginBatchDraw();
									putimage(680, 330, &cover5);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(680,330, str2);
									EndBatchDraw();
									break;
								case 3:
									BeginBatchDraw();
									putimage(840, 330, &cover6);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(840,330, str2);
									EndBatchDraw();
									break;
								case 4:
									BeginBatchDraw();
									putimage(1000, 330, &cover7);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(1000, 330, str2);
									EndBatchDraw();
									break;
								case 5:
									BeginBatchDraw();
									putimage(1200, 330, &cover8);
									sprintf(str2,"服务号码:%d",servep[mark].servenum);
									outtextxy(1200, 330, str2);
									EndBatchDraw();
									break;		
							}
						}					
}

