#include "widget.h"
#include "ui_widget.h"
#include"define.h"
#include<QDebug>
#include<QFile>
#include<QTextCodec>
#include<QString>
#include<QMessageBox>


int Widget::baseGraph()
{
    int record[2][12];
    int i,j,k,n,m,order,city1,city2;
    int interval,time1,time2,time_sta,time_end;
    int point_sum;

    point_sum=city_sum();

    base_graph=(cell**)malloc(sizeof(cell*)*point_sum);
    for(i=0;i<point_sum;i++)
        base_graph[i]=(cell*)malloc(sizeof(cell)*point_sum);

    base_record=(graphRecord*)malloc(sizeof(graphRecord)*point_sum);


    for(i=0;i<point_sum;++i)//初始化基本图 为INFINITE
        for(j=0;j<point_sum;++j)
        {
            base_graph[i][j].price=INFINITES;
            base_graph[i][j].time=INFINITES;
        }



    record[0][0]=0;record[1][0]=0;
    for(i=1;i<12;++i)
    {
        record[0][i]=record[0][i-1]+sum[0][i-1];
        record[1][i]=record[0][i];
    }

    for(i=0;i<12;++i)
    {
        for(j=0;j<12;++j)
        {
            for(k=0;k<veh_graph[i][j][0];++k)
            {
                order=veh_graph[i][j][k+1];
                for(n=0;n<veh[order].site_num;++n)  //一条线路；
                {
                    city1=veh[order].time_table[n].site_name;
                    time1=veh[order].time_table[n].arrive_time;
                    time_sta=(time1%10)+(time1/10)%10*10;
                    if(n!=veh[order].site_num-1)
                    {
                        city2=veh[order].time_table[n+1].site_name;
                        time2=veh[order].time_table[n+1].arrive_time;
                        time_end=(time2%10)+(time2/10)%10*10;
                        if(((time1/100)%10)!=((time2/100)%10))
                        {
                            interval=24*((time2/100)%10-(time1/100)%10-1)+24-time_sta+time_end;
                        }
                        else
                            interval=(time_end-time_sta+24)%24;

                        base_graph[record[0][city1]][record[0][city2]].time=interval;
                        base_graph[record[0][city1]][record[0][city2]].price=veh[order].time_table[n+1].price;

                        if(n!=0)
                            base_record[record[0][city1]].end=2;
                        else
                            base_record[record[0][city1]].end=1;
                    }
                    else
                    {
                        base_record[record[0][city1]].end=3;
                    }

                    base_record[record[0][city1]].city=city1;
                    base_record[record[0][city1]].veh=order;
                    base_record[record[0][city1]].time=time_sta;

                    if(record[0][city1]!=record[1][city1])
                    {
                        for(m=1;m<=(record[0][city1]-record[1][city1]);++m)
                        {
                            if(base_record[record[0][city1]].end!=1&&base_record[record[0][city1]-m].end!=3)    //当前点到其他点的等待时间
                            {
                                base_graph[record[0][city1]][record[0][city1]-m].time=(base_record[record[0][city1]-m].time-time_sta+24)%24;
                                base_graph[record[0][city1]][record[0][city1]-m].price=0;
                            }


                            if(base_record[record[0][city1]].end!=3&&base_record[record[0][city1]-m].end!=1)    //其他点到当前点的等待时间
                            {
                                base_graph[record[0][city1]-m][record[0][city1]].time=(time_sta-base_record[record[0][city1]-m].time+24)%24;
                                base_graph[record[0][city1]-m][record[0][city1]].price=0;
                            }

                        }
                    }
                }

                for(n=0;n<veh[order].site_num;++n)
                {
                    city1=veh[order].time_table[n].site_name;
                    record[0][city1]++;
                }
            }
        }
    }

    return point_sum;
}

