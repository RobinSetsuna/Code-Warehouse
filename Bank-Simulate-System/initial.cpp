#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"




void initial()
{
	int i, j, k;

	wait_p = 0; wait_v = 0; sum_p = 0; wait_v = 0; n = 10; rtime = 0; sum_v = 0; servepnumber = 0; servevnumber = 0;
	p_extraorder = 0; v_extraorder = 0; recordtime = 0; pause_order = 0; waitpn = 0; waitvn = 0;
	for (i = 0; i <= 7; i++)
	{
		flag3[i] = 0;
	}
	Q = Initqueue();                 //初始化普通顾客队列 
	U = Initqueue();                 //初始化VIP客户队列 


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

	for (k = 0; k <= 7; k++)
	{
		record[k].totalnum = 0;
		record[k].totaltime = 0;
	}
}


