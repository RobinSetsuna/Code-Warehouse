#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"



void state_change()

{
	int i, j;
	time_t tcurrent, time;
	char stu[200];
	
	if(wait_p==0&&wait_v==0&&def() == 0)
	{
		putimage(579,555,&linecover2);
	}

	if(quit ==0&&quit1 == 1)
	{
		 setcolor(YELLOW);
         outtextxy(580, 500, s8);
		 setcolor(WHITE);
	}
    if(change == 1)
	{
		if(strategy == 1)
		{
          putimage(579,605,&linecover1);
		  setcolor(YELLOW);
          outtextxy(580, 600, s7);
		  setcolor(WHITE);
		}
		if(strategy == 2)
		{
          putimage(579,605,&linecover1);
		  setcolor(YELLOW);
          outtextxy(580, 600, s6);
		  setcolor(WHITE);
		}
		change = 0;
	}
 
	v_extraorder = v_judge();
	p_extraorder = p_judge();               //如果要开新的窗口开一个，返回1，如果除了固定的窗口还有新
	                                        //的窗口并且要关闭，返回2 
	closeserve_p();	                       //根据指令关闭新开的窗口	                    
	closeserve_v();
	if((check_linenump == 1) || (check_linenumv == 1))
	{
		linenum();
		check_linenump = 0;
		check_linenumv = 0;
	}

	tcurrent = suretime();
	for (i = 0; i <= 5; i++)
	{
		drawservenump(i);
		switch (servep[i].state)
		{
		case FREE:
			if (i == (n - 1))
			{
				if (pause_order == 1)
				{
					n=0;
					servep[i].state = PAUSED;
					//更新动画状态
					draw(i,servep[i].state);
					drawservenump(i);
					rest_time_p[i] = tcurrent + timerandom(2);
					pause_order = 0;
				}
			}
			else
			{
				servep[i].servenum = Dlqueue(Q);
				if ((servep[i].servenum) != 0)
				{
                     putimage(579,555,&linecover2);
					 sprintf(stu,"%请%d号客户到%d号窗口",servep[i].servenum,i+1);
		             setcolor(YELLOW);
                     outtextxy(580, 550, stu);
		             setcolor(WHITE);
					//叫号（如果队列不为空，队列切头，Dlqueue-p()）
					servepnumber++;
					time = timerandom(1);
					record[i].totaltime = record[i].totaltime + time;
					servep[i].endwork = tcurrent + time;
					
					wait_p--;					//随机产生服务的时间
					linenum();
					record[i].totalnum++;
					servep[i].state = BUSY;

					//更新动画状态
					draw(i,servep[i].state);
					drawservenump(i);
					printf("draws!");
				}

			}
			break;
			//是否发出了休息指令和是否通过了，空闲叫号，如果队列不为空，队列切头，Dlqueue-p()，wait-p--; 
		case BUSY:
			if (i == (n - 1))
			{
				if (pause_order == 3)										//是否发出了休息指令和是否通过了，判断是否要转换状态为空闲；   //正在工作状态 
				{
					n=0;
					flag3[i] = 1;
					pause_order = 0;
					waitpn++;
				}
			}
			if (tcurrent / servep[i].endwork == 1)
			{
				servepnumber--;
				servep[i].servenum = 0;
				if (flag3[i] == 1)
				{
					servep[i].state = PAUSED;
					draw(i,servep[i].state);
					drawservenump(i);
					waitpn--;
					rest_time_p[i] = tcurrent + timerandom(2);
					flag3[i] = 0;
				}
				else
				{
                    servep[i].state = FREE;
				    draw(i,servep[i].state);
				    drawservenump(i);
				}
			}
			break;
			//休息时间有没有到
		case PAUSED:
			if (tcurrent/rest_time_p[i] == 1)
			{
				servep[i].state = FREE;
				draw(i,servep[i].state);
				drawservenump(i);
			}
			break;

		case CLOSED:
			if (p_extraorder == 1)
			{
				servep[i].state = FREE;
				draw(i,servep[i].state);
				drawservenump(i);
				p_extraorder = 0;
               switch(i)
			   {
				  case 3:
					setorigin(0,0);	
					putimage(833,120,&baycover2);
					setorigin(850,140);
					loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
					setorigin(0,0);	
					break;

				  case 4:
					setorigin(0,0);	
					putimage(1000,120,&baycover3);
					setorigin(1020,140);
					loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
					setorigin(0,0);	
					break;

				   case 5:
					setorigin(0,0);	
					putimage(1170,120,&baycover4);
				    setorigin(1180,140);
					loadimage(NULL, "普通窗口FREE状态图片.gif",150,180);
					setorigin(0,0);	
					break;
			   }
			}
			break;

		default:break;
		}
		setorigin(0,0);
	}


	tcurrent = suretime();
	for (j = 0; j <= 1; j++)
	{
		if(servev[j].state == PBUSY)
			drawservenumv(j,2);
		else
			drawservenumv(j,1);
		switch (servev[j].state)
		{
		case FREE:												
			if (j == (n - 7))
			{
				if (pause_order == 1)
				{
					n=0;
					servev[j].state = PAUSED;
					draw2(j,servev[j].state);
					drawservenumv(j,1);
					rest_time_v[j] = tcurrent + timerandom(2);
					pause_order = 0;
				}
			}
			else
			{
				if (wait_v != 0)
				{
					servev[j].servenum = Dlqueue(U);
					if (servev[j].servenum != 0)
					{	

					 putimage(579,555,&linecover2);
					 sprintf(stu,"%请v%d号客户到v%d号窗口",servev[j].servenum,j+1);
		             setcolor(YELLOW);
                     outtextxy(580, 550, stu);
		             setcolor(WHITE);
						servevnumber++;
						time = timerandom(1);
						record[j + 6].totaltime = record[j + 6].totaltime + time;
						servev[j].endwork = tcurrent + time;
						wait_v--;
						linenum();
						record[j + 6].totalnum++;
						servev[j].state = BUSY;
						draw2(j,servev[j].state);
						drawservenumv(j,1);
					}
						
				}
				else if ((wait_v == 0) && (wait_p != 0)&& (strategy == 1)&& def2() != 0)  //策略变换顺便服务
				{                                                           //叫号（如果队列不为空，队列切头，Dlqueue-p()）
					servev[j].servenum = Dlqueue(Q);

					if (servev[j].servenum != 0)
					{
						putimage(579,555,&linecover2);
					  sprintf(stu,"%请%d号客户到v%d号窗口",servev[j].servenum,j+1);
		             setcolor(YELLOW);
                     outtextxy(580, 550, stu);
		             setcolor(WHITE);
						servepnumber++;
						time = timerandom(1);
						record[j + 6].totaltime = record[j + 6].totaltime + time;
						servev[j].endwork = tcurrent + timerandom(1);        //随机产生服务的时间
						wait_p--;	
						linenum();
						record[j + 6].totalnum++;
						servev[j].state = PBUSY;
						draw2(j,servev[j].state);
						drawservenumv(j,2);
					
					}
				}

			}
			break;

		case BUSY:
			if (j == (n - 7))
			{
				if (pause_order == 3)										//是否发出了休息指令和是否通过了，判断是否要转换状态为空闲；   //正在工作状态 
				{
					n = 0;
					flag3[j + 6] = 1;
					waitvn++;
					pause_order = 0;
				}
			}
			if (tcurrent / servev[j].endwork == 1)
			{
				servevnumber--;
				servev[j].state = FREE;
				draw2(j,servev[j].state);
				drawservenumv(j,1);
				servev[j].servenum = 0;

				drawservenumv(j,1);


				if (flag3[j + 6] == 1)
				{
					servev[j].state = PAUSED;
					draw2(j,servev[j].state);
					drawservenumv(j,1);
					waitvn--;
					rest_time_v[j] = tcurrent + timerandom(2);
					flag3[j + 6] = 0;
				}
			}
			break;

		case PBUSY:
			if (j == (n - 7))
			{
				if (pause_order == 3)										//是否发出了休息指令和是否通过了，判断是否要转换状态为空闲；   //正在工作状态 
				{
					n = 0;
					flag3[j + 6] = 1;
					waitvn++;
					pause_order = 0;
				}
			}
			if (tcurrent / servev[j].endwork == 1)
			{
				servepnumber--;
				servev[j].state = FREE;
				draw2(j,servev[j].state);
				drawservenumv(j,1);
				servev[j].servenum = 0;
				if (flag3[j + 6] == 1)
				{
					servev[j].state = PAUSED;
					draw2(j,servev[j].state);
					drawservenumv(j,1);
					waitvn--;
					rest_time_v[j] =tcurrent + timerandom(2);
					flag3[j + 6] = 0;
				}
			}
			break;




		case PAUSED:
			if (tcurrent/rest_time_v[j] == 1)
			{
				servev[j].state = FREE;
				draw2(j,servev[j].state);
				drawservenumv(j,1);
			}
			break;

		case CLOSED:
			if (v_extraorder == 1)
			{
				servev[j].state = FREE;
				draw2(j,servev[j].state);
				drawservenumv(j,1);
				setorigin(0,0);
			    putimage(173,120,&baycover1);
			    setorigin(180,140);
			    loadimage(NULL, "VIP窗口FREE状态大白.gif",150,180);
				setorigin(0,0);
				v_extraorder = 0;
			}
			break;

		default:
			break;
		}
	}
}


