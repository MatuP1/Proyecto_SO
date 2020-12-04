#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <errno.h>
#define SIZE_MSG sizeof(SMS) - sizeof(long)
#define FILE_PATH "/home/pi/Desktop/Proyecto_SO/Proyecto"
#define HAYLECHE 1L
#define HELADERALOCK 2L
#define HELADERAUNLOCK 3L
#define Tespera 2

struct message{
	
	long type;
	int tiempo;
	
}; typedef struct message SMS;

void report_and_exit(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}	



int main(){
	pid_t pid = getpid();
	SMS messSND;
	SMS messRCV;
	key_t key = ftok(FILE_PATH, 2);
	if(key<0){
		report_and_exit("ftok");
	}
	
	int queueID = msgget(key, 0666 | IPC_CREAT);
	msgctl(queueID,IPC_RMID,NULL);
	queueID = msgget(key, 0666 | IPC_CREAT);
	if(queueID<0){
		report_and_exit("msgget");
	}
	
	int tiempoInicial= time(NULL);
	
	printf("%li : %i : Desbloqueador de heladera y suministrador de tiempo creado.\n",time(NULL) - tiempoInicial,pid);	
	while(1){
		messSND.tiempo = tiempoInicial;
		messSND.type = HELADERALOCK;
		msgsnd(queueID,&messSND,SIZE_MSG,0);
		msgrcv(queueID,&messRCV,SIZE_MSG,HELADERAUNLOCK,0);
	}
	
}
