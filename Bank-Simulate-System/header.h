#ifndef _HEADER_H_
#define _HEADER_H_
#define FREE 0
#define BUSY 1
#define PAUSED 2
#define CLOSED 3
#define PBUSY 4

//结构体声明
typedef struct
{
	char name[20];
	char ID[20];
	int money;
}VIPDATA;

typedef struct{
	int state;
	time_t endwork;							//结束工作的时间 
	int  servenum;							//这个窗口服务或者等待的顾客号码 
}serve_p;

typedef struct{
	int state;
	time_t endwork;							//结束工作的时间 
	int servenum;							//正在服务的顾客号码 
}serve_v;
								
struct Linknode{
	int data;                
	struct Linknode *next;
};
typedef struct Linknode Linknode;

struct Linkqueue{							//链式存储的等待队列的类型定义 
	struct Linknode *front;
	struct Linknode *rear;
};
typedef struct Linkqueue Linkqueue;

typedef struct
{
	int totalnum;
	int totaltime;
}RECORD;

//函数声明
extern int p_judge();						//判断是否新开普通窗口
extern int v_judge();						//判断是否新开VIP窗口
extern void closeserve_p();					//将新开的普通窗口关闭
extern void closeserve_v();					//将新开的VIP窗口关闭
extern void checkvip(char[20]);             //判断是否为VIP 客户 
extern void vipchange(FILE*);				//VIP维护函数
extern int pause();						//休息指令通过了之后关闭休息的窗口，如果（同时传入休息指令
extern time_t timerandom(int);              //产生随机服务时间 
extern void state_change();				//状态机
extern void output();						//文件输出
extern time_t suretime();					
extern Linkqueue* Initqueue();
extern int IsEmpty(Linkqueue *);			//判断队列是否为空
extern void Enqueue(Linkqueue *, int);
extern int Dlqueue(Linkqueue*);
extern int def();							//判断增添窗口的函数 
extern void printrecord(FILE*);					//输出统计信息
extern void input();						//输入线程函数
extern void newwin();						//欢迎界面窗口初始化					
extern void winimg();						//银行界面初始化
extern void draw(int,int);					//普通窗口状态图形输出
extern void linenum();						//排队状态信息输出
extern void draw2(int,int);					//VIP窗口状态图形输出	
extern void closeimg();						//银行关闭界面
extern void drawservenumv(int,int);
extern void drawservenump(int);
extern void changeBay();
extern int def2();


//变量声明
extern int MinSec;							//最短服务时间
extern int MaxSec;							//最长服务时间
extern int MinRestSec;						//最短休息时间
extern int MaxRestSec;						//最长休息时间
extern int VIPSERVLen;						//VIP排队长度
extern int v_extraorder, p_extraorder;		//判断是否需要增开窗口
extern int sum_p, wait_p, sum_v, wait_v;	//记录普通,VIP的排队人数和进入营业厅的总人数
extern int n;								//要暂停的窗口参数
extern int servepnumber, servevnumber;
extern int pause_order;
extern int waitpn, waitvn;					//正在等待休息的普通窗口和VIP窗口数量
extern int flag3[8];					
extern int quit;							//判断是否有以下班指令发出来
extern int strategy;						//VIP窗口的服务策略
extern int sum;								//验证VIP循环3次参数
extern int check_linenump,check_linenumv;
extern char viporder[5];
extern char str1[20];
extern char str2[20];
extern char order;
extern RECORD record[8];					//8个窗口的记录信息
extern serve_v servev[2];					//两个VIP窗口     
extern serve_p servep[6];					//六个普通窗口 
extern Linkqueue *Q;						//普通客户的队列 
extern Linkqueue *U;						//VIP客户的队列 
extern time_t rest_time_p[6];				//存普通窗口的休息时间
extern time_t rest_time_v[2];				//存VIP窗口的休息时间
extern time_t start, recordtime, rtime,uu;
extern MOUSEMSG m;							//接收鼠标信息结构体
extern IMAGE img3,img,img1,VIPA2,VIPA,pu1,pu2,pause1,pause2,VIPG1,VIPG2,C1,C2;					//存覆盖图的IMAGE指针
extern IMAGE cover1,cover2,cover3,cover4,cover5,cover6,cover7,cover8;
extern IMAGE baycover1,baycover2,baycover3,baycover4,linecover1,linecover2,timecover;
extern int change,quit1;
extern char s6[],s7[],s8[];
extern HWND initial;
extern time_t tt;
extern struct tm *t;
extern char ss[100];
#endif




