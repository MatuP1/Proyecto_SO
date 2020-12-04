#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define Tespera 2

sem_t HayLeche;
sem_t heladera;

struct paramThread {
	int tim;
	char *compa;
};

void comprarLeche(char *C, int tiempo){
	int tActual;
	tActual = time(NULL) - tiempo;
	printf("%i : %s : Va al supermercado.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %s : Llega al supermercado.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %s : Compra leche.\n",tActual,C);
	sleep(Tespera);
	tActual = time(NULL) - tiempo;
	printf("%i : %s : Llega a la casa; guarda la leche.\n",tActual,C);
	sem_post(&HayLeche);
	sem_post(&HayLeche);
	sem_post(&HayLeche);
	sleep(Tespera);
}

void *companiero(void *C){
	struct paramThread *estr = C;
	char *nombre = estr->compa;
	int tiempoActual,tiempoIn;
	tiempoIn=estr->tim;
	tiempoActual = time(NULL) - tiempoIn;
	printf("%i : Nacio el compañero %s.\n",tiempoActual,nombre);
	sleep(Tespera);
	while(1){
		sem_wait(&heladera);
		tiempoActual = time(NULL) - tiempoIn;
		printf("%i : %s : Mira el refrigerador...;.\n",tiempoActual,nombre);
		if(!sem_trywait(&HayLeche)){//Hay leche?
			tiempoActual = time(NULL) - tiempoIn;
			printf("%i : %s : Hay leche, y toma 1.\n",tiempoActual, nombre);
			sleep(Tespera);
			sem_post(&heladera);
		}	
		else{//No hay leche
			tiempoActual = time(NULL) - tiempoIn;
			printf("%i : %s : No hay leche, fui a comprar.\n",tiempoActual, nombre);
			comprarLeche(nombre,tiempoIn);
			sem_post(&heladera);
		}
	}
}

int main(){
	sem_init(&HayLeche,0,0);
	sem_init(&heladera,0,1);
	pthread_t compa1,compa2;
		
	int tiempoInicial;
	tiempoInicial= time(NULL); 
		
	struct paramThread *comp1;
	comp1 =(struct paramThread *)malloc(sizeof(struct paramThread));
	comp1->tim = tiempoInicial;
	comp1->compa =  malloc(sizeof(char));
	strcpy(comp1->compa,"A");
	
	struct paramThread *comp2;
	comp2 = (struct paramThread *)malloc(sizeof(struct paramThread));
	comp2->tim = tiempoInicial;
	comp2->compa = malloc(sizeof(char));
	strcpy(comp2->compa,"B");
	
	pthread_create(&compa1,NULL,companiero,comp1);
	pthread_create(&compa2,NULL,companiero,comp2);
	
	pthread_exit(NULL);

}
