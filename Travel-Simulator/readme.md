# 旅行模拟系统
这是一个模拟旅行系统，旅客可以选择目的地、出发地和旅行策略。系统会计算出最优的旅行方式，并在地图中模拟旅客的旅行轨迹与时间。该系统使用QT开发，具有一个图形界面，方便直观地显示。

# Travel-Simulator 
This is a group project for my data structure course. The system is developed by Qt, with a desgined interface. It intends to offer travellers the optimal solution to his travel arrangement. Travellers can choose the wanted travel strategy and also both departures and destinations<br/>

The system have three travel strategies. <br/>
The first is time-least strategy<br/>
the second is cost-least strategy<br/>
the last is the mixed strategy which has the least cost under the condition that time is limited<br/>

I implemented a directed-map struture to represent the timetable of train,car and plane, which is stored in matrixs. Floyed and Dijkstra's algorithms are used and adapted in the system.
