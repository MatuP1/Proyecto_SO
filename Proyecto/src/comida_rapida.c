#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t vacios; //lugares para platos
sem_t ocupado; //lugares ocupados
sem_t mesas_limpias;
sem_t mesas_sucias;
sem_t pedidos;
sem_t atencion;

void* cocinero(void* num_cocinero){
	int numero_c = (int) num_cocinero;
	while(1){
		sem_wait(&vacios);
		//hace un plato
		printf("Estoy cocinando. Cocinero:%i \n",numero_c);
		sleep(2);
		printf("Plato listo para servir del Cocinero:%i \n",numero_c);
		sem_post(&ocupado);
	}
	pthread_exit(NULL);
	return NULL;
}
void* camarero(){
	while(1){
		sem_wait(&pedidos);
		sem_wait(&ocupado);
		//recoge el plato
		printf("Tome un plato de la cola\n");
		sem_post(&vacios);
		sleep(1);
		printf("Cliente atendido\n");
		sem_post(&atencion);
	}
	pthread_exit(NULL);
	return NULL;
}
void* cliente(void* num_cliente){
	int numero_c = (int)num_cliente;
	printf("Esperando una mesa limpia.....Cliente:%i\n",numero_c);
	sem_wait(&mesas_limpias);
	//elige la comida
	sleep(1);
	sem_post(&pedidos);
	//espera que lo atiendan
	sem_wait(&atencion);
	//come
	//sleep(10);
	//se va
	printf("Adios Cliente:%i\n",numero_c);
	sem_post(&mesas_sucias);
	pthread_exit(NULL);
	return NULL;
}
void* limpiador(){
	while(1){
		sem_wait(&mesas_sucias);
		//limpia la mesa
		sleep(2);
		sem_post(&mesas_limpias);
	}
	pthread_exit(NULL);
	return NULL;
}
int main(){
	
	int clientes = 50;
	int limpiadores = 1;
	int cocineros = 3;
	int camareros = 1;
	
	sem_init(&vacios,0,10);
	sem_init(&mesas_limpias,0,30);
	sem_init(&mesas_sucias,0,0);
	sem_init(&ocupado,0,0);
	sem_init(&pedidos,0,0);
	sem_init(&atencion,0,0);
	
	pthread_t hilos_clientes[clientes];
	pthread_t hilos_limpiadores[limpiadores];
	pthread_t hilos_cocineros[cocineros];
	pthread_t hilos_camareros[camareros];
	
	for(int i=0;i<cocineros;i++){
		void* valor = (void*)i;
		pthread_create(&hilos_cocineros[i],NULL,cocinero,valor);
	}
	for(int i=0;i<limpiadores;i++){
		pthread_create(&hilos_limpiadores[i],NULL,limpiador,NULL);
	}
	for(int i=0;i<camareros;i++){
		pthread_create(&hilos_camareros[i],NULL,camarero,NULL);
	}
	for(int i=0;i<clientes;i++){
		void* valor = (void*)i;
		pthread_create(&hilos_clientes[i],NULL,cliente,valor);
	}
	//bucles de join de hilos
	for(int i=0;i<cocineros;i++){
		pthread_join(hilos_cocineros[i],NULL);
	}
	for(int i=0;i<limpiadores;i++){
		pthread_join(hilos_limpiadores[i],NULL);
	}
	for(int i=0;i<camareros;i++){
		pthread_join(hilos_camareros[i],NULL);
	}
	for(int i=0;i<clientes;i++){
		pthread_join(hilos_clientes[i],NULL);
	}
	
	exit(0);
}
