#include"define.h"

//int point_sum;
//int city_sta;
//int city_end;
//int pathway[12];
//int strategy;
//extern int limTime;
//int start;
//time_t sec_start;
//int time_now;
int table_col;
int sum[2][12];
int change;
char* city[MAX_CITYNUM];
char* way[3];
int veh_graph[MAX_CITYNUM][MAX_CITYNUM][10];
Vehicle veh[MAX_VEHNUM];
int route[5][12];  //站点，到达时间，价格, 方式，班次
cell** base_graph;
graphRecord *base_record;   //记录每个拆分点的具体信息
