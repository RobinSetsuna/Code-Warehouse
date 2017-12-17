#ifndef WIDGET_H
#define WIDGET_H
#include"define.h"
#include <QWidget>
#include<QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void getText();
    int checkInput();
    int getCityNum(QString);
    int setPassCity();
    int baseGraph();
    int city_sum(void);//返回拆分点的总数
    int S1();
    int S2();
    int S3();
    void S1_create_graph(int**);
    void S2_create_graph(int** );
    void S3_create_graph(cell**);
    int combination(int n, int m);
    int S1_S2_MinStrategy(int **graph,int pointsum,int *path,int k);
    int S3_MinStrategy(cell **graph,int pointsum,int *path,int k,int lim);
    int S1_S2_route(int* m_route,int**my_graph,int minTime,int strategy);
    int S3_route(int* m_route,cell**my_graph,int minTime);
    int total_time(int city_num);
    void clean(void);
    //void setTable();
    void paintEvent(QPaintEvent *event);
    void writeFile(QString);
    void writeFile_result();


private slots:
    void on_pushButton_check_clicked();

    void on_comboBox_startegy_currentIndexChanged(int index);
    void qtimeSlot();

    void on_pushButton_exit_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::Widget *ui;
    int point_sum;
    int city_sta;
    int city_end;
    int pathway[12];
    int coord[2][12];
    QString cityList[12];
    QString way[3];
    int strategy;
    int limTime;
    int city_num;
    int time_now;
    QTimer *timer;
    int statue;
    int countTime;
    int change_city;
    int change_time;
};

#endif // WIDGET_H