int Widget::city_sum(void)
{
    int i,j,k,order,n;
    int my_city;
    for(i=0;i<12;++i)
    {
        sum[0][i]=0;
        sum[1][i]=0;
    }


    for(i=0;i<12;++i)
    {
        for(j=0;j<12;++j)
        {
            for(k=0;k<veh_graph[i][j][0];++k)
            {
                order=veh_graph[i][j][k+1];
                if(veh[order].veh_type!=0)
                {
                    my_city=veh[order].time_table[0].site_name;
                    sum[0][my_city]++;
                    my_city=veh[order].time_table[1].site_name;
                    sum[0][my_city]++;
                }
                else
                {
                    for(n=0;n<veh[order].site_num;++n)
                    {
                        my_city=veh[order].time_table[n].site_name;
                        sum[0][my_city]++;
                    }
                }
            }
        }
    }

    my_city=0;
    for(i=0;i<12;++i)
        my_city=my_city+sum[0][i];


    sum[1][0]=0;
    for(i=1;i<12;++i)
    {
        sum[1][i]=sum[1][i-1]+sum[0][i-1];
    }

    return my_city;
}

int Widget::S1()
{
    int i,j,k;
    int **my_graph;
    int *min_route;
    int time;
    int minTime;

    k=1;
    for(i=1;i<=city_num;++i)   k=2*k; //计算要添加的图的个数

    my_graph=(int**)malloc(sizeof(int*)*(point_sum*k+2));//创建用户图   倒数第二个为出发点，倒数第一个为终点
    for(i=0;i<point_sum*k+2;i++)
        my_graph[i]=(int*)malloc(sizeof(int)*(point_sum*k+2));

    for(i=0;i<point_sum*k+2;++i)//初始化用户图为 INFINITE
        for(j=0;j<point_sum*k+2;++j)
            my_graph[i][j]=INFINITES;

    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)//出发点
    {
        if(base_record[i].end!=3)
        {
            j=base_record[i].time;
            my_graph[point_sum*k][i]=0;
        }

    }

    for(i=sum[1][city_end];i<sum[1][city_end+1];++i) //终点
    {
        if(base_record[i].end!=1)
        {
            j=base_record[i].time;
            my_graph[point_sum*k-1][i+((k-1)*point_sum)]=0;

        }
    }
    S1_create_graph(my_graph);//创建用户图

    //调用最短路径算法，起始点为 point_sum*k，终点为point_sum*k-1,
    min_route=(int*)malloc(sizeof(int)*100);  //传入到最短路径算法中，用来记录算法得到的数据
    for(i=0;i<100;++i)
        min_route[i]=-1;

    //调用最短路径算法，传入的参数为  min_route；
    minTime=S1_S2_MinStrategy(my_graph,point_sum*k+2,min_route,k);

    //处理min_route的数据  返回城市个数
    i=S1_S2_route(min_route,my_graph,minTime,1);
    return i;
}



int Widget::S2()
{
    int i,j,k;
    int **my_graph;
    int *min_route;
    int time,pre_city,now_city,next_city;
    int minTime;

    k=1;
    for(i=1;i<=city_num;++i)   k=2*k; //计算要添加的图的个数

    my_graph=(int**)malloc(sizeof(int*)*(point_sum*k+2));//创建用户图   倒数第二个为出发点，倒数第一个为终点
    for(i=0;i<point_sum*k+2;i++)
        my_graph[i]=(int*)malloc(sizeof(int)*(point_sum*k+2));

    for(i=0;i<point_sum*k+2;++i)//初始化用户图为 INFINITE
        for(j=0;j<point_sum*k+2;++j)
            my_graph[i][j]=INFINITES;

    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)//出发点
    {
        if(base_record[i].end!=3)
        {
            j=base_record[i].time;
            my_graph[point_sum*k][i]=(j-time_now+24)%24;

        }

    }

    for(i=sum[1][city_end];i<sum[1][city_end+1];++i) //终点
    {
        if(base_record[i].end!=1)
        {
            j=base_record[i].time;
            my_graph[point_sum*k-1][i+((k-1)*point_sum)]=0;

        }
    }

    S2_create_graph(my_graph);//创建用户图

    //调用最短路径算法，起始点为 point_sum*k，终点为point_sum*k-1,
    min_route=(int*)malloc(sizeof(int)*100);  //传入到最短路径算法中，用来记录算法得到的数据
    for(i=0;i<100;++i)
       min_route[i]=-1;

    //调用最短路径算法，传入的参数为  min_route；
    minTime=S1_S2_MinStrategy(my_graph,point_sum*k+2,min_route,k);

    //处理min_route的数据  返回城市个数
    i=S1_S2_route(min_route,my_graph,minTime,2);

    return i;
}



