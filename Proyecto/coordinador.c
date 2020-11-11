#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#define TIME_UNIT 1


struct task {
	int type_work;
	char dato[25];
};	
typedef struct task *tTask; // estructura de las tareas
struct info_task {
	char type;
	struct task tarea;
}; typedef struct info_task *tInfo; // estructura de los mensajes del creador de tareas

#define SIZE_MSG sizeof(struct info_task)
#define MIN_TASK 4
#define MAX_TASK 6

int pipe_a[2];
int pipe_b[2];
int pipe_c[2];
int pipe_tareas[2]; //pipe para comunicar las tareas
int pipe_coordinador[2];//pipe para coordinar

void creador_tareas(int cant_tareas){
	close(pipe_tareas[0]);
	tInfo tarea_info;
	int i = 0;
	while(i<cant_tareas){
		tarea_info = malloc(sizeof(struct info_task));
		printf("Ingrese el tipo de tarea: ");
		scanf("%s",&(tarea_info->type));
		printf("Tipo de tarea ingresado; %c\n",tarea_info->type);
		printf("Ingrese el tipo de trabajo: ");
		scanf("%d",&(tarea_info->tarea.type_work));
		printf("Tipo de trabajo ingresado: %d\n",tarea_info->tarea.type_work);
		printf("Ingrese el Dato para el trabajo: ");
		scanf("%s",tarea_info->tarea.dato);
		printf("Dato Ingresado para el trabajo: %s\n",tarea_info->tarea.dato);
		i++;
		write(pipe_tareas[1],tarea_info,sizeof(struct info_task));
		free(tarea_info);
	}
}

void tarea_a(){
	tTask tarea_actual = malloc(sizeof(struct task));
	printf("Reservo memoria en la tarea a\n");
	read(pipe_a[0],tarea_actual,sizeof(struct task));
	printf("Leo sin errores en la tarea a\n");
	char* color = tarea_actual->dato;
	printf("El color en la tarea a es :%s\n",tarea_actual->dato);
	int tarea = tarea_actual->type_work;
	printf("La tarea solicitada es la numero %d en la tarea a\n", tarea_actual->type_work);
	if(tarea == 1){ // tarea parcial
		printf("Duermo una Unidad de Tiempo en A a\n");
		sleep(1*TIME_UNIT);
		printf("Despierto en A a\n");
	}
	else{
		printf("Duermo tres Unidades de Tiempo en A a\n");
		sleep(3*TIME_UNIT);
		printf("Despierto en A a\n");
	}
	printf("Auto pintado de color %s\n",color);
	free(tarea_actual);
	int valor = 1;
	write(pipe_coordinador[1],&valor,sizeof(int));
}
void tarea_b(){
	tTask datos = malloc(sizeof(tInfo));
	int termine=read(pipe_b[0],&datos,sizeof(tInfo));
	if(termine == 0)
		printf("se ejecuto tarea B\n");
	char* ver_rep = datos->dato;
	int tarea = datos->type_work;
	if(tarea == 1){ // tarea verificar
		sleep(1*TIME_UNIT);
	}
	else
		sleep(2*TIME_UNIT);
	printf("La %s de los frenos del Auto se realizo correctamente\n",ver_rep);
	int valor = 1;
	write(pipe_coordinador[1],&valor,sizeof(int));
}
void tarea_c(){
	tTask datos = malloc(sizeof(tInfo));
	read(pipe_c[0],&datos,sizeof(tInfo));
	char* rep_bal = datos->dato;
	int tarea = datos->type_work;
	if(tarea == 1){ // tarea balanceo
		sleep(3*TIME_UNIT);
	}
	else
		sleep((tarea*TIME_UNIT)-TIME_UNIT); // la tarea son las ruedas a reparar mas uno 
	printf("La %s de las ruedas del Auto se talizo correctamente\n",rep_bal);
	int valor = 1;
	write(pipe_coordinador[1],&valor,sizeof(int));
}
void coordinador(int cant_tareas){
	close(pipe_tareas[1]);
	if (cant_tareas >= MIN_TASK && cant_tareas <= MAX_TASK){
		int i = 0;
		tInfo tipo_task;
		while (i<cant_tareas){
			read(pipe_tareas[0],&tipo_task,sizeof(struct info_task));
			printf("Leo una tarea de tipo:%c\n",(tipo_task->type));
			if(tipo_task->type == 'a'){
				write(pipe_a[1],&tipo_task->tarea,sizeof(struct task));
			}
			else
				if(tipo_task->type == 'b'){
					write(pipe_b[1],&tipo_task->tarea,sizeof(tInfo));
				}
				else{ // la tarea es de tipo c
					write(pipe_c[1],&tipo_task->tarea,sizeof(tInfo));
				}
			i++;
		}
		printf("Envie todas las tareas\n");
	}
	else 
		exit(EXIT_FAILURE);
}

int main(){
	printf("Arranca la locomotora del sabor\n");
	if(pipe(pipe_tareas) == -1){
		perror("Fallo al crear el pipe");
	}
	if(pipe(pipe_coordinador) == -1){
		perror("Fallo al crear el pipe");
	}
	if(pipe(pipe_a) == -1){
		perror("Fallo al crear el pipe");
	}if(pipe(pipe_b) == -1){
		perror("Fallo al crear el pipe");
	}if(pipe(pipe_c) == -1){
		perror("Fallo al crear el pipe");
	}
	pid_t pid_ta = fork();
	if(pid_ta < 0){
		perror("Fork tarea A");
		exit(EXIT_FAILURE);
	}
	else
		if(pid_ta == 0){ // estoy en el hijo que hace la tarea a
			tarea_a();
		}
		else{ //estoy en el padre			
			pid_t pid_tb = fork();
			if(pid_tb < 0){
				perror("Fork tarea B");
				exit(EXIT_FAILURE);
			}
			else
				if(pid_tb == 0){ // estoy en el hijo que hace la tarea a
					tarea_b();
				}
				else{ //estoy en el padre									
					pid_t pid_tc = fork();
					if(pid_tc < 0){
						perror("Fork tarea C");
						exit(EXIT_FAILURE);
					}
					else
						if(pid_tc == 0){ // estoy en el hijo que hace la tarea a
							tarea_c();
						}
						else{ //estoy en el padre
							// recibis tareas indefinidamente
							int tareas = 10;
							int i = 0;
							int termine = 0;
							while (i < tareas){
								tareas = ((random() % 3) + 4);
								creador_tareas(tareas);
								coordinador(tareas);
								printf("%d\n",tareas);
								i++;
								while(termine!= tareas){
									read(pipe_coordinador[0],NULL,sizeof(int));
									termine++;
								}
								termine = 0;
							}
							
						}
					}
			}
}
