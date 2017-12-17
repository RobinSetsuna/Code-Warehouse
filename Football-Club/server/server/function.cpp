#include "header.h"
#include "socket.h"
extern vector<FootBall_Club>clubs;
extern string order[MAX][MAX];
extern PlayerData Players[MAX_PLAYER];
extern int Player_Num;
int convert(string t)
{
	stringstream stream(t);
	int result;
	stream>>result;
	return result;
}

void rewrite_file()
{
	ofstream file("clubs_server.txt",ios::out);
	if(!file.is_open())
	{
		cout<<"д���ļ�ʧ��"<<endl;
		exit(1); 
	}
	
	for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
	{
		(*iter).write(file);
		if(iter != clubs.end() - 1)
			file<<endl;
	}
	file.close();
}

void FootBall_Player::tran_data()
{
	strcpy_s(Players[Player_Num].name,name.c_str());
	Players[Player_Num].ability = ability;
	Players[Player_Num].age = age;
	Players[Player_Num].salary = salary;
	Players[Player_Num].transfer_fee = transfer_fee;
	Players[Player_Num].serve_year = serve_year;
	Players[Player_Num].total_goal = total_goal;
	Player_Num++;
}

void FootBall_Player::write(ofstream &out)
{
	out<<name<<' ';
	out<<age<<' ';
	out<<ability<<' ';
	out<<salary<<' ';
	out<<transfer_fee<<' ';
	out<<total_goal<<' ';
	out<<serve_year<<'\n';
}

void Administrator::write(ofstream &outs)
{
	outs<<name<<" "<<age<<" "<<ability<<" "<<salary<<'\n';
}

void FootBall_Club::write(ofstream &out)
{
	FootBall_Player *p = player;
	Administrator *s = staff;
	//������ֲ���Ϣ
	out<<name<<" "<<cash_stream<<" "<<player_num<<" "<<admin_num<<'\n';
	//�����Ա��Ϣ 
	for(int i=0;i < player_num;i++)
	{
		(*p).write(out);
		p++;
	}
	//���������Ա��Ϣ
	for(int j=0;j < admin_num;j++)
	{
		(*s).write(out);
		s++;
	} 
}

void Administrator::file_initial(ifstream &in)
{
	char buffer[256];
	//��ʼ��������Ա���� 
	in.getline (buffer,100,' ');
	string str(buffer);
	name = str;
	//��ʼ������ 
	in.getline (buffer,100,' ');
	string val1(buffer);
	age = convert(val1);
	//��ʼ������
	in.getline (buffer,100,' ');
	string val2(buffer);
	ability = convert(val2); 
	//��ʼ����н
	in.getline (buffer,100,'\n');
	string val3(buffer);
	salary = convert(val3);   
}

void FootBall_Player::file_initial(ifstream &in)
{
	char buffer[256];
	//��ʼ����Ա���� 
	in.getline (buffer,100,' ');
	string str(buffer);
	name = str;
	//��ʼ������ 
	in.getline (buffer,100,' ');
	string val1(buffer);
	age = convert(val1);
	//��ʼ������
	in.getline (buffer,100,' ');
	string val2(buffer);
	ability = convert(val2); 
	//��ʼ����н
	in.getline (buffer,100,' ');
	string val3(buffer);
	salary = convert(val3); 
	//��ʼ��ת��� 
	in.getline (buffer,100,' ');
	string val4(buffer);
	transfer_fee = convert(val4); 
	//��ʼ����������
	in.getline (buffer,100,' ');
	string val5(buffer);
	total_goal = convert(val5);
	//��ʼ����������
	in.getline (buffer,100,'\n');
	string val6(buffer);
	serve_year = convert(val6);   
}

void FootBall_Player::show()
{
	cout<<"��Ա:"<<setw(10)<<left<<name<<"����:"<<setw(10)<<left<<age
	<<"����:"<<setw(10)<<left<<ability<<"��н:"<<setw(10)<<left<<salary
	<<"ת���:"<<setw(10)<<left<<transfer_fee<<"��������:"<<setw(10)<<left<<total_goal
	<<"��������:"<<setw(10)<<left<<serve_year<<endl; 
}

void Administrator::show()
{
	cout<<"������Ա:"<<setw(10)<<left<<name<<"����:"<<setw(10)<<left<<age
	<<"����:"<<setw(10)<<left<<ability<<"��н:"<<setw(10)<<left<<salary<<endl;
}

void FootBall_Club::write_name(string pname)
{
	name = pname;
	cout<<"���ֲ��������޸�!"<<endl; 
}

void FootBall_Club::write_cash(int pcash)
{
	cash_stream = pcash;
	cout<<"���ֲ��ֽ����޸�!"<<endl; 
}

void FootBall_Club::alt_player(string player_to_alt)
{
	FootBall_Player *a = player;
	for(int i = 0; i < player_num; i++)
	{
		if((*a).getname() == player_to_alt)
		{
			(*a).initial();
		}
		a++;
	}
}

