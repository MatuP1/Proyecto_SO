#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#define TIME_UNIT 1


struct info_task {
int tipe_work;
char *dato;
};	
typedef struct info_task tInfo; // estructura de la info necesaria para las tareas
struct tipe_task {
	char tipe;
	tInfo info;
}; typedef struct tipe_task tTask; // estructura de los mensajes de creador de tareas

#define SIZE_MSG sizeof(tMessage)
#define MIN_TASK 4
#define MAX_TASK 6

int pipe_t[2]; //pipe para comunicar las tareas
int pipe_co[2];//pipe para coordinar

void creador_tareas(int cant_tareas){
	close(pipe_t[0]);
	tTask *tarea_nueva;
	int i = 0;
	while(i<cant_tareas){
		tarea_nueva = malloc(sizeof(tTask));
		char valor_d[25];
		tarea_nueva->info.dato = valor_d;
		printf("Ingrese el tipo de tarea: ");
		scanf("%s",&tarea_nueva->tipe);
		printf("Tipo de tarea ingresado; %c\n",tarea_nueva->tipe);
		printf("Ingrese el tipo de trabajo: ");
		scanf("%d",&tarea_nueva->info.tipe_work);
		printf("Tipo de trabajo ingresado: %d\n",tarea_nueva->info.tipe_work);
		printf("Ingrese el Dato para el trabajo: ");
		scanf("%s",tarea_nueva->info.dato);
		printf("Dato Ingresado para el trabajo: %s\n",tarea_nueva->info.dato);
		
		i++;
		write(pipe_t[1],tarea_nueva,sizeof(tTask));
		free(tarea_nueva);
	}
}

void tarea_a(){
	printf("Cierro el pipe en la tarea a\n");
	close(pipe_co[1]);
	tInfo *datos = malloc(sizeof(tInfo));
	printf("Reservo memoria en la tarea a\n");
	read(pipe_co[0],datos,sizeof(tInfo));
	printf("Leo sin errores en la tarea a\n");
	char* color = datos->dato;
	printf("El color en la tarea a es :%s\n",datos->dato);
	int tarea = datos->tipe_work;
	printf("La tarea solicitada es la numero %d en la tarea a\n", datos->tipe_work);
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
	free(datos);
}
void tarea_b(){
	close(pipe_co[1]);
	tInfo *datos = malloc(sizeof(tInfo));
	int termine=read(pipe_co[0],&datos,sizeof(tInfo));
	if(termine == 0)
		printf("se ejecuto tarea A\n");
	char* ver_rep = datos->dato;
	int tarea = datos->tipe_work;
	if(tarea == 1){ // tarea verificar
		sleep(1*TIME_UNIT);
	}
	else
		sleep(2*TIME_UNIT);
	printf("La %s de los frenos del Auto se realizo correctamente\n",ver_rep);
}
void tarea_c(){
	close(pipe_co[1]);
	tInfo *datos = malloc(sizeof(tInfo));
	read(pipe_co[0],&datos,sizeof(tInfo));
	char* rep_bal = datos->dato;
	int tarea = datos->tipe_work;
	if(tarea == 1){ // tarea balanceo
		sleep(3*TIME_UNIT);
	}
	else
		sleep((tarea*TIME_UNIT)-TIME_UNIT); // la tarea son las ruedas a reparar mas uno 
	printf("La %s de las ruedas del Auto se talizo correctamente\n",rep_bal);
}
void coordinador(int cant_tareas){
	close(pipe_co[0]);
	close(pipe_t[1]);
	if (cant_tareas >= MIN_TASK && cant_tareas <= MAX_TASK){
		int i = 0;
		tTask *tipo_task;
		while (i<cant_tareas){
			read(pipe_t[0],&tipo_task,sizeof(tTask));
			printf("Leo una tarea de tipo:%c\n",(tipo_task->tipe));
			if(tipo_task->tipe == 'a'){
				write(pipe_co[1],&tipo_task->info,sizeof(tInfo));
			}
			else
				if(tipo_task->tipe == 'b'){
					write(pipe_co[1],&tipo_task->info,sizeof(tInfo));
				}
				else{ // la tarea es de tipo c
					write(pipe_co[1],&tipo_task->info,sizeof(tInfo));
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
	if(pipe(pipe_t) == -1){
		perror("Fallo al crear el pipe");
	}
	if(pipe(pipe_co) == -1){
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
							while (i < tareas){
								tareas = ((random() % 3) + 4);
								creador_tareas(tareas);
								printf("%d\n",tareas);
								i++;
								coordinador(tareas);
								waitpid(pid_ta,NULL,0);
								waitpid(pid_tb,NULL,0);
								waitpid(pid_tc,NULL,0);
							}
							
						}
					}
			}
}
	
//HAY QUE HACERLO COMO DIJO SANTI, EL TENIA RAZON Y YO ESTABA EQUIVOCADO CHUPA VERGA DE MIERDA, A PESAR DE SU AMOR POR EL PENE MASCULINO TENIA RAZON

