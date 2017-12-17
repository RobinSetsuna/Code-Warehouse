#include "header.h"
#include "socket.h"
extern ReplyData receivedData;
extern SubmitData sendData;
void linkForData()
{
	int sockfd;
	char receive_buf[RECEIVE_SIZE];
	char send_buf[SEND_SIZE];
	struct sockaddr_in serv_addr;
	//创建套接字
    WORD myVersionRequest;
    WSADATA wsaData;
    myVersionRequest=MAKEWORD(1,1);
    int err;
    err=WSAStartup(myVersionRequest,&wsaData);
	if (err == SOCKET_ERROR)
    {
		cout<<"嵌套字未打开!"<<endl;
		exit(1);
    }

	if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
	{
		cout << "\nError:socket create failed\n" << endl;
		exit(1);
	}
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_port 			= htons(SERVPORT);
	serv_addr.sin_addr.s_addr 	= inet_addr("127.0.0.1");


	if( connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) == SOCKET_ERROR )
	{
		cout << "\nError:connect failed\n" << endl;
		cout << errno << endl;
		exit(1);
	}

	memset(receive_buf, 0, sizeof(receive_buf));
	memset(send_buf, 0, sizeof(send_buf));
	memcpy(send_buf, (char *)&sendData, sizeof(sendData));
	
		

	send(sockfd, send_buf, sizeof(send_buf), 0);
	recv(sockfd, receive_buf, sizeof(receive_buf), 0);
	memset(&receivedData, 0, sizeof(receivedData));
	memcpy(&receivedData, receive_buf, sizeof(receivedData));
	closesocket(sockfd);
	WSACleanup();
}