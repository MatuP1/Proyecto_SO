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

//Funcion que lista el contendio de un directorio
void listarContenido(char *nombre){
	DIR *dir;
	struct dirent *entry;
	//Crea un stream del directorio y si no es posible retorna error.
	if((dir = opendir (nombre))== NULL)
		perror("opendir() error");
	else {
		//Recorre el directorio e imprime su contenido por pantalla.
		puts("Contenido de el directorio");
		while ((entry = readdir(dir)) !=NULL)
			printf(" %s.\n", entry ->d_name);
		//Cierra el stream creado anteriormente.
		closedir(dir);
		}
}







int main(int argc, char* arg[]){
	char directorio[20];
	printf("Escriba el nombre del directorio del que se quiera conocer el contenido.\n");
	scanf("%s",directorio);
	listarContenido(directorio);


	exit(0);
}