void Widget::S1_create_graph(int** graph)
{
    int i, j, k,floor_sum,f,m,n,n1,n2;
    int a[2][city_num+1];
    int** point;

    for(i=0;i<2;++i)
    {
        for(j=0;j<city_num+1;++j)
        {
            a[i][j]=0;
        }
    }


    floor_sum=0;
    for(i=0;i<city_num+1;++i)
    {
        k=combination(city_num,i); //每层几个
        a[0][i]=k;
        floor_sum=floor_sum+a[0][i];
    }

    a[1][0]=0;
    for(i=1;i<city_num+1;++i)
       a[1][i]=a[1][i-1]+a[0][i-1];

    point=(int**)malloc(sizeof(int*)*(city_num+1));
    for(i=0;i<floor_sum;i++)
        point[i]=(int*)malloc(sizeof(int)*floor_sum);

    for(i=0;i<city_num+1;++i)
       for(j=0;j<floor_sum;++j)
       {
          if(i==0)
             point[0][j]=city_num;
          else
             point[i][j]=0;
       }

    f=0;
    for(i=0;i<city_num+1;++i)
    {
        for(j=0;j<a[0][i];++j)
        {
            if(i+1<city_num+1){

            n=a[1][i+1];
            for(k=0;k<point[0][f];++k)
            {
                m=1;
                while(point[m][f]==1)   ++m;

                while(point[m][n]==1)
                {
                    ++n;
                    if(n>=a[1][i+2])
                        n=a[1][i+1];
                }

                //第f点->第n个点（0开始）  填pathway的第 m（ 1开始）个城市
                n2=n*point_sum+sum[1][pathway[m]];
                for(n1=f*point_sum+sum[1][pathway[m]];n1<f*point_sum+sum[1][pathway[m]+1];++n1,++n2)
                {
                    graph[n1][n2]=0;
                }

                point[m][f]=1;
                point[m][n]=1;
                point[0][n]--;

                ++n;
                if(n>=a[1][i+2])
                    n=a[1][i+1];

            }
            ++f;
            }
        }
    }

    k=1;
    for(i=0;i<city_num;++i)   k=k*2;

    for(i=0;i<k;++i)
    {
        for(j=i*point_sum;j<(i+1)*point_sum;++j)
        {
            for(n=i*point_sum;n<(i+1)*point_sum;++n)
            {
                graph[j][n]=base_graph[j%point_sum][n%point_sum].price;

            }


        }
    }

    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)
    {
        for(j=sum[1][city_sta];j<sum[1][city_sta+1];++j)
        {
            graph[i][j]=INFINITES;
        }
    }

}


