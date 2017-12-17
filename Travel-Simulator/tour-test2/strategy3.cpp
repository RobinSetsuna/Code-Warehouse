#include "widget.h"
#include "ui_widget.h"
#include"define.h"
#include<QDebug>
#include<QFile>
#include<QTextCodec>
#include<QString>
#include<QMessageBox>

int Widget::S3()
{
    int i,j,k;
    cell **my_graph;
    int *min_route;
    int time,pre_city,now_city,next_city;
    int num,minTime;;

    num=S1(); //调用策略一
    time=total_time(num);

    if(time<=limTime)
    {
        //print(num);
        //显示
        return 0;
    }

    num=S2();//调用策略二
    time=total_time(num);

    if(time>limTime)
    {
        //printf("不存在时间<=%d的路径\n",lim);
        QString s = QString::number(time, 10);
        QMessageBox::warning(this,tr("Warning"),"不存在时间<="+s+"的路径!",QMessageBox::Yes);
        return 0;
    }


    //路径存在
    k=1;
    for(i=1;i<=city_num;++i)   k=2*k; //计算要添加的图的个数

    my_graph=(cell**)malloc(sizeof(cell*)*(point_sum*k+2));//创建用户图   倒数第二个为出发点，倒数第一个为终点
    for(i=0;i<point_sum*k+2;i++)
        my_graph[i]=(cell*)malloc(sizeof(cell)*(point_sum*k+2));

    for(i=0;i<point_sum*k+2;++i)//初始化用户图为 INFINITE
        for(j=0;j<point_sum*k+2;++j)
        {
            my_graph[i][j].price=INFINITES;
            my_graph[i][j].time=INFINITES;
        }


    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)//出发点
    {
        if(base_record[i].end!=3)
        {
            j=base_record[i].time;
            my_graph[point_sum*k][i].time=(j-time_now+24)%24;
            my_graph[point_sum*k][i].price=0;
        }

    }
    for(i=sum[1][city_end];i<sum[1][city_end+1];++i) //终点
    {
        if(base_record[i].end!=1)
        {
            j=base_record[i].time;
            my_graph[i+((k-1)*point_sum)][point_sum*k+1].price=0;
            my_graph[i+((k-1)*point_sum)][point_sum*k+1].time=0;
        }
    }

    S3_create_graph(my_graph);//创建用户图

    min_route=(int*)malloc(sizeof(int)*100);  //传入到最短路径算法中，用来记录算法得到的数据
    for(i=0;i<100;++i)
       min_route[i]=-1;

    minTime=S3_MinStrategy(my_graph,point_sum*k+2,min_route,k,limTime);

    table_col=S3_route(min_route,my_graph,minTime);
    //print(i);
    return table_col;
}



int Widget::total_time(int city_num)
{
    int i;
    int time;

    time=route[1][city_num-1];
    if((time/100)%100!=0)
    {
        time=((time/100)%100-1)*24+(time%10)+(time/10)%10*10+24-time_now;
    }
    else
    {
        time=((time%10)+(time/10)%10*10-time_now+24)%24;
    }
    return time;
}


void Widget::S3_create_graph(cell** graph)
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
                    graph[n1][n2].time=0;
                    graph[n1][n2].price=0;
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
                graph[j][n].time=base_graph[j%point_sum][n%point_sum].time;
                graph[j][n].price=base_graph[j%point_sum][n%point_sum].price;

            }


        }
    }

    for(i=sum[1][city_sta];i<sum[1][city_sta+1];++i)
    {
        for(j=sum[1][city_sta];j<sum[1][city_sta+1];++j)
        {
            graph[i][j].time=INFINITES;
            graph[i][j].price=INFINITES;
        }
    }
}



int Widget::S3_MinStrategy(cell **graph,int pointsum,int *path,int k,int lim)  //dijkstra算法 (最小时间)
{
    //point_sum*k+2
    int **p,*d,*s,*final,*flag;
    int v,w,i,j,min,city_sum;
    int found,final_city,price,time,price_min;
    int temp[100];
    int base_sum;
    base_sum=point_sum;
    d=(int *)malloc(sizeof(int)*(pointsum));                    //源点到各点之间的路径长度。
    s=(int *)malloc(sizeof(int)*(pointsum));
    final=(int *)malloc(sizeof(int)*(pointsum));
    p=(int**)malloc(sizeof(int*)*(pointsum));                   //表示某点是不是源点到另一点的最短路径上的点
    for(i=0;i<pointsum;i++)
    {
        p[i]=(int*)malloc(sizeof(int)*(pointsum));
    }


    city_sum=sum[1][city_end+1]+(k-1)*base_sum-sum[1][city_end]+(k-1)*base_sum;
    flag=(int *)malloc(sizeof(int)*(city_sum));
    for(i=0;i<city_sum;i++)
    {
        flag[i]=0;
    }

    for(v=0;v<pointsum;v++)                         //初始化
    {
        final[v]=0;
        d[v]=graph[pointsum-2][v].time;//
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

    price_min=INFINITES;
    while(s[0]<=pointsum&&found==0)
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
        for(w=0;w<pointsum;w++)
        {
            if((!final[w])&&(min+graph[v][w].time<=d[w]))
            {
                d[w]=min+graph[v][w].time;
                p[w][v]=1;
            }
        }

        for(i=sum[1][city_end]+(k-1)*base_sum;i<sum[1][city_end+1]+(k-1)*base_sum;++i)
        {
            if(final[i]==1&&flag[i-(sum[1][city_end]+(k-1)*base_sum)]==0)
            {
                flag[i-(sum[1][city_end]+(k-1)*base_sum)]=1;
                --city_sum;
                price=0,time=0;
                w=i;
                temp[0]=1;
                temp[1]=w;
                j=s[0];
                while(j>1)
                {
                    w=j-1;
                    while(w>=1)
                    {
                        if(p[s[j]][s[w]]==1)
                        {
                            temp[++temp[0]]=s[w];
                            j=w;
                            break;
                        }
                        else
                        {
                            w--;
                        }
                    }
                }

                for(j=temp[0];j>1;--j)
                {
                    time=graph[temp[j]][temp[j-1]].time+time;
                    price=graph[temp[j]][temp[j-1]].price+price;
                }
                if(time<=lim&&price<price_min)
                {
                    price_min=price;
                    for(j=0;j<=temp[0];++j)
                    {
                        path[j]=temp[j];
                    }
                }

                break;
            }
        }

        if(city_sum==0)
        {
            found=1;
        }

    }
    return path[0];
}


int Widget::S3_route(int* m_route,cell**my_graph,int minTime)
{
    int i,j,k,n,time;
    int pre_city,now_city,next_city,price;
    i=1;

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
                time=time+my_graph[min_route[0][i-1]][min_route[0][i]].time;
            }
            now_city=base_record[min_route[1][i]].city;//route[5][12];  //站点，到达时间，价格, 方式，班次
        }
        else
        {
            now_city=base_record[min_route[1][1]].city;
            time=time+my_graph[min_route[0][0]][min_route[0][1]].time;
        }

        if(((time%10)+(time/10)%10*10)>24)
        {
            time=((time%10)+(time/10)%10*10)-24+((time/100)%10+1)*100;
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
    return j;
}
