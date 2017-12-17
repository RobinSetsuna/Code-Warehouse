#include "header.h"
#include "socket.h"
void linkForData(SubmitData& sData, ReplyData& rData)
{
	int sockfd;
	char receive_buf[RECEIVE_SIZE];
	char send_buf[SEND_SIZE];
	struct sockaddr_in serv_addr;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		cout << "\nError:socket create failed\n" << endl;
		exit(1);
	}
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_port 			= htons(SERVPORT);
	serv_addr.sin_addr.s_addr 	= inet_addr("127.0.0.1");


	if( connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) == -1 )
	{
		cout << "\nError:connect failed\n" << endl;
		cout << errno << endl;
		exit(1);
	}

	memset(receive_buf, 0, sizeof(receive_buf));
	memset(send_buf, 0, sizeof(send_buf));
	memcpy(send_buf, (char *)&sData, sizeof(sData));


	send(sockfd, send_buf, sizeof(send_buf), 0);
	recv(sockfd, receive_buf, sizeof(receive_buf), 0);
	memset(&rData, 0, sizeof(rData));
	memcpy(&rData, receive_buf, sizeof(rData));

}