void Widget::S2_create_graph(int** graph)
{
    int i, j, k,floor_sum,f,m,n,n1,n2;
    int a[2][city_num+1];
    int** point;

    for(i=0;i<2;++i)
    {
        for(j=0;j<city_num+1;++j)
        {
            a[i][j]=0;
        }
    }


    floor_sum=0;
    for(i=0;i<city_num+1;++i)
    {
        k=combination(city_num,i); //每层几个
        a[0][i]=k;
        floor_sum=floor_sum+a[0][i];
    }

    a[1][0]=0;
    for(i=1;i<city_num+1;++i)
       a[1][i]=a[1][i-1]+a[0][i-1];

    point=(int**)malloc(sizeof(int*)*(city_num+1));
    for(i=0;i<floor_sum;i++)
        point[i]=(int*)malloc(sizeof(int)*floor_sum);

    for(i=0;i<city_num+1;++i)
       for(j=0;j<floor_sum;++j)
       {
          if(i==0)
             point[0][j]=city_num;
          else
             point[i][j]=0;
       }

    f=0;
    for(i=0;i<city_num+1;++i)
    {
        for(j=0;j<a[0][i];++j)
        {
            if(i+1<city_num+1){

            n=a[1][i+1];
            for(k=0;k<point[0][f];++k)
            {
                m=1;
                while(point[m][f]==1)   ++m;

                while(point[m][n]==1)
                {
                    ++n;
                    if(n>=a[1][i+2])
                        n=a[1][i+1];
                }

                //第f点->第n个点（0开始）  填pathway的第 m（ 1开始）个城市
                n2=n*point_sum+sum[1][pathway[m]];
                for(n1=f*point_sum+sum[1][pathway[m]];n1<f*point_sum+sum[1][pathway[m]+1];++n1,++n2)
                {
                    graph[n1][n2]=0;
                }

                point[m][f]=1;
                point[m][n]=1;
                point[0][n]--;

                ++n;
                if(n>=a[1][i+2])
                    n=a[1][i+1];

            }
            ++f;
            }
        }
    }

    k=1;
    for(i=0;i<city_num;++i)   k=k*2;

    for(i=0;i<k;++i)
    {
        for(j=i*point_sum;j<(i+1)*point_sum;++j)
        {
            for(n=i*point_sum;n<(i+1)*point_sum;++n)
            {
                graph[j][n]=base_graph[j%point_sum][n%point_sum].time;

            }


        }
    }

    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)
    {
        for(j=sum[1][city_sta];j<sum[1][city_sta+1];++j)
        {
            graph[i][j]=INFINITES;
        }
    }

}


int Widget::combination(int n, int m)//从n个里选m个
{
    int i;
    int result, k1, k2, k3;

    k1=1,k2=1,k3=1;
    for(i=1;i<=n;++i)  k1=k1*i;
    for(i=1;i<=(n-m);++i)  k2=k2*i;
    for(i=1;i<=m;++i)   k3=k3*i;

    result=k1/(k2*k3);
    return result;
}

int Widget::S1_S2_MinStrategy(int **graph,int pointsum,int *path,int k)  //dijkstra算法 (最小时间)
{
    //point_sum*k+2
    int **p,*d,*s,*final;
    int v,w,i,j,min;
    int found,final_city;
    int base_sum;
    base_sum=point_sum;

    d=(int *)malloc(sizeof(int)*(pointsum));     //源点到各点之间的路径长度。
    s=(int *)malloc(sizeof(int)*(pointsum));
    final=(int *)malloc(sizeof(int)*(pointsum));
    p=(int**)malloc(sizeof(int*)*(pointsum));   //表示某点是不是源点到另一点的最短路径上的点。
    for(i=0;i<pointsum;i++)
    {
        p[i]=(int*)malloc(sizeof(int)*(pointsum));
    }

    for(v=0;v<pointsum;v++) //初始化
    {
        final[v]=0;
        d[v]=graph[pointsum-2][v];
        for(w=0;w<pointsum;w++)
        {
            p[v][w]=0;
        }
        if(d[v]<INFINITES)
        {
            p[v][pointsum-2]=1;
            p[v][v]=1;
        }
    }
    d[pointsum-2]=0;
    final[pointsum-2]=1;
    s[0]=1;
    s[1]=pointsum-2;

    found=0,final_city=0;
    while(!final[pointsum-1]&&s[0]<=pointsum&&found==0)
    {
        min=INFINITES;
        for(w=0;w<pointsum;w++)
        {
            if(!final[w])
            {

                if(d[w]<min)
                {
                    v=w;
                    min=d[w];
                }
            }
        }
        final[v]=1;

        ++s[0];
        s[s[0]]=v;
        for(w=0;w<pointsum&&v<pointsum;w++)
        {
            if((!final[w])&&(min+graph[v][w]<=d[w]))
            {
                d[w]=min+graph[v][w];
                p[w][v]=1;
            }
        }

        for(i=sum[1][city_end]+(k-1)*base_sum;i<sum[1][city_end+1]+(k-1)*base_sum;++i)
        {
            if(final[i]==1)
            {
                found=1;
                break;
            }

        }

    }

    path[0]=1;
    path[1]=i;
    j=s[0];
    while(j>1)
    {
        i=j-1;
        while(i>=1)
        {
            if(p[s[j]][s[i]]==1)
            {
                path[++path[0]]=s[i];
                j=i;
                break;
            }
            else
            {
                i--;
            }
        }
    }
    return path[0];
}


