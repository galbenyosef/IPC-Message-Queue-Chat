#include "server.h"

void server (void){
	
	int i;
	msgStruct msg, ack;
	
	for(i=0; i < ITER*N; i++){
		
		if(msgQReceive(serverQueue, &msg, MAX_MSG_LEN, WAIT_FOREVER) == ERROR)
			printf("Server has failed receiving message\n");
		
		ack.senderType = T_SERVER;
		ack.to = msg.from;
		
		/* send acknowledge message */
		if((msgQSend(clientsQueue[msg.from], &ack, MAX_MSG_LEN, WAIT_FOREVER,MSG_PRI_NORMAL)) == ERROR)
			printf("Server has failed sending ack to %d\n",msg.from);
		
		/* send message */
		if((msgQSend(clientsQueue[msg.to], &msg, MAX_MSG_LEN, WAIT_FOREVER,MSG_PRI_NORMAL)) == ERROR)
			printf("Server has failed sending msg to %d\n",msg.to);
	}
	
	taskDelay(TIMEOUT);
	msgQDelete(serverQueue);
}