void FootBall_Club::alt_admin(string admin_to_alt)
{
	Administrator *a = staff;
	for(int i = 0; i < admin_num; i++)
	{
		if((*a).getname() == admin_to_alt)
		{
			(*a).initial();
		}
		a++;
	}	
}

void FootBall_Club::add_player(FootBall_Player *p)
{
	player_num += 1; 
	FootBall_Player *t = new FootBall_Player[player_num];
	FootBall_Player *s = t;
	FootBall_Player *k = player;
	for(int i=0; i < player_num - 1; i++)
	{
		player_copy_to((*player),(*s));
		player++;
		s++;
	}
	player_copy_to((*p),(*s));
	player = t;
	delete[] k;
}

void FootBall_Club::delete_player(int player_to_delete)
{
	player_num -= 1; 
	FootBall_Player *t = new FootBall_Player[player_num];
	FootBall_Player *s = t;	
	FootBall_Player *k = player;
	for(int j=0; j < player_to_delete; j++)
	{
		player_copy_to((*player),(*s));
		player++;
		s++;
	}
	player++;
	for(int j = player_to_delete + 1; j < player_num + 1; j++)
	{
		player_copy_to((*player),(*s));
		player++;
		s++;
	}
	player = t;
	delete[] k;
}

void FootBall_Club::add_admin(Administrator *p)
{
	admin_num += 1; 
	Administrator *t = new Administrator[admin_num];
	Administrator *s = t;
	Administrator *k = staff;
	for(int i=0; i < admin_num - 1; i++)
	{
		admin_copy_to((*staff),(*s));
		staff++;
		s++;
	}
	admin_copy_to((*p),(*s));
	staff = t;
	delete[] k;
}

void FootBall_Club::delete_admin(int admin_to_delete)
{
	admin_num -= 1; 
	Administrator *t = new Administrator[player_num];
	Administrator *s = t;	
	Administrator *k = staff;
	for(int j=0; j < admin_to_delete; j++)
	{
		admin_copy_to((*staff),(*s));
		staff++;
		s++;
	}
	staff++;
	for(int j = admin_to_delete + 1; j < admin_num + 1; j++)
	{
		admin_copy_to((*staff),(*s));
		staff++;
		s++;
	}
	staff = t;
	delete[] k;
}

void FootBall_Club::show()
{
	cout<<"���ֲ�:"<<setw(15)<<left<<name<<"���ֲ��ʽ�:"<<setw(15)<<left
	<<cash_stream<<"��Ա����:"<<setw(15)<<left<<player_num<<"������Ա����:"<<setw(15)<<left<<admin_num<<endl; 
	FootBall_Player *n = player;
	for(int m = 0; m < player_num; m++)
	{
		(*n).show();
		n++;
	}
	Administrator *ad = staff;
	for(int j = 0; j < admin_num; j++)
	{
		(*ad).show();
		ad++;
	}
}
void FootBall_Club::out_transfer(int transfer_fee)
{
	cash_stream -= transfer_fee;
}
void FootBall_Club::in_transfer(int transfer_fee)
{
	cash_stream += transfer_fee;
}