//处理min_route的数据
int Widget::S1_S2_route(int* m_route,int**my_graph,int minTime,int strategy)
{
    int i,j,k,n,time;
    int pre_city,now_city,next_city,price;
    int **min_route;

    min_route=(int**)malloc(sizeof(int)*2);
    for(i=0;i<2;++i)
       min_route[i]=(int*)malloc(sizeof(int)*minTime);

    for(i=0;i<minTime;++i)
    {
        min_route[0][i]=m_route[minTime-i];
        min_route[1][i]=min_route[0][i];
        if(i!=0)
        {
            while(min_route[1][i]>=point_sum)
               min_route[1][i]=min_route[1][i]-point_sum;
        }
    }

    clean();
    i=0,j=0;
    pre_city=-1, time=time_now, price=0;
    while(i<minTime)
    {
        if(i!=0)
        {
            if(i!=1)
            {
                if(strategy==2&&my_graph[min_route[0][i-1]][min_route[0][i]]!=INFINITES)
                {
                    time=time+my_graph[min_route[0][i-1]][min_route[0][i]];
                }
                else if(strategy==1)
                {
                    if(min_route[1][i-1]==min_route[1][i])
                    {
                        time=time+0;
                    }
                    else if(base_graph[min_route[1][i-1]][min_route[1][i]].time!=INFINITES)
                    {
                        time=time+base_graph[min_route[1][i-1]][min_route[1][i]].time;
                    }

                }

            }
            now_city=base_record[min_route[1][i]].city;//route[5][12];  //站点，到达时间，价格, 方式，班次
        }
        else
        {
            now_city=base_record[min_route[1][1]].city;
            if(strategy==2)
            {
                time=time+my_graph[min_route[0][0]][min_route[0][1]];
            }
            else if(strategy==1)
            {
                time=time+(base_record[min_route[0][1]].time-time_now+24)%24;
            }

        }

        if(((time%10)+(time/10)%10*10)>24)
        {
            time=((time%10)+(time/10)%10*10)-24+((time/100)%100+1)*100;
        }

        if(now_city!=pre_city)
        {
            route[0][j]=now_city;
            route[1][j]=time;
            if(i!=minTime-1)
            {
                next_city=base_record[min_route[1][i+1]].city;
                if(now_city==next_city)
                {

                    n=i+1;
                    while(now_city==next_city&&n<minTime)
                    {
                        n++;
                        next_city=base_record[min_route[1][n]].city;
                    }
                    route[4][j]=base_record[min_route[1][n-1]].veh;
                }

                else
                {
                    route[4][j]=base_record[min_route[1][i]].veh;
                    n=i+1;
                }

                route[3][j]=veh[route[4][j]].veh_type;

                for(k=0;k<veh[route[4][j]].site_num;++k)
                {
                    if(veh[route[4][j]].time_table[k].site_name==base_record[min_route[1][n]].city)
                    {
                        price=veh[route[4][j]].time_table[k].price;
                        break;
                    }
                }

                route[2][j]=price;
            }

                ++j;
        }
        ++i;
        pre_city=now_city;
    }

    return j;//城市个数
}


