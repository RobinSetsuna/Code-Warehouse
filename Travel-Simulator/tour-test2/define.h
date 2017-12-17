#ifndef DEFINE
#define DEFINE
#define MAX_CITYNUM 12
#define MAX_VEHNUM 248
#define MAXPRICE 1000000
#define INFINITES 1000000

typedef struct{
    int site_name;                             //站点名
    int arrive_time;                           //到达时间 (*日**时（24小时制）百位：0表示当天，1表示次日，2表示次次日)
    int price;                                 //票价
}Site_TimeTable;
typedef struct{
    int veh_type;                              //类型 {0：火车 ，1：汽车，2：飞机}
    int site_num;                              //站点数
    Site_TimeTable time_table[MAX_CITYNUM];    //时刻价格表
}Vehicle;

typedef struct{
    int city;
    int end;//是否是终点或者起点  1-起点 2-中途 3-终点   //终点不能被指，出发点不能指出
    int time;//出发时间
    int veh;
}graphRecord;

typedef struct{
    int time;
    int price;
}cell;

//extern int point_sum;
//extern int city_sta;
//extern int city_end;
//extern int pathway[12];
//extern int strategy;
//extern int limTime;
//extern int start;
//time_t sec_start;
//extern int time_now;
extern int table_col;
extern int sum[2][12];
extern int change;
extern char* city[MAX_CITYNUM];
extern char* way[3];
extern int veh_graph[MAX_CITYNUM][MAX_CITYNUM][10];
extern Vehicle veh[MAX_VEHNUM];
extern int route[5][12];  //站点，到达时间，价格, 方式，班次
extern cell** base_graph;
extern graphRecord *base_record;   //记录每个拆分点的具体信息


#endif // DEFINE

