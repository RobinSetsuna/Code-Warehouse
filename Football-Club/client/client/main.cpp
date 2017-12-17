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
	//��ʼ�����ֲ�����
	ifstream file("clubs.txt");
	char buffer[256];
	char ch;
	string club_name;
	int club_para[3];
	if (!file.is_open()) 
	{
		cout<<"�ļ���ȡʧ��!"<<'\n';
		exit(1); 
	}	
	while (!file.eof() ) 
	{
		//��ȡ���ֲ����� 
		file.getline (buffer,100,' ');
		string tr(buffer);
		club_name = tr;
		//��ȡ���ֲ����� 
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
	cout<<"				  \t������ֲ����������ҵ�棩  "<<'\n';
	cout<<'\n';
	cout<<"				  \t������transfer��������Ա��ת��"<<'\n';
	cout<<"				  \t������search�������ѯģʽ    "<<'\n';
	cout<<"				  \t������add������һ�����ֲ�     "<<'\n';
	cout<<"				  \t������delete��ɾ��һ�����ֲ�  "<<'\n';
	cout<<"				  \t������show����ʾ��Ϣ          "<<'\n'; 
	cout<<"				  \t������edit���޸ľ��ֲ���Ϣ    "<<'\n'; 
	cout<<"				  \t������exit���˳�����ϵͳ	    "<<'\n'; 

	
	while(1)
	{
		cin>>str;
		if(str == "transfer")
		{
			string out_club;
			string transfer_player;
			int tag = 0;
			cout<<"------------------------------------------------ת��ģʽ-----------------------------------------------------"<<endl;
			memset(&receivedData, 0, sizeof(receivedData));
			memset(&sendData, 0, sizeof(sendData));
			
			// call server
			sendData.type = GET_CLUB;
			linkForData();
			cout<<"��ǰ�ľ��ֲ���:"<<endl;
			cout<<"//���ؿͻ�������//"<<endl;
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				cout<<(*iter).getname()<<'\n';
			}
			cout<<"//Զ�̷���������//"<<endl;
			for(int n=0;n<receivedData.allNames.number;n++)
			{
				cout<<receivedData.allNames.names[n]<<'\n';
			}
			cout<<"������Ҫ����ת��ľ��ֲ�����"<<endl; 
			cin>>out_club; 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				if((*iter).getname() == out_club)
				{
					if((*iter).get_player_num() == 0)
					{
						cout<<"�þ��ֲ�û����Ա!ת��ʧ��!"<<endl; 
					}
					else
					{
						cout<<"�þ��ֲ�ӵ�е���Ա�У�"<<endl;
						cout<<"--------------------------------------------------"<<endl;
						FootBall_Player *p = (*iter).getplayer();
						for(int i=0; i < (*iter).get_player_num(); i++)
						{
							
							cout<<(*p).getname()<<endl;
							p++;
						}
						cout<<"--------------------------------------------------"<<endl;
						cout<<"��������Ҫת�����Ա����"<<endl;
						cin>>transfer_player;
						p = (*iter).getplayer();
						for(int i=0; i < (*iter).get_player_num(); i++)
						{
							if((*p).getname() == transfer_player)
							{
								cout<<"������Ҫתȥ�ľ��ֲ�����"<<endl;
								string in_club;
								cin>>in_club;
								for(vector<FootBall_Club>::iterator iter_2 = clubs.begin(); iter_2 != clubs.end(); iter_2++)
								{
								 	if((*iter_2).getname() == in_club)
									{
									 	if((*iter_2).get_cash_stream() < (*p).get_transfer_fee())
									 	{
									 		cout<<"ת��Ѳ��� ת��ʧ��!"<<endl; 
									 	}
									 	else 
									 	{
									 		(*iter_2).add_player(p);
									 		(*iter).delete_player(i);
									 		(*iter_2).out_transfer((*p).get_transfer_fee()); 
									 		(*iter).in_transfer((*p).get_transfer_fee());
									 		cout<<"ת��ɹ�!"<<endl;
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
				cout<<"�þ��ֲ�ӵ�е���Ա�У�"<<endl;
				serve_show();
				cout<<"��������Ҫת�����Ա������Ҫתȥ�ľ��ֲ�����"<<endl;
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
							cout<<"ת��ɹ���"<<endl;
						}
					}
				}
				else
				{
					cout<<"ת��Ѳ��㣡ת��ʧ��!"<<endl;
				}
			
			}
			
		}
		if(str == "exit")
		{
			return 0;
		}
		if(str == "add")
		{	
			cout<<"------------------------------------------------��Ӿ��ֲ�ģʽ------------------------------------------------"<<endl;
			FootBall_Club club;
			clubs.push_back(club);
			rewrite_file(); 
			cout<<"�ѳɹ���Ӿ��ֲ�"<<endl;
		}
		if(str == "delete")
		{
			cout<<"------------------------------------------------ɾ�����ֲ�ģʽ------------------------------------------------"<<endl;
			string new_club;
			cout<<"������Ҫɾ�����ֲ�������"<<endl;
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
			cout<<"���ֲ���ɾ��"<<endl;
			rewrite_file(); 
		}
		if(str == "show")
		{
			cout<<"------------------------------------------------��ϸ��Ϣģʽ----------------------------------------------------"<<endl;
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
			cout<<"------------------------------------------------���ֲ��޸�ģʽ-------------------------------------------------"<<endl;
			cout<<"������Ҫ�����޸ĵľ��ֲ�����"<<endl; 
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
			
			cout<<"  					��������Ҫ���еĲ���  "<<endl;
			cout<<"					1-------�޸ľ��ֲ�������"<<endl;
			cout<<"					2-------�޸ľ��ֲ����ֽ�"<<endl;
			cout<<"					3-------�޸���Ա��Ϣ    "<<endl;
			cout<<"					4-------�޸�������Ա��Ϣ"<<endl;
			
					cin>>op;
					switch(op)
					{
						case 1:
							cout<<"�������µ�����"<<endl;
							cin>>new_name;
							(*iter).write_name(new_name);
							rewrite_file(); 
							cout<<"��Ϣ���޸�!"<<endl;
							break;
							
						case 2:
							cout<<"�������ֽ�����"<<endl;
							cin>>cash;
							(*iter).write_cash(cash);
							rewrite_file(); 
							cout<<"��Ϣ���޸�!"<<endl;
							break;
							
						case 3:
							cout<<"------------------------------------------------��Ա�޸�ģʽ-------------------------------------------------"<<endl;
							cout<<"�þ��ֲ�ӵ�е���Ա�У�"<<endl;
							p = (*iter).getplayer();
							for(int i=0; i < (*iter).get_player_num(); i++)
							{
							
								cout<<(*p).getname()<<endl;
								p++;
							}
							
							
						
							cout<<"					������add��������Ա"<<endl;
							cout<<"					������delete��ɾ��Ա"<<endl;
							cout<<"					������alter���޸���Ա��Ϣ"<<endl;
							
						
							cin>>player_op;
							if(player_op == "add")
							{
								FootBall_Player *new_player = new FootBall_Player(1);
								(*iter).add_player(new_player);
								cout<<"�ѳɹ������Ա!"<<endl; 
							}
							if(player_op == "delete")
							{
								string delete_player;
								cout<<"��������Ҫɾ������Ա����"<<endl; 
								cin>>delete_player;
								FootBall_Player *s = (*iter).getplayer();
								s = (*iter).getplayer();
								for(int i=0; i < (*iter).get_player_num(); i++)
								{
									if((*s).getname() == delete_player)
									{
										(*iter).delete_player(i);
										cout<<"�ѳɹ�ɾ����Ա"<<endl; 
									}
									s++;
								}
							} 
							if(player_op == "alter")
							{
								string alt_player;
								cout<<"��������Ҫ�޸ĵ���Ա����"<<endl; 
								cin>>alt_player;
								(*iter).alt_player(alt_player);
								cout<<"�ѳɹ��޸���Ա"<<endl; 
							}
							rewrite_file(); 
							break;
							
						case 4:
							cout<<"----------------------------------------�����޸�ģʽ-----------------------------------------"<<endl;
							cout<<"�þ��ֲ�ӵ�е�������Ա�У�"<<endl;
							u = (*iter).getadmin();
							for(int i=0; i < (*iter).get_admin_num(); i++)
							{
							
								cout<<(*u).getname()<<endl;
								u++;
							}
							
							
							
							cout<<"*****************************"<<endl;
							cout<<"*   ����add������������Ա   *"<<endl;
							cout<<"*   ����delete��ɾ������Ա  *"<<endl;
							cout<<"*����alter���޸�������Ա��Ϣ*"<<endl;
							cout<<"*****************************"<<endl;
							cin>>admin_op;
							if(admin_op == "add")
							{
								Administrator *new_admin = new Administrator();
								(*new_admin).initial();
								(*iter).add_admin(new_admin);
								cout<<"�ѳɹ����������Ա!"<<endl; 
							}
							if(admin_op == "delete")
							{
								string delete_admin;
								cout<<"��������Ҫɾ����������Ա����"<<endl; 
								cin>>delete_admin;
								
								u = (*iter).getadmin();
								for(int i=0; i < (*iter).get_admin_num(); i++)
								{
									if((*u).getname() == delete_admin)
									{
										(*iter).delete_admin(i);
										cout<<"�ѳɹ�ɾ��������Ա"<<endl; 
									}
									u++;
								}
							} 
							if(admin_op == "alter")
							{
								string alt_admin;
								cout<<"��������Ҫ�޸ĵ�������Ա����"<<endl; 
								cin>>alt_admin;
								(*iter).alt_admin(alt_admin);
								cout<<"�ѳɹ��޸�������Ա"<<endl; 
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
			cout<<"------------------------------------------------���ʽ����-----------------------------------------------------"<<endl;
			cout<<"�������ѯ���ʽ"<<endl; 
			cin>>str;
			int i;
			int pos = 0;
			int ini = 0;
			int length = 0; 
			int length_order[MAX];
			//ͨ��||���ַ����ָ� 
			for(length; pos != -1; length++)
			{
				pos = str.find("||",ini);
				order[length][0] = str.substr(ini,pos-ini);
				ini = 2 + pos;
			}
			//ͨ��&&���ַ����ָ�
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
			cout<<"//���ؿͻ�������//"<<endl;
			//������������ 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				(*iter).search(length,length_order);	
			}

			//Զ����������
			cout<<"//Զ�̷���������//"<<endl;
			
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
