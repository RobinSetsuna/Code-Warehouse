#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"


void output()
{

	int i, j;
	FILE *ftp;

	if ((ftp = fopen("ouput.txt", "w")) == NULL)
	{
		printf("无法打开文件！");
		exit(0);
	}

	while (1)
	{
		Sleep(500);
		fprintf(ftp, "------------------------欢迎来到中国银行！---------------------\n");
		fprintf(ftp, "当前时间：%d\n", recordtime);
		fprintf(ftp, "当前普通用户排队人数:%d		", wait_p);
		fprintf(ftp, "当前VIP用户排队人数:%d\n", wait_v);

		fprintf(ftp, "当前普通用户服务人数:%d		", servepnumber);
		fprintf(ftp, "当前VIP用户服务人数:%d	", servevnumber);
		fprintf(ftp, "\n");

		fprintf(ftp, "当前窗口				窗口状态				窗口服务号码\n");
		for (i = 1; i <= 6; i++)
		{
			switch (servep[i - 1].state)
			{
			case 0:
				fprintf(ftp, "窗口%d					%s						%d\n", i, "FREE", servep[i - 1].servenum);
				break;
			case 1:
				fprintf(ftp, "窗口%d					%s						%d\n", i, "BUSY", servep[i - 1].servenum);
				break;
			case 2:
				fprintf(ftp, "窗口%d					%s						%d\n", i, "PAUSED", servep[i - 1].servenum);
				break;
			case 3:

				fprintf(ftp, "窗口%d					%s						%d\n", i, "CLOSED", servep[i - 1].servenum);
				break;
			}
		}
		for (j = 1; j <= 2; j++)
		{
			switch (servev[j - 1].state)
			{
			case 0:
				fprintf(ftp, "窗口%d					%s						%d\n", j + 6, "FREE", servev[j - 1].servenum);
				break;
			case 1:
				fprintf(ftp, "窗口%d					%s						%s%d\n", j + 6, "BUSY", "V", servev[j - 1].servenum);
				break;
			case 2:
				fprintf(ftp, "窗口%d					%s						%d\n", j + 6, "PAUSED", servev[j - 1].servenum);
				break;
			case 3:
				fprintf(ftp, "窗口%d					%s						%d\n", j + 6, "CLOSED", servev[j - 1].servenum);
				break;
			case 4:
				fprintf(ftp, "窗口%d					%s						%d\n", j + 6, "BUSY", servev[j - 1].servenum);
				break;

			}
		}
		
			printrecord(ftp);
	}
	fclose(ftp);
	
}

void printrecord(FILE* pt)
{
	int k, temp1, temp2, temp3;
	fprintf(pt, "统计数据如下:\n");
	fprintf(pt, "营业厅受理的普通客户:%d			营业厅受理的VIP客户:%d\n", sum_p, sum_v);
	fprintf(pt, "窗口号				办理的客户总数			总业务时长			平均业务时长\n");
	for (k = 0; k <= 7; k++)
	{
		temp1 = record[k].totaltime;
		temp2 = record[k].totalnum;
		if (temp2 == 0)
			temp3 = 0;
		else
			temp3 = (temp1 / temp2);

		fprintf(pt, "窗口%d				%d				%d				%d\n", (k + 1), record[k].totalnum, record[k].totaltime, temp3);

	}

	fprintf(pt, "\n");
	
}