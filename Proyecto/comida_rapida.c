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
	sem_wait(&pedido);
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

