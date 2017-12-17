#include "header.h"
#include "socket.h"
vector<FootBall_Club>clubs;
string order[MAX][MAX];
char info[MAX_INFO_LEN];
PlayerData Players[MAX_PLAYER];
int Player_Num = 0;
int main() 
{	
	string str;
	//cout<<"------------------------------------------------初始化阶段---------------------------------------------------"<<'\n';
	ifstream file("clubs_server.txt");
	char buffer[256];
	char ch;
	string club_name;
	int club_para[3];
	if (!file.is_open()) 
	{
		cout<<"文件读取失败!"<<'\n';
		exit(1); 
	}
	else
	{
		//cout<<"文件读取成功"<<'\n'; 
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
	//cout<<"已成功初始化数据"<<'\n'; 
	//cout<<"------------------------------------------------初始化结束-----------------------------------------------------"<<'\n';

	//设立缓冲区
	char receive_buf[RECEIVE_SIZE];
	char send_buf[SEND_SIZE];
	SubmitData recv_data;
	ReplyData send_data;
	//创建套接字
    WORD myVersionRequest;
    WSADATA wsaData;
    myVersionRequest=MAKEWORD(1,1);
    int err, client_fd;
    err=WSAStartup(myVersionRequest,&wsaData);
    if (err == SOCKET_ERROR)
    {
		cout<<"嵌套字未打开!"<<endl;
		return -1;
    }

	//binding
	SOCKET sServer = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	//创建了可识别套接字
	if(INVALID_SOCKET == sServer)
	{
		cout<<"socket()错误!"<<endl;
		WSACleanup();
		return -1;
	}
	struct sockaddr_in addrServ, remote_addr;
	addrServ.sin_family=AF_INET;
	addrServ.sin_addr.s_addr = inet_addr("127.0.0.1");			//ip地址
	addrServ.sin_port=htons(SERVPORT);							//绑定端口
	bind(sServer,(struct sockaddr*)&addrServ,sizeof(struct sockaddr));		//绑定完成
	int retVal = listen(sServer,LISTEN_SIZE);					//其中第二个参数代表能够接收的最多的连接数
	if(SOCKET_ERROR == retVal)
	{
		cout<<"listen错误!"<<endl;
		closesocket(sServer);
		WSACleanup();
		return -1;
	}
	cout<<"TCP服务器开始监听"<<"6000"<<"端口"<<endl;
	
	//accept
	// deal with coming requests
    while(true) 
    {
		int sin_size = sizeof(remote_addr);    
		if ((client_fd = accept(sServer, (struct sockaddr*)&remote_addr, &sin_size)) == SOCKET_ERROR) 
        {
            cout << "\nError:accept failed\n" << endl;
            exit(1);
		}

		memset(&send_data, 0, sizeof(send_data));
		memset(&recv_data, 0, sizeof(recv_data));
		memset(receive_buf, 0, sizeof(receive_buf));
		memset(send_buf, 0, sizeof(receive_buf));
		//从socket接收一个包
		recv(client_fd, receive_buf, sizeof(receive_buf), 0);
		memcpy(&recv_data, receive_buf, sizeof(recv_data));

		if(recv_data.type == QUERY_PLAYER)
		{

			string str(recv_data.expression);
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
				//cout<<order[length][0]<<endl;
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
				//	cout<<order[i][length_order[i]]<<endl;
				}
			} 
			//调用搜索函数 
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				(*iter).search(length,length_order);	
			}
			//将数据传递至发送包内
			for(int j=0;j<Player_Num;j++)
			{
				send_data.playerTransfered[j].ability = Players[j].ability;
				send_data.playerTransfered[j].salary = Players[j].salary;
				send_data.playerTransfered[j].age = Players[j].age;
				send_data.playerTransfered[j].total_goal = Players[j].total_goal;
				send_data.playerTransfered[j].transfer_fee = Players[j].transfer_fee;
				send_data.playerTransfered[j].serve_year = Players[j].serve_year;
				strcpy_s(send_data.playerTransfered[j].name,Players[j].name);
				strcpy_s(send_data.playerTransfered[j].cname,Players[j].cname);
			}
			send_data.PLAYER_NUM = Player_Num;
			memcpy(send_buf, &send_data, sizeof(send_data));
			send(client_fd, send_buf, sizeof(send_buf), 0);
			closesocket(client_fd);
			Player_Num = 0;
		}
		if(recv_data.type == GET_CLUB)
		{
			int m = 0;
			send_data.type = GET_CLUB;
			
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				strcpy_s(send_data.allNames.names[m],(*iter).getname().c_str());
				m++;
			}
			send_data.allNames.number = m;
			memcpy(send_buf, &send_data, sizeof(send_data));
			send(client_fd, send_buf, sizeof(send_buf), 0);
			closesocket(client_fd);
		}
		if(recv_data.type == QUERY)
		{
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				if(strcmp((*iter).getname().c_str(),recv_data.clubName) == 0)
				{
					FootBall_Player *p = (*iter).getplayer();
					for(int i=0; i < (*iter).get_player_num(); i++)
					{
						strcpy_s(Players[Player_Num].cname,(*iter).getname().c_str()); 
						(*p).tran_data();
						p++;
					}
				}
			}

			for(int j=0;j<Player_Num;j++)
			{
				send_data.playerTransfered[j].ability = Players[j].ability;
				send_data.playerTransfered[j].salary = Players[j].salary;
				send_data.playerTransfered[j].age = Players[j].age;
				send_data.playerTransfered[j].total_goal = Players[j].total_goal;
				send_data.playerTransfered[j].transfer_fee = Players[j].transfer_fee;
				send_data.playerTransfered[j].serve_year = Players[j].serve_year;
				strcpy_s(send_data.playerTransfered[j].name,Players[j].name);
				strcpy_s(send_data.playerTransfered[j].cname,Players[j].cname);
			}
			send_data.PLAYER_NUM = Player_Num;
			memcpy(send_buf, &send_data, sizeof(send_data));
			send(client_fd, send_buf, sizeof(send_buf), 0);
			closesocket(client_fd);
			Player_Num = 0;
		}
		if(recv_data.type == BUY_PLAYER)
		{
			for(vector<FootBall_Club>::iterator iter = clubs.begin(); iter != clubs.end(); iter++)
			{
				if(strcmp((*iter).getname().c_str(),recv_data.clubName) == 0)
				{
					FootBall_Player *p = (*iter).getplayer();
					for(int i=0; i < (*iter).get_player_num(); i++)
					{
						if(strcmp((*p).getname().c_str(),recv_data.playerName) == 0)
						{
							//若可以完成转会
							if(recv_data.cash >= (*p).gettransfer_fee())
							{
								send_data.isSucceed = true;
								send_data.playerTransfered[0].ability = (*p).getability();
								send_data.playerTransfered[0].salary = (*p).getsalary();
								send_data.playerTransfered[0].age = (*p).getage();
								send_data.playerTransfered[0].total_goal = (*p).gettotal_goal();
								send_data.playerTransfered[0].transfer_fee = (*p).gettransfer_fee();
								send_data.playerTransfered[0].serve_year = (*p).getserve_year();
								strcpy_s(send_data.playerTransfered[0].name,(*p).getname().c_str());
								(*iter).delete_player(i);
								cout<<send_data.playerTransfered[0].transfer_fee<<endl;
								(*iter).in_transfer(send_data.playerTransfered[0].transfer_fee);
								rewrite_file();
								send_data.PLAYER_NUM = Player_Num;
								memcpy(send_buf, &send_data, sizeof(send_data));
								send(client_fd, send_buf, sizeof(send_buf), 0);
								closesocket(client_fd);
							}
							else
							{
								send_data.isSucceed = false;

								send_data.PLAYER_NUM = Player_Num;
								memcpy(send_buf, &send_data, sizeof(send_data));
								send(client_fd, send_buf, sizeof(send_buf), 0);
								closesocket(client_fd);
							}
						}
						p++;
					}
				}
			}


		}
	}
       return 0;
}
