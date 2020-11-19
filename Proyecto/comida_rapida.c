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

void* cocinero(){
	sem_wait(&vacios);
	//hace un plato
	sem_post(&ocupado);
	return NULL;
}
void* camarero(){
	sem_wait(&pedidos);
	sem_wait(&ocupado);
	//recoge el plato
	sem_post(&vacios);
	sem_post(&atencion);
	return NULL;
}
void* cliente(){
	sem_wait(&mesas_limpias);
	//elige la comida
	sem_post(&pedidos);
	//espera que lo atiendan
	sem_wait(&atencion);
	//come
	//se va
	sem_post(&mesas_sucias);
	return NULL;
}
void* limpiador(){
	sem_wait(&mesas_sucias);
	//---------
	sem_post(&mesas_limpias);
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
		pthread_create(&hilos_cocineros[i],NULL,cocinero,NULL);
	}
	for(int i=0;i<limpiadores;i++){
		pthread_create(&hilos_limpiadores[i],NULL,limpiador,NULL);
	}
	for(int i=0;i<camareros;i++){
		pthread_create(&hilos_camareros[i],NULL,camarero,NULL);
	}
	for(int i=0;i<clientes;i++){
		pthread_create(&hilos_clientes[i],NULL,cliente,NULL);
	}
	exit(0);
}
