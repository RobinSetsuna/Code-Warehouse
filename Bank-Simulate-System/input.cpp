#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"


void input()
{
	char info[20];
	char vID[20];
	char s[] = "点我下班";
	char s1[] = "普通客户取号";
	char s2[] = "VIP客户取号";
	char s3[] = "暂停窗口";
	char s4[] = "策略转换";
	char s5[] = "VIP管理";
	FILE *vipfp;
	char p[20];
    FlushMouseMsgBuffer();                    //清空鼠标消息缓冲区

	                              
	while (1)
	{
		m = GetMouseMsg(); 
		                 //接受鼠标信息
	
		if (m.uMsg == WM_LBUTTONDOWN)    //鼠标左键被按下且营业厅还未准备下班
		{

			if (m.x<=160&&m.y>=730)
			{
				//实现鼠标按下瞬间变换颜色										done
				putimage(0,730,&pu2);
				m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				putimage(0,730,&pu1);
			  if(quit!=0)
			  {
                order = 'G';
				sum_p++;                     //取的号
				Enqueue(Q, sum_p);           //将到达人员写入链表 
																	
				

				wait_p++;                    //排队的人数+1
				//动画数字增加													done

				check_linenump = 1;

				//人走进来等待的动画效果(可以先不做）							undone
			  }
			  else
			  {
				  MessageBox (initial, TEXT ("营业厅已下班，请下次再来\n: )"), TEXT("注意"), 0);
			  }
				
			}

			else if (m.x<=160&&m.y>=690&&m.y<=730)
			{
				//实现鼠标按下瞬间变换颜色
				  //done
				putimage(0,690,&VIPA2);
				m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				//Sleep(200);
				putimage(0,690,&VIPA);
				//setcolor(WHITE);
				//outtextxy(0, 700, s2);
             if(quit!=0)
			 {
				order = 'V';	
				//动画弹窗
				
				InputBox(vID,20,"请输入VIP客户号码","VIP客户");
				printf("%s",vID);
				p[0] = '\0';
				if(strcmp(vID, p) != 0)
				{
                checkvip(vID);
				//三次验证
				sum = 1;
				while ((sum <= 2) && (order == 'G'))
				{
					InputBox(vID,20,"请输入VIP客户号码","VIP客户");
				
					memset(info,0,20*sizeof(char));
					checkvip(vID);
					sum++;
				}
				sum = 1;

				if (order == 'V')
				{
					sum_v++;
					Enqueue(U, sum_v);
					//动画数字增加												undone
					wait_v++;
					check_linenumv = 1;
				}
				else if (order == 'G')
				{
					sum_p++;                     //取的号
					Enqueue(Q, sum_p);           //将到达人员写入链表 
					//动画数字增加												undone
					wait_p++;                    //排队的人数
					check_linenump = 1;
					//人走进来等待的动画效果(可以先不做）						undone
				}

				}
			 }
			 else
			 {
				 MessageBox (initial, TEXT ("营业厅已下班，请下次再来\n: )"), TEXT("注意"), 0);
			 }
			}
			else if (m.x<=160&&m.y>=650&&m.y<=690)
			{
				//实现鼠标按下瞬间变换颜色
				putimage(0,650,&pause2);
			    m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				putimage(0,650,&pause1);
			if(quit !=0)
			{
				order = 'R';
				//弹窗看休息输入休息的窗口
				memset(info,0,20*sizeof(char));																				
				InputBox(info, 20, "请输入要休息的窗口号","暂停窗口");
				sscanf(info,"%d",&n);
				printf("%d",n);
				memset(info,0,20*sizeof(char));	
				pause_order = pause();           
				if(pause_order==0)
				{ n = 0;}
				//判断窗口是否可以休息
				//可以休息的动画以及不可以休息的动画，可以放在pause(n)里面		done
			}
			else
			{
				MessageBox (initial, TEXT ("营业厅已下班\n: )"), TEXT("注意"), 0);
			}
                
			}
			else if (m.x>=1211&&m.y>=687&&m.y<=727)
			{
				//实现鼠标按下瞬间变换颜色				
			
				putimage(1210,690,&VIPG2);
				m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				putimage(1210,690,&VIPG1);
				if(quit !=0)
				{

				InputBox(viporder,5,"输入E			退出维护状态\n输入V+			增加VIP\n输入V-			删除VIP\n输入V/			更新VIP","VIP管理");
				

				order = 'X';
				if ((vipfp = fopen("vip.dat", "rb+")) == NULL)
				{
					printf("无法打开文件！");
					exit(0);
				}
				vipchange(vipfp);                  //里面有输入
				}
				else
				{
					MessageBox (initial, TEXT ("营业厅已下班，已停止维护\n: )"), TEXT("注意"), 0);
				}
				
			}
			else if (m.x>=1211&&m.y>=727)
			{
				//实现鼠标按下瞬间变换颜色	    
				putimage(1210,730,&C2);

 
			    m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				putimage(1210,730,&C1);
            if(quit != 0)
			{
				order = 'C';                        //策略转换
                change = 1;
				if (strategy == 2)
					strategy = 1;                   //变成顺便服务
				else if(strategy ==1)
					strategy = 2;                   //定向服务；
			}
			else
			{
					MessageBox (initial, TEXT ("营业厅已下班\n: )"), TEXT("注意"), 0);
			}
				
               
			}
			else if (m.x>=1270&&m.y<=30)
			{
				//实现鼠标按下瞬间变换颜色
                putimage(1270,2,&linecover1);
                m = GetMouseMsg();
				while(m.uMsg !=  WM_LBUTTONUP )
				{
					m = GetMouseMsg();
				}
				setcolor(WHITE);
	            outtextxy(1270, 0, s);				//输出点我下

				if(quit !=0)
				{
				quit1 = 1;

				order = 'Q';                        //下班了
				quit = 0;
				}
				else
				{
					MessageBox (initial, TEXT ("营业厅正在等待下班\n: )"), TEXT("注意"), 0);
				}

			}
		}
    }
}
