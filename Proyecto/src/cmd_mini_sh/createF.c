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




//Funcion que crea un archivo
void crearArchivo(char *nombre){
	FILE *fl;
	fl = fopen(nombre, "w");
	fclose(fl);
	printf("Se creo el archivo con el nombre : %s.\n",nombre);
}


int main(int argc, char* arg[]){
	printf("Escriba el nombre del nuevo archivo\n");
	char rutaCrear[20];
	scanf("%s", rutaCrear);
	crearArchivo(rutaCrear);






	exit(0);
}
