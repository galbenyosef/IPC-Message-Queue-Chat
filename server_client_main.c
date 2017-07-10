#include "server.h"

int main(){
	
	int i;
	
	/*create server queue*/
	if((serverQueue = msgQCreate(MAX_MSGS, MAX_MSG_LEN,MSG_Q_FIFO)) == NULL)
		printf("FAILED CREATING SERVER QUEUE\n");
	
	/*spawn server task*/
	if(tidServer = taskSpawn ("Server", SERV_PRIO, 0, STACK_SIZE,(FUNCPTR)server,0,0,0,0,0,0,0,0,0,0) == ERROR);
		printf("taskSpawn server failed\n");
		
	/*create N clients queues and spawn their tasks*/
	for(i=0; i<N; i++){
		
		if((clientsQueue[i] = msgQCreate(MAX_MSGS,MAX_MSG_LEN,MSG_Q_FIFO)) == NULL)
			printf("FAILED CREATING CLIENT %d QUEUE\n",i);
		
		if(tidClients[i] = taskSpawn ("Client", CLIENT_PRIO, 0, STACK_SIZE, (FUNCPTR)ClientEntryPoint,i,0,0,0,0,0,0,0,0,0) == ERROR);
			printf("taskSpawn client %d failed\n",i);
	}
	
	return 0;
}

