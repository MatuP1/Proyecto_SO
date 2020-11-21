#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#define TIME_UNIT 1

char colores[6][10] = {"Blanco","Negro","Rojo","Azul","Amarillo"};
struct mensaje{
	int cantidad;
	int tipo;
	int informacion;
}; typedef struct mensaje* msj_t;

int pipe_a[2];
int pipe_b[2];
int pipe_c[2];
int pipe_final[2];

msj_t crear_tarea_a(){
	int tipo=((random() % 2)+1);
	int cant_tareas = 2;
	int color = (rand() % 5);
	msj_t ret = malloc(sizeof(struct mensaje));
	ret->cantidad = cant_tareas;
	ret->tipo = tipo;
	ret->informacion =color;
	return ret; 
}
msj_t crear_tarea_b(int cant_tareas){
	int tipo=((random() % 2)+1);
	msj_t ret = malloc(sizeof(struct mensaje));
	ret->cantidad = cant_tareas;
	ret->tipo = tipo;
	ret->informacion = -1;
	return ret; 
}
msj_t crear_tarea_c(int cant_tareas){
	int tipo=((random() % 2)+1);
	msj_t ret = malloc(sizeof(struct mensaje));
	ret->cantidad = cant_tareas;
	ret->tipo = tipo;
	ret->informacion = ((random() % 5)+1);
	return ret;
}

void coordinador_principal(){
		int terminados = 0;
		int numero_tareas=0;
		msj_t ret;
		while(1){
			numero_tareas = ((random() % 3) + 4);
			printf("\nLa cantidad de tareas es:%i\n",numero_tareas);
			if(numero_tareas == 4){
				ret = crear_tarea_a();
				write(pipe_a[1],ret,sizeof(struct mensaje));
				ret = crear_tarea_a();
				write(pipe_a[1],ret,sizeof(struct mensaje));
				ret = crear_tarea_b(1);
				write(pipe_b[1],ret,sizeof(struct mensaje));
				ret = crear_tarea_c(1);
				write(pipe_c[1],ret,sizeof(struct mensaje));
			}
			else
				if(numero_tareas == 5){
					ret = crear_tarea_a();
					write(pipe_a[1],ret,sizeof(struct mensaje));
					ret = crear_tarea_a();
					write(pipe_a[1],ret,sizeof(struct mensaje));
					ret = crear_tarea_b(1);
					write(pipe_b[1],ret,sizeof(struct mensaje));
					ret = crear_tarea_c(2);
					write(pipe_c[1],ret,sizeof(struct mensaje));
					ret = crear_tarea_c(2);
					write(pipe_c[1],ret,sizeof(struct mensaje));
				}
				else 
					if(numero_tareas == 6){
						ret = crear_tarea_a();
						write(pipe_a[1],ret,sizeof(struct mensaje));
						ret = crear_tarea_a();
						write(pipe_a[1],ret,sizeof(struct mensaje));
						ret = crear_tarea_b(2);
						write(pipe_b[1],ret,sizeof(struct mensaje));
						ret = crear_tarea_b(2);
						write(pipe_b[1],ret,sizeof(struct mensaje));
						ret = crear_tarea_c(2);
						write(pipe_c[1],ret,sizeof(struct mensaje));
						ret = crear_tarea_c(2);
						write(pipe_c[1],ret,sizeof(struct mensaje));
					}
					else{
						printf("El numero de tareas es invalido\nW");
						exit(3);
					}
			int i=0;
			while(terminados < numero_tareas){
				read(pipe_final[0],&i,sizeof(int));
				terminados++;
			}
			printf("La cantidad de Tareas terminadas es: %i\n", terminados);
			terminados = 0;
			//sleep(1);		//este sleep es para poder ver mejor la ejecucion
		}
}

