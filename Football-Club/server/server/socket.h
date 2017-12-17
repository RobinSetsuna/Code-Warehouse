#include "header.h"
#define MAX_NAME_LEN 20
#define MAX_EXPRE_LEN 256
#define MAX_STAFF 20
#define MAX_PLAYER 20
#define SEND_SIZE 2048
#define RECEIVE_SIZE 2048

#define QUERY_CLUB		1
#define QUERY_PLAYER	2
#define BUY_PLAYER		3
#define GET_CLUB		4
#define QUERY           5

#define SERVPORT 6000
#define LISTEN_SIZE 10
#define MAX_INFO_LEN 512

typedef struct 
{
	char name[MAX_NAME_LEN];
	char cname[MAX_NAME_LEN];
	int age, ability, salary, transfer_fee, total_goal, serve_year;
}PlayerData;

typedef struct 
{
	int number;									//���ص����ֵ�����
	char names[20][MAX_NAME_LEN];				//�洢����
}Names;

typedef struct 
{
	int type;									//�ύ����������ָ������		
	bool isSucceed;								//�ж��Ƿ�ת��ɹ�
	char club_name[20];
	int PLAYER_NUM;
	Names allNames;								//player names or club names;
	PlayerData playerTransfered[MAX_PLAYER];
}ReplyData;

typedef struct 
{
	int type;								
	int cash;				
	char clubName[MAX_NAME_LEN];			//Ҫ�����ľ��ֲ�����
	char playerName[MAX_NAME_LEN];		//Ҫ��������Ա����
	char expression[MAX_EXPRE_LEN];		//�������ʽ
}SubmitData;

