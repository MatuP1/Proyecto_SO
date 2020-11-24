#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>


int main(int argc, char* arg[]){

	pid_t procesoComando;
	char action[20];
	char route[40];
	printf("Bienvenido a la Mini Shell de Santiago y Matias, Ingrese sus comandos\n");
	while(!(strcmp(action, "exit") == 0)){
		//Lee de la consola el comando a ejecutar.
		scanf("%s", action);
		//Borra lo que esta escrito en el string route.
		memset(route,0,40);
		route[0] = '.';
		route[1] = '/';
		strcat(route,action);
		//Crea el proceso hijo para ejecutar el comando deseado.
		procesoComando = fork();
		if(procesoComando<0)
				perror("Fallo la creacion del procesoComando");
		else
			if(procesoComando == 0){
				if(execlp(route,route,NULL)<0)
					printf("Comando incorrecto, escriba 'help' para mostrar los posibles comandos.\n");
			}else
				waitpid(procesoComando,NULL,0);
	}
	exit(0);
}
