#ifndef _HEADER_H
#define _HEADER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip> 
#include <sstream> 
#include <fstream>

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>

#define MAX 20
using namespace std;
extern int convert(string);
extern void rewrite_file();
class FootBall_Player
{
	private:	
		string name;								 //球员姓名
		int age;									//球员年龄
		int ability;								//能力
		int salary;									//年薪
		int transfer_fee;							//转会费
		int total_goal;								//进球总数
		int serve_year;								//服役年限
		
	public:
		FootBall_Player(){};
		FootBall_Player(FootBall_Player &ply)
		{
		 	name = ply.name;
		 	age = ply.age;
		 	ability = ply.ability;
		 	salary = ply.salary;
		 	transfer_fee = ply.transfer_fee;
		 	total_goal = ply.total_goal;
		 	serve_year = ply.serve_year;
		};
		FootBall_Player(int k)
		{
		 	cout<<"请输入球员的名字"<<endl;
			cin>>name;
			cout<<"请输入球员的年龄"<<endl;
			cin>>age;
			cout<<"请输入球员的能力值"<<endl;
			cin>>ability;
			cout<<"请输入球员的年薪"<<endl;
			cin>>salary;
			cout<<"请输入球员的转会费"<<endl;
			cin>>transfer_fee;
			cout<<"请输入球员的总进球数"<<endl;
			cin>>total_goal;
			cout<<"请输入球员的服役年限"<<endl;
			cin>>serve_year; 
		};
		void initial()
		{
			cout<<"请输入球员的名字"<<endl;
			cin>>name;
			cout<<"请输入球员的年龄"<<endl;
			cin>>age;
			cout<<"请输入球员的能力值"<<endl;
			cin>>ability;
			cout<<"请输入球员的年薪"<<endl;
			cin>>salary;
			cout<<"请输入球员的转会费"<<endl;
			cin>>transfer_fee;
			cout<<"请输入球员的总进球数"<<endl;
			cin>>total_goal;
			cout<<"请输入球员的服役年限"<<endl;
			cin>>serve_year; 
		};
		FootBall_Player(string pname,int page,int pability,int psalary,int ptransfer_fee,int ptotal_goal,int pserve_year)
		{
			name = pname;
			age = page;
			ability = pability;
			salary = psalary;
			transfer_fee = ptransfer_fee;
			total_goal = ptotal_goal;
			serve_year = pserve_year;
		};
		void copy(FootBall_Player &p)
		{
			name = p.name;
			age = p.age;
			ability = p.ability;
			salary = p.salary;
			transfer_fee = p.transfer_fee;
			total_goal = p.total_goal;
			serve_year = p.serve_year;
		}
		friend void player_copy_to(FootBall_Player &p,FootBall_Player &s)
		{
			s.name = p.name;
			s.age = p.age;
			s.ability = p.ability;
			s.salary = p.salary;
			s.transfer_fee = p.transfer_fee;
			s.total_goal = p.total_goal;
			s.serve_year = p.serve_year;
		};
		string getname(){return name;};
		int getage(){return age;};
		int getability(){return ability;};
		int getsalary(){return salary;};
		int gettransfer_fee(){return transfer_fee;};
		int gettotal_goal(){return total_goal;};
		int getserve_year(){return serve_year;};
		void show();
		void file_initial(ifstream &in);
		void write(ofstream &);
		void tran_data();
		
};

class Administrator
{
	private:
		string name;
		int age;
		int ability;
		int salary;
		
	public:
		Administrator(){};
		Administrator(string pname,int page,int pability,int psalary)
		{
			name = pname;
			age = page;
			ability =  pability;
			salary = psalary;	
		};
		void initial()
		{
			cout<<"请输入行政人员的名字"<<endl;
		 	cin>>name;
			cout<<"请输入行政人员的年龄"<<endl;
			cin>>age;
			cout<<"请输入行政人员的能力值"<<endl;
			cin>>ability;
			cout<<"请输入行政人员的年薪"<<endl;
			cin>>salary;
		};
		friend void admin_copy_to(Administrator &p,Administrator &s)
		{
			s.name = p.name;
			s.age = p.age;
			s.ability = p.ability;
			s.salary = p.salary;
		};
		string getname(){return name;};
		void show();
		void file_initial(ifstream &in);
		void write(ofstream &);	
};		

class FootBall_Club 
{
	private:
		string name;
		int cash_stream;
		int player_num;
		int admin_num;
		FootBall_Player *player; 
		Administrator *staff;
		
	public:
		FootBall_Club()
	 	{
	 		cout<<"请输入俱乐部的名字"<<endl;
	 		cin>>name;
	 		cout<<"请输入俱乐部的资金"<<endl;
	 		cin>>cash_stream;
	 		cout<<"请输入俱乐部的球员个数"<<endl;
	 		cin>>player_num;
	 		player = new FootBall_Player[player_num];
	 		FootBall_Player *h = player;
	 		for(int i = 0; i < player_num; i++)
	 		{
	 			(*h).initial();
	 			h++;
	 		}
	 		cout<<"请输入俱乐部的行政人员个数"<<endl;
			cin>>admin_num; 
			staff = new Administrator[admin_num];	
	 		Administrator *r = staff;
	 		for(int i = 0; i < admin_num; i++)
	 		{
	 			(*r).initial();
	 			r++;
	 		}
	 	};
	 	FootBall_Club(string pname,int pcash,int pplayer,int pstaff,ifstream &ins)
	 	{
	 		name = pname;
	 		cash_stream = pcash;
	 		player_num = pplayer;
	 		player = new FootBall_Player[player_num];
	 		FootBall_Player *h = player;
	 		for(int i = 0; i < player_num; i++)
	 		{
	 			(*h).file_initial(ins);
	 			h++;
	 		}
	 		admin_num = pstaff;
	 		staff = new Administrator[admin_num];	
	 		Administrator *r = staff;
	 		for(int i = 0; i < admin_num; i++)
	 		{
	 			(*r).file_initial(ins);
	 			r++;
	 		}
	 	}
		string getname(){return name;};	
		FootBall_Player* getplayer(){return player;};
		Administrator* getadmin(){return staff;};
		int get_player_num(){return player_num;};
		int get_admin_num(){return admin_num;};
		int get_cash_stream(){return cash_stream;};
		void show();
		void write_name(string);
		void write_cash(int);
		void alt_player(string);
		void alt_admin(string);
		void add_player(FootBall_Player *);
		void delete_player(int);
		void add_admin(Administrator *);
		void delete_admin(int);
		void out_transfer(int);
		void in_transfer(int);
		void search(int,int[]);
		void write(ofstream &);
};
#endif