void* tarea_a(void* args){
	msj_t tarea = args;
	enum tipos_tareas {Parcial=1, Total};
	int tipo = tarea->tipo;
	int color = tarea->informacion;
	if(tipo == Parcial){
		printf("Recibi una tarea Parcial para pintar de color: %s\n", colores[color]);
		sleep(1*TIME_UNIT);
	}
	else{
		if(tipo == Total){
		printf("Recibi una tarea Total para pintar de color: %s\n", colores[color]);	
		sleep(3*TIME_UNIT);
		}
		else{
			printf("Recibi un tipo Invalido en A\n");
			exit(2);
		}
	}
	void * ret=NULL;
	free(args);
	pthread_exit(ret);
}
void* tarea_b(void* args){
	msj_t tarea = args;
	enum tipos_tareas {Verificacion=1, Reparacion};
	int tipo = tarea->tipo;
	if(tipo == Verificacion){
		printf("Recibi una tarea de Verificacion de Frenos\n");
		sleep(1*TIME_UNIT);
	}
	else{
		if(tipo == Reparacion){
		printf("Recibi una tarea de Reparacion de Frenos\n");	
		sleep(2*TIME_UNIT);
		}
		else{
			printf("Recibi un tipo Invalido en B\n");
			exit(2);
		}
	}
	void * ret=NULL;
	free(args);
	pthread_exit(ret);
}
void* tarea_c(void* args){
	msj_t tarea = args;
	enum tipos_tareas {Balanceo=1, Reparacion=2};
	int tipo = tarea->tipo;
	int ruedas = tarea->informacion;
	if(tipo == Balanceo){
		printf("Recibi una tarea de Balanceo y Rotacion de ruedas\n");
		sleep(3*TIME_UNIT);
	}
	else{
		if(tipo == Reparacion){
		printf("Recibi una tarea para Reparar %i ruedas del vehiculo\n", ruedas);	
		sleep(ruedas*TIME_UNIT);
		}
		else{
			printf("Recibi un tipo Invalido en C\n");
			exit(2);
		}
	}
	void * ret=NULL;
	free(args);
	pthread_exit(ret);
}

void coordinador_a(){
	while(1){
		int cant_tareas = 1;
		int i = 0;
		pthread_t *hilos_a;
		while(i<cant_tareas){
			msj_t tarea_corriente = malloc(sizeof(struct mensaje));
			if(tarea_corriente == NULL)
				exit(1);
			read(pipe_a[0],tarea_corriente,sizeof(struct mensaje));
			cant_tareas = tarea_corriente->cantidad;
			hilos_a = malloc(sizeof(cant_tareas *sizeof(pthread_t)));
			pthread_create(&hilos_a[i],NULL,tarea_a,tarea_corriente);
			i++;
		}
		printf("Se estan realizando %d tareas de tipo A\n",cant_tareas);
		i=0;
		while(i<cant_tareas){
			pthread_join(hilos_a[i],NULL);
			write(pipe_final[1],&i,sizeof(int));
			i++;
		}
		
	}
}
void coordinador_b(){
	while(1){
		int cant_tareas = 1;
		int i = 0;
		pthread_t *hilos_b;
		while(i<cant_tareas){
			msj_t tarea_corriente = malloc(sizeof(struct mensaje));
			if(tarea_corriente == NULL)
				exit(1);
			read(pipe_b[0],tarea_corriente,sizeof(struct mensaje));
			cant_tareas = tarea_corriente->cantidad;
			hilos_b = malloc(sizeof(cant_tareas *sizeof(pthread_t)));
			pthread_create(&hilos_b[i],NULL,tarea_b,tarea_corriente);
			i++;
		}
		printf("Se estan realizando %d tareas de tipo B\n",cant_tareas);		
		i=0;
		while(i<cant_tareas){
			pthread_join(hilos_b[i],NULL);
			write(pipe_final[1],&i,sizeof(int));
			i++;
		}
	}
}
void coordinador_c(){
	while(1){
		int cant_tareas = 1;
		int i = 0;
		pthread_t *hilos_c;
		while(i<cant_tareas){
			msj_t tarea_corriente = malloc(sizeof(struct mensaje));
			if(tarea_corriente == NULL)
				exit(1);
			read(pipe_c[0],tarea_corriente,sizeof(struct mensaje));
			cant_tareas = tarea_corriente->cantidad;
			hilos_c = malloc(sizeof(cant_tareas*sizeof(pthread_t)));
			pthread_create(&hilos_c[i],NULL,tarea_c,tarea_corriente);
			i++;
		}
		printf("Se estan realizando %d tareas de tipo C\n",cant_tareas);
		i=0;
		while(i<cant_tareas){
			pthread_join(hilos_c[i],NULL);
			write(pipe_final[1],&i,sizeof(int));
			i++;			
		}
	}
}

int main(){
	srand(time(NULL));
	pipe(pipe_a);
	pipe(pipe_b);
	pipe(pipe_c);
	pipe(pipe_final);
	int pid_a = fork();
	if(pid_a == 0){
		coordinador_a();
	}
	else{
		int pid_b = fork();
		if(pid_b == 0){
			coordinador_b();
		}
		else{
			int pid_c = fork();
			if(pid_c == 0){
				coordinador_c();
			}
			else{
				coordinador_principal();
			}
		}
	}
	exit(0);
}
