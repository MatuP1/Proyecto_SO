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

void comprarLeche(int C, int tiempo){
	int tActual;
	tActual = time(NULL) - tiempo;
	printf("%i : %i : Va al supermercado.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %i : Llega al supermercado.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %i : Compra leche.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %i : Llega a la casa; guarda la leche.\n",tActual,C);
	sleep(Tespera);
}

void companiero(int compa,int queue){
		SMS messRCVHeladera;
		SMS messRCVHayLeche;
		SMS messSNDHayLeche;
		SMS messSNDHeladera;
		int tiempoActual;
		sleep(Tespera);
		while(1){
			msgrcv(queue,&messRCVHeladera,SIZE_MSG,HELADERALOCK,0);
			tiempoActual= time(NULL)-messRCVHeladera.tiempo;
			printf("%i : %i : Mira el refrigerador...;.\n",tiempoActual,compa);
			sleep(Tespera);//Revisa la heladera. 
			int recibio = msgrcv(queue,&messRCVHayLeche,SIZE_MSG,HAYLECHE,IPC_NOWAIT);//No Hay leche?
			if (recibio > -1){//Hay leche y la toma.
				recibio = 0;
				tiempoActual= time(NULL)-messRCVHeladera.tiempo;
				printf("%i : %i : Hay leche, y la tomo.\n",tiempoActual, compa);
				sleep(Tespera);//Toma la leche
			}
			else{//No hay leche
				tiempoActual= time(NULL)-messRCVHeladera.tiempo;
				printf("%i : %i : No hay leche, fui a comprar.\n",tiempoActual,compa);
				comprarLeche(compa,messRCVHeladera.tiempo);
				//Cargo leche(3).
				messSNDHayLeche.type= HAYLECHE;
				msgsnd(queue,&messSNDHayLeche,SIZE_MSG,0);
				msgsnd(queue,&messSNDHayLeche,SIZE_MSG,0);
				msgsnd(queue,&messSNDHayLeche,SIZE_MSG,0);
				//Desbloqueo heladera.
				
				sleep(Tespera);													
				}
		messSNDHeladera.type = HELADERAUNLOCK;
		msgsnd(queue,&messSNDHeladera,SIZE_MSG,0);		
		}
		
}
	





















int main(){
	pid_t pid = getpid();
	
	key_t key = ftok(FILE_PATH, 2);
	if(key<0){
		report_and_exit("ftok");
	}
	
	int queueID = msgget(key, 0666 | IPC_CREAT);
	if(queueID<0){
		report_and_exit("msgget");
	}
	companiero(pid,queueID);
	
	
	
	
}
