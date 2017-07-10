#ifndef __SERVER
#define __SERVER

#include "vxWorks.h"
#include "taskLib.h"
#include "semLib.h"
#include "msgQLib.h"
#include <stdlib.h> 
#include <time.h>
#include <stdlib.h>

#define MAX_MSGS 20
#define MAX_MSG_LEN 50
#define SERV_PRIO 108
#define CLIENT_PRIO 107
#define T_SERVER 1
#define T_CLIENT 2
#define N 3
#define ITER 5
#define STACK_SIZE 2000
#define CLIENT_DELAY 6
#define TIMEOUT 30

int tidServer;
int tidClients[N];
MSG_Q_ID clientsQueue[N];
MSG_Q_ID serverQueue;

typedef struct _msgStruct_{
	
	int from; 
	int to; 
	int senderType;
	char data[MAX_MSG_LEN]; // the message
	
} msgStruct;

void server (void);

void ClientEntryPoint (int senderID);

void initMsgStruct (msgStruct *,int clientID);

void displayClient (msgStruct*);

#endif
