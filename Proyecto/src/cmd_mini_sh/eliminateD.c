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



//Funcion que elimina un directorio
void eliminarDirectorio(char *ruta){
	if(rmdir(ruta)==-1)
		perror("Ocurrio un error al inentar eliminar el directorio.\n");
}






int main(int argc, char* arg[]){
	printf("Escriba el nombre del archivo a eliminar\n");
	char rutaElim[20];
	scanf("%s", rutaElim);
	eliminarDirectorio(rutaElim);



	exit(0);
}
