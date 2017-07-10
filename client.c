#include "server.h"

void ClientEntryPoint (int clientID)
{
	int i;
	msgStruct msg;
	
	for(i=0; i < ITER; i++)
	{
		/*create message*/
		initMsgStruct(&msg,clientID);
		/*send message*/
		if((msgQSend(serverQueue, &msg, MAX_MSG_LEN, WAIT_FOREVER, MSG_PRI_NORMAL)) == ERROR)
			printf("msgQSend failed client\n");
		
		taskDelay(CLIENT_DELAY);
		
		/* wait for acknowledgement */
		if((msgQReceive(clientsQueue[msg.from], &msg, MAX_MSG_LEN, WAIT_FOREVER)) == ERROR)
			printf("msgQReceive failed client\n");
		
		displayClient(&msg);
		
		taskDelay(CLIENT_DELAY);
		
		/* wait for message */
		if((msgQReceive(clientsQueue[msg.to], &msg, MAX_MSG_LEN, WAIT_FOREVER)) == ERROR)
			printf("msgQReceive failed client\n");
		
		displayClient(&msg);
	}
	
	/* wait for all tasks, then delete queue */
	taskDelay(TIMEOUT);
	msgQDelete(clientsQueue[clientID]); 
	
	printf("finished!\n");
}


void initMsgStruct (msgStruct *msg,int senderID){
	
	int r=senderID;
	while (r==senderID){
		srand(time(NULL));
		r = rand()%N;
	}
	
	msg->from=senderID;
	msg->to=r;
	msg->senderType = T_CLIENT;

	strcpy(msg->data,"data\n");
}

void displayClient (msgStruct *msg)
{
	if(msg->senderType == T_SERVER){
		printf("I am client %d, received ack msg\n", msg->to);
		return;
	}
	
	if(msg->senderType == T_CLIENT){
		printf("I am client %d, have got msg from client %d. ",msg->to, msg->from);
		printf("The message: %s\n",msg->data);
		return;
	}
}
