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

#define SIZE_MSG sizeof(struct message) - sizeof(long)
#define FILE_PATH "/home/pi/Desktop/Proyecto_SO/Proyecto"
//mensajes para la cola
#define VEGGIE 1L
#define NORMAL 2L
#define MESAS_LIMPIAS 3L
#define MESAS_SUCIAS 4L
#define COCINA_VACIA 5L
#define COCINA_LLENA 6L
#define ATENCION 7L

struct message{	
	long type;
	char * msg;
}; typedef struct message *info;

void report_and_exit(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}	

void cocinero(int num_cocinero, int queue){
	info cocina = malloc(sizeof(struct message));
	while(1){
		msgrcv(queue,cocina,SIZE_MSG,COCINA_VACIA,0);
		//hace un plato
		printf("Estoy cocinando. Cocinero:%i \n",num_cocinero);
		sleep(2);
		printf("Plato listo para servir del Cocinero:%i \n",num_cocinero);
		//lo agrega a los platos listos
		cocina->type = COCINA_LLENA;
		msgsnd(queue,cocina,SIZE_MSG,0);
	}
}
void camarero(int num_camarero, int queue){
	info bandeja = malloc(sizeof(struct message));
	while(1){
		//long tipo_pedidos= (long)(-VEGGIE); //No entiendo porque esto no anda
		msgrcv(queue,bandeja,SIZE_MSG,(-2L),0);
		msgrcv(queue,bandeja,SIZE_MSG,COCINA_LLENA,0);
		//recoge el plato
		printf("Tome un plato de la cola\n");
		bandeja->type = COCINA_VACIA;
		msgsnd(queue,bandeja,SIZE_MSG,0);
		sleep(1);
		printf("Cliente atendido\n");
		bandeja->type=ATENCION;
		msgsnd(queue,bandeja,SIZE_MSG,0);
	}
}
void cliente(int num_cliente, int queue){
	printf("Esperando una mesa limpia.....Cliente:%i\n",num_cliente);
	info mesa_limpia = malloc(sizeof(struct message));
	msgrcv(queue,mesa_limpia,SIZE_MSG,MESAS_LIMPIAS,0);
	//elige la comida
	sleep(1);
	info pedido = malloc(sizeof(struct message));
	int i = random() % 2;
	if(i == 0){
		pedido->type = VEGGIE;
		msgsnd(queue,pedido,SIZE_MSG,0);
	}
	else{
		pedido->type = NORMAL;
		msgsnd(queue,pedido,SIZE_MSG,0);
	}
	//espera que lo atiendan
	msgrcv(queue,pedido,SIZE_MSG,ATENCION,0);
	//come
	//sleep(10);
	//se va
	printf("Adios Cliente:%i\n",num_cliente);
	mesa_limpia->type = MESAS_SUCIAS;
	msgsnd(queue,mesa_limpia,SIZE_MSG,0);
	exit(1);
}
void limpiador(int num_limpiador, int queue){
	info mesa_sucia = malloc(sizeof(struct message));
	while(1){
		msgrcv(queue,mesa_sucia,SIZE_MSG,MESAS_SUCIAS,0);
		//limpia la mesa
		sleep(2);
		mesa_sucia->type = MESAS_LIMPIAS;
		msgsnd(queue,mesa_sucia,SIZE_MSG,0);
	}
}

int main(){
	pid_t pid = getpid();
	
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
	info mesa_limpia = malloc(sizeof(struct message));
	info vacio = malloc(sizeof(struct message));
	if(pid>0){ // envio las mesas limpias
		mesa_limpia->type = MESAS_LIMPIAS;
		for(int i = 0; i<30; i++){
			msgsnd(queueID,mesa_limpia,SIZE_MSG,IPC_NOWAIT);
		}
		vacio->type = COCINA_VACIA;
		for(int i=0; i<10; i++){
			msgsnd(queueID,vacio,SIZE_MSG,IPC_NOWAIT);
		}
	}
	//creo los clientes
	for (int i=0;i<50;i++){
			if(pid>0){
				pid = fork();
				if(pid == 0){ // estoy en un cliente
					cliente(getpid()%50,queueID);
				}
			}
	}
	
	if(pid>0){
		for(int i=0;i<3;i++){ //creo los cocineros
			if(pid>0){
				pid = fork();
			}
		}
		
		if(pid == 0){ //estoy en un cocinero
			cocinero(getpid()%3,queueID);
		}
		else{
			pid = fork(); //creo al camarero
			if(pid == 0){
				camarero(getpid(),queueID);
			}
			else{
				pid = fork(); //creo al limpiador de mesas
				if(pid==0){
					limpiador(getpid(),queueID);
				}
				else{ //estoy en el padre espero a los hijos
					for(int i=0; i<55; i++){
						wait(NULL);
					}
				}
			}
		}
	}
	
}
