#include "header.h"
#include "socket.h"
vector<FootBall_Club>clubs;
string order[MAX][MAX];
extern void linkForData();
ReplyData receivedData;
SubmitData sendData;
int main() 
{
	string str;
	//初始化俱乐部数据
	ifstream file("clubs.txt");
	char buffer[256];
	char ch;
	string club_name;
	int club_para[3];
	if (!file.is_open()) 
	{
		cout<<"文件读取失败!"<<'\n';
		exit(1); 
	}	
	while (!file.eof() ) 
	{
		//读取俱乐部名字 
		file.getline (buffer,100,' ');
		string tr(buffer);
		club_name = tr;
		//读取俱乐部参数 
		for(int i=0;i<3;i++)
		{
			if(i == 2)
				file.getline(buffer,100,'\n');
			else
				file.getline(buffer,100,' ');
			string bu(buffer);
			club_para[i] = convert(bu);
		}
		FootBall_Club club(club_name,club_para[0],club_para[1],club_para[2],file);
		clubs.push_back(club);
		file.get(ch);
	} 
	


	cout<<'\n';
	cout<<"				  \t足球俱乐部管理程序（企业版）  "<<'\n';
	cout<<'\n';
	cout<<"				  \t请输入transfer来进行球员的转会"<<'\n';
	cout<<"				  \t请输入search来进入查询模式    "<<'\n';
	cout<<"				  \t请输入add来增加一个俱乐部     "<<'\n';
	cout<<"				  \t请输入delete来删除一个俱乐部  "<<'\n';
	cout<<"				  \t请输入show来显示信息          "<<'\n'; 
	cout<<"				  \t请输入edit来修改俱乐部信息    "<<'\n'; 
	cout<<"				  \t请输入exit来退出管理系统	    "<<'\n'; 

	
	while(1)
	{
		cin>>str;
		if(str == "transfer")
		{
			string out_club;
			string transfer_player;
			int tag = 0;
			cout<<"------------------------------------------------转会模式-----------------------------------------------------"<<endl;
			memset(&receivedData, 0, sizeof(receivedData));
			memset(&sendData, 0, sizeof(sendData));
			
			// call server
			sendData.type = GET_CLUB;
			linkForData();
			cout<<"当前的俱乐部有:"<<endl;
			cout<<"//本地客户端数据//"<<endl;
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				cout<<(*iter).getname()<<'\n';
			}
			cout<<"//远程服务器数据//"<<endl;
			for(int n=0;n<receivedData.allNames.number;n++)
			{
				cout<<receivedData.allNames.names[n]<<'\n';
			}
			cout<<"请输入要进行转会的俱乐部名字"<<endl; 
			cin>>out_club; 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				if((*iter).getname() == out_club)
				{
					if((*iter).get_player_num() == 0)
					{
						cout<<"该俱乐部没有球员!转会失败!"<<endl; 
					}
					else
					{
						cout<<"该俱乐部拥有的球员有："<<endl;
						cout<<"--------------------------------------------------"<<endl;
						FootBall_Player *p = (*iter).getplayer();
						for(int i=0; i < (*iter).get_player_num(); i++)
						{
							
							cout<<(*p).getname()<<endl;
							p++;
						}
						cout<<"--------------------------------------------------"<<endl;
						cout<<"请输入你要转会的球员姓名"<<endl;
						cin>>transfer_player;
						p = (*iter).getplayer();
						for(int i=0; i < (*iter).get_player_num(); i++)
						{
							if((*p).getname() == transfer_player)
							{
								cout<<"请输入要转去的俱乐部名字"<<endl;
								string in_club;
								cin>>in_club;
								for(vector<FootBall_Club>::iterator iter_2 = clubs.begin(); iter_2 != clubs.end(); iter_2++)
								{
								 	if((*iter_2).getname() == in_club)
									{
									 	if((*iter_2).get_cash_stream() < (*p).get_transfer_fee())
									 	{
									 		cout<<"转会费不足 转会失败!"<<endl; 
									 	}
									 	else 
									 	{
									 		(*iter_2).add_player(p);
									 		(*iter).delete_player(i);
									 		(*iter_2).out_transfer((*p).get_transfer_fee()); 
									 		(*iter).in_transfer((*p).get_transfer_fee());
									 		cout<<"转会成功!"<<endl;
											tag = 1;
											rewrite_file(); 
									 	}
									}
							 	}
							}
							p++;
						} 	 
					}
				}
			}	
			//calling server
			if(tag != 1)
			{
				string t_club;
				memset(&receivedData, 0, sizeof(receivedData));
				memset(&sendData, 0, sizeof(sendData));
				sendData.type = QUERY;
				strcpy_s(sendData.clubName,out_club.c_str());
				linkForData();
				cout<<"该俱乐部拥有的球员有："<<endl;
				serve_show();
				cout<<"请输入你要转会的球员姓名和要转去的俱乐部名字"<<endl;
				cin>>transfer_player;
				cin>>t_club;
				memset(&receivedData, 0, sizeof(receivedData));
				memset(&sendData, 0, sizeof(sendData));
				sendData.type = BUY_PLAYER;
				for(vector<FootBall_Club>::iterator iter_2 = clubs.begin(); iter_2 != clubs.end(); iter_2++)
				{
					if((*iter_2).getname() == t_club)
					{
						sendData.cash = (*iter_2).get_cash_stream();
					}
				}
				strcpy_s(sendData.clubName,out_club.c_str());
				strcpy_s(sendData.playerName,transfer_player.c_str());
				linkForData();
				if(receivedData.isSucceed == true)
				{
					string names(receivedData.playerTransfered[0].name);
					FootBall_Player player(names,
						receivedData.playerTransfered[0].age,
						receivedData.playerTransfered[0].ability,
						receivedData.playerTransfered[0].salary,
						receivedData.playerTransfered[0].transfer_fee,
						receivedData.playerTransfered[0].total_goal,
						receivedData.playerTransfered[0].serve_year);
						
					for(vector<FootBall_Club>::iterator iter_2 = clubs.begin(); iter_2 != clubs.end(); iter_2++)
					{
						if((*iter_2).getname() == t_club)
						{
							(*iter_2).add_player(&player);
							(*iter_2).out_transfer(receivedData.playerTransfered[0].transfer_fee); 
							rewrite_file();
							cout<<"转会成功！"<<endl;
						}
					}
				}
				else
				{
					cout<<"转会费不足！转会失败!"<<endl;
				}
			
			}
			
		}
		if(str == "exit")
		{
			return 0;
		}
		if(str == "add")
		{	
			cout<<"------------------------------------------------添加俱乐部模式------------------------------------------------"<<endl;
			FootBall_Club club;
			clubs.push_back(club);
			rewrite_file(); 
			cout<<"已成功添加俱乐部"<<endl;
		}
		if(str == "delete")
		{
			cout<<"------------------------------------------------删除俱乐部模式------------------------------------------------"<<endl;
			string new_club;
			cout<<"请输入要删除俱乐部的名字"<<endl;
			cin>>new_club;
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end();)
			{
				if((*iter).getname() == new_club)
				{
					clubs.erase(iter); 
				}
				else
					iter++;
			}
			cout<<"俱乐部已删除"<<endl;
			rewrite_file(); 
		}
		if(str == "show")
		{
			cout<<"------------------------------------------------详细信息模式----------------------------------------------------"<<endl;
			cout<<'\n';
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{	
				cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
				(*iter).show();
				cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
				cout<<'\n';
			}
		}
		if(str == "edit")
		{
			cout<<"------------------------------------------------俱乐部修改模式-------------------------------------------------"<<endl;
			cout<<"请输入要进行修改的俱乐部名字"<<endl; 
			string alt_club;
			cin>>alt_club; 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				if((*iter).getname() == alt_club)
				{
					int op;
					string new_name;
					int cash;
					FootBall_Player *p;
					Administrator *u;
					string player_op;
					string admin_op;
			
			cout<<"  					请输入你要进行的操作  "<<endl;
			cout<<"					1-------修改俱乐部的名字"<<endl;
			cout<<"					2-------修改俱乐部的现金"<<endl;
			cout<<"					3-------修改球员信息    "<<endl;
			cout<<"					4-------修改行政人员信息"<<endl;
			
					cin>>op;
					switch(op)
					{
						case 1:
							cout<<"请输入新的名字"<<endl;
							cin>>new_name;
							(*iter).write_name(new_name);
							rewrite_file(); 
							cout<<"信息已修改!"<<endl;
							break;
							
						case 2:
							cout<<"请输入现金数额"<<endl;
							cin>>cash;
							(*iter).write_cash(cash);
							rewrite_file(); 
							cout<<"信息已修改!"<<endl;
							break;
							
						case 3:
							cout<<"------------------------------------------------球员修改模式-------------------------------------------------"<<endl;
							cout<<"该俱乐部拥有的球员有："<<endl;
							p = (*iter).getplayer();
							for(int i=0; i < (*iter).get_player_num(); i++)
							{
							
								cout<<(*p).getname()<<endl;
								p++;
							}
							
							
						
							cout<<"					请输入add来增加球员"<<endl;
							cout<<"					请输入delete来删球员"<<endl;
							cout<<"					请输入alter来修改球员信息"<<endl;
							
						
							cin>>player_op;
							if(player_op == "add")
							{
								FootBall_Player *new_player = new FootBall_Player(1);
								(*iter).add_player(new_player);
								cout<<"已成功添加球员!"<<endl; 
							}
							if(player_op == "delete")
							{
								string delete_player;
								cout<<"请输入你要删除的球员姓名"<<endl; 
								cin>>delete_player;
								FootBall_Player *s = (*iter).getplayer();
								s = (*iter).getplayer();
								for(int i=0; i < (*iter).get_player_num(); i++)
								{
									if((*s).getname() == delete_player)
									{
										(*iter).delete_player(i);
										cout<<"已成功删除球员"<<endl; 
									}
									s++;
								}
							} 
							if(player_op == "alter")
							{
								string alt_player;
								cout<<"请输入你要修改的球员姓名"<<endl; 
								cin>>alt_player;
								(*iter).alt_player(alt_player);
								cout<<"已成功修改球员"<<endl; 
							}
							rewrite_file(); 
							break;
							
						case 4:
							cout<<"----------------------------------------行政修改模式-----------------------------------------"<<endl;
							cout<<"该俱乐部拥有的行政人员有："<<endl;
							u = (*iter).getadmin();
							for(int i=0; i < (*iter).get_admin_num(); i++)
							{
							
								cout<<(*u).getname()<<endl;
								u++;
							}
							
							
							
							cout<<"*****************************"<<endl;
							cout<<"*   输入add来增加行政人员   *"<<endl;
							cout<<"*   输入delete来删行政球员  *"<<endl;
							cout<<"*输入alter来修改行政人员信息*"<<endl;
							cout<<"*****************************"<<endl;
							cin>>admin_op;
							if(admin_op == "add")
							{
								Administrator *new_admin = new Administrator();
								(*new_admin).initial();
								(*iter).add_admin(new_admin);
								cout<<"已成功添加行政人员!"<<endl; 
							}
							if(admin_op == "delete")
							{
								string delete_admin;
								cout<<"请输入你要删除的行政人员姓名"<<endl; 
								cin>>delete_admin;
								
								u = (*iter).getadmin();
								for(int i=0; i < (*iter).get_admin_num(); i++)
								{
									if((*u).getname() == delete_admin)
									{
										(*iter).delete_admin(i);
										cout<<"已成功删除行政人员"<<endl; 
									}
									u++;
								}
							} 
							if(admin_op == "alter")
							{
								string alt_admin;
								cout<<"请输入你要修改的行政人员姓名"<<endl; 
								cin>>alt_admin;
								(*iter).alt_admin(alt_admin);
								cout<<"已成功修改行政人员"<<endl; 
							}
							rewrite_file(); 
							break;
						default:
							break;
					}
				}
			}
		}
		if(str == "search")
		{	
			cout<<"------------------------------------------------表达式搜索-----------------------------------------------------"<<endl;
			cout<<"请输入查询表达式"<<endl; 
			cin>>str;
			int i;
			int pos = 0;
			int ini = 0;
			int length = 0; 
			int length_order[MAX];
			//通过||将字符串分割 
			for(length; pos != -1; length++)
			{
				pos = str.find("||",ini);
				order[length][0] = str.substr(ini,pos-ini);
				ini = 2 + pos;
			}
			//通过&&将字符串分割
			for(i=0;i < length;i++)
			{
				ini=0;pos=0;
				for(length_order[i] = 1; pos != -1;length_order[i]++)
				{
					pos = order[i][0].find("&&",ini);
					order[i][length_order[i]] = order[i][0].substr(ini,pos-ini);
					ini = 2 + pos;
				}
			} 
			cout<<"//本地客户端数据//"<<endl;
			//调用搜索函数 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				(*iter).search(length,length_order);	
			}

			//远程搜索部分
			cout<<"//远程服务器数据//"<<endl;
			
			memset(&receivedData, 0, sizeof(receivedData));
			memset(&sendData, 0, sizeof(sendData));
			
			// call server
			sendData.type = QUERY_PLAYER;
			strncpy_s(sendData.expression, str.c_str(), MAX_EXPRE_LEN+1);
			linkForData();
			serve_show();
		}
	}
}