void closeserve_p()
{

	if (p_extraorder == 2)
	{
		if ((servep[5].state == FREE))
		{
			servep[5].state = CLOSED;
			draw(5,servep[5].state);
			flag3[5] = 0;
			setorigin(0,0);	
			putimage(1170,120,&baycover4);
			setorigin(968,20);
			loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
			
		}
		else if ((servep[5].state == CLOSED&&servep[4].state == FREE))
		{
			servep[4].state = CLOSED;
			draw(4,servep[4].state);
			flag3[4] = 0;
			setorigin(0,0);	
			putimage(1000,120,&baycover3);
			setorigin(798,20);
			loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
		}
		else if (servep[3].state == FREE)
		{
			servep[3].state = CLOSED;
			draw(3,servep[3].state);
			flag3[3] = 0;
			setorigin(0,0);	
			putimage(833,120,&baycover2);
			setorigin(630,20);
			loadimage(NULL, "普通窗口CLOSE状态图片.gif",560,310);
			
		}
		p_extraorder = 0;
		setorigin(0,0);	
	}
}

void closeserve_v()
{

	if (v_extraorder == 2)
	{
		if ((servev[1].state == FREE))
		{
			servev[1].state = CLOSED;
			draw2(1,servev[1].state);
			setorigin(0,0);
			putimage(173,120,&baycover1);
			setorigin(160,100);
			loadimage(NULL, "VIP窗口CLOSE状态.gif",220,240);
			setorigin(0,0);
			flag3[7] = 0;
		}
		v_extraorder = 0;
	}
}


time_t timerandom(int mark)
{
	time_t i;

	srand(time(NULL));

	if (mark == 1)
	{
		i = rand() % (MaxSec - MinSec + 1);
		return (i + (MaxSec - MinSec));
	}
	else if (mark == 2)
	{
		i = rand() % (MaxRestSec - MinRestSec + 1);
		return (i + (MaxRestSec - MinRestSec));
	}

	return 0;
}


time_t suretime()
{
	time_t current;
	time(&current);
	return (current - start);
}