void FootBall_Club::search(int length,int length_order[MAX])
{
	FootBall_Player *s = player;
	int mark[MAX];								//��������������Ϊ1��������Ϊ0 
	int i,j,value,pos_at,pos_great,pos_comma, pos_least, pos_equal,pos_dash,m;
	int flag[MAX] = {0};						//ȷ��ÿ����ֻ�ᱻ���һ�� 
	int ands = 0;								//ȷ��&&�������������ͬʱ���� 
	string cmp;
	string property;
	string operatr;
	for(m = 0; m < player_num; m++)
	{
		for(i=0;i<length;i++)
		{	
			ands = 0;							
			for(j=1;j<length_order[i];j++)
			{
				//������property��operatr��value 
				pos_at = order[i][j].find("@",0);
				pos_great = order[i][j].find(">",0);
				if(pos_great != -1)
				{
					property = order[i][j].substr(pos_at + 1, pos_great-pos_at-1);
				//	cout<<property<<endl;
					if(order[i][j].find("!",0) != -1)
					{
						operatr = "<=";
						pos_comma = order[i][j].find(")",0);
						value = convert(order[i][j].substr(pos_great + 1, pos_comma-pos_great-1));
					}	
					else 
					{
						operatr = ">";
						if((j == length_order[i] - 1) && (j != 1))
						{
							pos_comma = order[i][j].find(")",0);
							value = convert(order[i][j].substr(pos_great + 1, pos_comma-pos_great-1));
						}
						else
						{
							value = convert(order[i][j].substr(pos_great + 1, order[i][j].length()-pos_great));
						}
					}					
				}	
				if((pos_least = order[i][j].find("<",0)) != -1)
				{
					property = order[i][j].substr(pos_at + 1, pos_least-pos_at-1);
					if(order[i][j].find("!",0) != -1)
					{
						operatr = ">=";
						pos_comma = order[i][j].find(")",0);
						value = convert(order[i][j].substr(pos_least + 1, pos_comma-pos_least-1));
					}	
					else 
					{
						operatr = "<";
						if((j == length_order[i] - 1) && (j != 1))
						{
							pos_comma = order[i][j].find(")",0);
							value = convert(order[i][j].substr(pos_least + 1, pos_comma-pos_least-1));
						}
						else
						{
							value = convert(order[i][j].substr(pos_least + 1, order[i][j].length()-pos_least));
						}
					}		
					
				}
				if((pos_equal = order[i][j].find("=",0)) != -1)
				{
					property = order[i][j].substr(pos_at + 1, pos_equal-pos_at-1);
					if(order[i][j].find("!",0) != -1)
					{
						operatr = "!=";
						pos_comma = order[i][j].find(")",0);
						cmp = order[i][j].substr(pos_equal + 1, pos_comma-pos_equal-1);
					}	
					else 
					{
						operatr = "=";
						if((j == length_order[i] - 1) && (j != 1))
						{
							pos_comma = order[i][j].find(")",0);
							cmp = order[i][j].substr(pos_equal + 1, pos_comma-pos_equal-1);
						}
						else
						{
							cmp = order[i][j].substr(pos_equal + 1, order[i][j].length()-pos_equal);
						}
					}	
						
				}
				if((pos_dash = order[i][j].find("~",0)) != -1)
				{
					property = order[i][j].substr(pos_at + 1, pos_dash-pos_at-1);
					operatr = "~";
					if((j == length_order[i] - 1) && (j != 1))
					{
						pos_comma = order[i][j].find(")",0);
						cmp = order[i][j].substr(pos_dash + 1, pos_comma-pos_dash-1);
					}
					else
					{
						cmp = order[i][j].substr(pos_dash + 1, order[i][j].length()-pos_dash);
					}
				}
			  
				
			//�����Խ��з������� 
					if(property == "age")
					{
						if(operatr == ">")
						{
							if((*s).getage() > value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<=")
						{
							if((*s).getage() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}
						}
						else if(operatr == "<")
						{
							if((*s).getage() < value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).getage() >= value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}	
					else if(property == "ability")
					{
						if(operatr == ">")
						{
							if((*s).getability() > value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<=")
						{
							if((*s).getability() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<")
						{
							if((*s).getability() < value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).getability() >= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}
					else if(property == "salary")		
					{
						if(operatr == ">")
						{
							if((*s).getsalary() > value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}
						}
						else if(operatr == "<=")
						{
							if((*s).getsalary() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<")
						{
							if((*s).getsalary() < value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).getsalary() >= value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}	
					else if(property == "transfer_fee")		
					{
						if(operatr == ">")
						{
							if((*s).gettransfer_fee() > value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<=")
						{
							if((*s).gettransfer_fee() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<")
						{
							if((*s).gettransfer_fee() < value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).gettransfer_fee() >= value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}	
					else if(property == "total_goal")
					{
						if(operatr == ">")
						{
							if((*s).gettotal_goal() > value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<=")
						{
							if((*s).gettotal_goal() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<")
						{
							if((*s).gettotal_goal() < value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).gettotal_goal() >= value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}
					else if(property == "serve_year")
					{
						if(operatr == ">")
						{
							if((*s).getserve_year() > value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<=")
						{
							if((*s).getserve_year() <= value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == "<")
						{
							if((*s).getserve_year() < value)
							{
								mark[m] = 1;
							}
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
						else if(operatr == ">=")
						{
							if((*s).getserve_year() >= value)
								mark[m] = 1;
							else
							{
								mark[m] = 0;
								ands = 1;
							}	
						}
					}
					else if(property == "club")
					{
						if(operatr == "=")
						{
							if((cmp == name) && (length_order[i] == 2) && (flag[m] == 0))
							{
								strcpy_s(Players[Player_Num].cname,name.c_str());
								//(*s).show();
								(*s).tran_data();
								flag[m] = 1;
							}
						}
					}
					else if	(property == "name")
					{
						string c_name;
						c_name = (*s).getname();
						if((c_name.find(cmp,0) != -1) && (flag[m] == 0))
						{
							strcpy_s(Players[Player_Num].cname,name.c_str());
							//(*s).show();
							(*s).tran_data();
							flag[m] = 1;
						}	
					}		
			}
			//��ÿ��||�����ж�һ����� 
			if((mark[m] == 1) && (flag[m] == 0) && (ands == 0))
			{
				strcpy_s(Players[Player_Num].cname,name.c_str()); 
				//(*s).show();
				(*s).tran_data();
				flag[m] = 1;
			}		
		}
		s++;			
	}
}

