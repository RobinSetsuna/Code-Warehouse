#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "graphics.h"
#include <conio.h>
#include "header.h"


//初始化队列 
Linkqueue *Initqueue()
{
	Linkqueue* T = (Linkqueue *)malloc(sizeof(Linkqueue));
	if (T != NULL)
	{
		T->front = NULL;
		T->rear = NULL;
	}
	return T;
}


int IsEmpty(Linkqueue *pqueue)  //判断队列是否为空 
{
	if (pqueue->front == NULL&&pqueue->rear == NULL)
		return 1;    //为空 
	else
		return 0;
}



/*将新元素入队尾*/
void Enqueue(Linkqueue *T, int item)
{
	Linknode* pnode = (Linknode*)malloc(sizeof(Linknode));
	if (pnode != NULL)
	{
		pnode->data = item;
		pnode->next = NULL;

		if (IsEmpty(T) == 1)
		{
			T->front = pnode;
		}
		else
		{
			if (T->rear == NULL)
			{
				T->front->next = pnode;
				T->rear = pnode;
			}
			else
			{
				T->rear->next = pnode;
				T->rear = pnode;
			}
		}
	}
}

/*队头元素出队*/
int Dlqueue(Linkqueue *T)
{
	Linknode* pnode = T->front;
	int item;
	if (pnode != NULL)              //队列不为空 
	{
		item = pnode->data;
		T->front = pnode->next;
		free(pnode);
		return item;
	}
	else
	{
		T->rear = NULL;
		return 0;
	}
}

int p_judge()
{
	int i = 0, j = 0;
	for (i = 0; i <= 5; i++)
	{
		if (servep[i].state != CLOSED&&servep[i].state != PAUSED)
		{
			j++;
		}
	}
	if (3 * j == wait_p&&j<6)
		return 1;
	else if (wait_p<2 * j&&j>3)
		return 2;
	else return 0;
}
int v_judge()
{
	if (wait_v >= 3)
	{
		rtime = 0;
		if (wait_v>3)
		{
			return 1;
		}
	}
	else if (wait_v<3)
	{
		rtime = suretime() - rtime;
		if (rtime> VIPSERVLen)
		{
			return 2;
		}
	}
	return 0;
}
int def()
{
	int i;
	for (i = 0; i <= 2; i++)
	{
		if (servep[i].state != FREE)
		{
			return 1;
		}
	}
	for (i = 3; i <= 5; i++)
	{
		if (servep[i].state != CLOSED)
		{
			return 1;
		}
	}
	if (servev[0].state != FREE)
	{
		return 1;
	}
	if (servev[1].state != CLOSED)
	{
		return 1;
	}
	return 0;

}

int pause()
{
	
	int i = 0, j = 0, count1 = 0, count2 = 0;

	if (n <= 6 && n >= 1)
	{
		if (servep[n - 1].state == CLOSED)
		{
			//printf("窗口未开放，无法暂停\n");
			//动画弹窗
			MessageBox (initial, TEXT ("窗口未开放，无法暂停\n: )"), TEXT("注意"), 0);
			
			return 0;
		}
		else if (servep[n - 1].state == PAUSED)
		{
			//printf("窗口已暂停\n");
			//动画弹窗
			MessageBox (initial, TEXT ("窗口已暂停\n: )"), TEXT("注意"), 0);
			return 0;
		}
		else
		{
			for (i = 0; i <= 5; i++)
			{
				if (servep[i].state != CLOSED&&servep[i].state != PAUSED)
				{
					count1++;
				}
			}
			count1 = count1 - waitpn;
			if (count1 >= 4)
			{
				if (servep[n - 1].state == BUSY)
					return 3;    //这个申请的窗口等待暂停 
				else if (servep[n - 1].state == FREE)
					return 1;
				else
					return 0;
			}
			else if (count1 < 4)
			{
				MessageBox (initial, TEXT ("未达到暂停条件，无法暂停\n: )"), TEXT("注意"), 0);
				return 0;
			}
				
		}
	}
	else if (n >= 7 && n <= 8)
	{
		for (i = 0; i <= 1; i++)
		{
			if (servev[i].state != CLOSED&&servev[i].state != PAUSED)
			{
				count2++;
			}
		}
		count2 = count2 - waitvn;
		if (count2 == 2)
		{
			if (servev[n - 7].state == BUSY)
				return 3;
			else if (servev[n - 7].state == FREE)
				return 1;
			else
				return 0;
		}
		else if (count2<2)
		{	
			MessageBox (initial, TEXT ("未达到暂停条件，无法暂停\n: )"), TEXT("注意"), 0);
			return 0;
		}
		
	}

		return 0;
}
int def2()
{
	int i;
	for(i=0;i<=5;i++)
	{
		if( servep[i].state ==FREE)
		{return 0;}
	}
	return 1;

}