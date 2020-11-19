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
#define TYPE_1 1L
#define TYPE_2 2L
#define TYPE_3 3L
#define Tespera 2


//Tipos
//Tipo1 = no hay leche.(igual al semaforo Leche)
//Tipo2 = Haytomar leche.(igual al semaforo HayLeche)
//Tipo3 = Termino de comprar
struct message{
	
	long type;
	char instrLeche[40];
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

void companiero(int tiempo,int compa,int queue,key_t key,int cantCompanieros){
		printf("Nacio el compañero : %i\n", compa);
		errno = 0;
		SMS messRCV;
		SMS messSNDT1;
		SMS messSNDT2;
		SMS messSNDT3;
		int tiempoActual;
		sleep(Tespera);
		while(1){
			int recibio = msgrcv(queue,&messRCV,SIZE_MSG,TYPE_2,IPC_NOWAIT);//Hay leche?
			if (recibio > -1){//Hay leche y me tomo 1.
				tiempoActual= time(NULL) -tiempo; 
				printf("%i : %i : Hay leche, y toma 1.\n",tiempoActual, compa);
				sleep(Tespera);
				messSNDT1.type = TYPE_1;
				msgsnd(queue, &messSNDT1, SIZE_MSG,0);
				sleep(Tespera);
			}
			else{//No hay leche
				sleep(Tespera);
				sleep(Tespera);
				int comprar = msgrcv(queue,&messRCV,SIZE_MSG,TYPE_1,IPC_NOWAIT);
				if(comprar > -1){//Alguien fue a comprar?
					//Va a comprar
					sleep(Tespera);
					tiempoActual= time(NULL) -tiempo;
					printf("%i : %i : Mira el refrigerador; no hay leche.\n",tiempoActual,compa);
					comprarLeche(compa,tiempo);
					messSNDT2.type = TYPE_2;
					sleep(Tespera);
					msgsnd(queue,&messSNDT2,SIZE_MSG,0);
					messSNDT3.type = TYPE_3;
					for(int i=0;i<cantCompanieros;i++)//Desbloqueo los otros procesos que estaban esperando la leche.
						msgsnd(queue,&messSNDT3,SIZE_MSG,0);
									
				}
				else{//Alguien fue a comprar
					tiempoActual= time(NULL) -tiempo;
					printf("%i : %i : No hay leche, pero otro fue a comprar.\n",tiempoActual, compa);
					msgrcv(queue,&messRCV,SIZE_MSG,TYPE_3,0);
					sleep(Tespera);
					
				}
				
			}
				
		}
	
	
}







int main(){
	SMS messSND;
	int n=0;
	scanf("%d",&n);
	printf("Numero de compañeros : %i\n",n);
	
	pid_t pid = getpid();
	
	key_t key = ftok(FILE_PATH, 2);
	if(key<0){
		report_and_exit("ftok");
	}
	
	int queueID = msgget(key, 0666 | IPC_CREAT);
	if(queueID<0){
		report_and_exit("msgget");
	}
	
	
	
	int tiempoInicial= time(NULL);
	int aux= 0;
	for (int i=0;i<n;i++){
			if(pid>0){
				pid = fork();
				aux = i;
			}
			
	}
	if(pid>0){
		messSND.type = TYPE_2;
		msgsnd(queueID,&messSND,SIZE_MSG,IPC_NOWAIT);
	}
	if(pid == 0){
		companiero(tiempoInicial,aux+1,queueID,key,n);
	}
	else{
			for (int i=0;i<n;i++)
				wait(NULL);
		}
	

	








}
