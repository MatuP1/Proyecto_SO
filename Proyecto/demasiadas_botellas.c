#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define Tespera 2

sem_t leche;
sem_t HayLeche;

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
		if(sem_trywait(&HayLeche)){
		
		
		
			if(sem_trywait(&leche)){
				tiempoActual = time(NULL) - tiempoIn;
				printf("%i : %s : No hay leche, pero otro fue a comprar.\n",tiempoActual, nombre);
				sleep(5*Tespera);
			}
			else{
				tiempoActual = time(NULL) - tiempoIn;
				printf("%i : %s : Mira el refrigerador; no hay leche.\n",tiempoActual,nombre);
				sleep(Tespera);
				comprarLeche(nombre,tiempoIn);
				}
			}
		else{
			printf("%i : %s : Hay leche, y toma 1.\n",tiempoActual, nombre);
			sleep(Tespera);
			sem_post(&leche);
		}	
	
	
	}
}

int main(){
	sem_init(&leche,0,1);
	sem_init(&HayLeche,0,0);
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
