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












//Funcion que crea un directorio
void crearDirectorio(char *ruta){
	//Crea un archivo con los permisos 0777 por defecto, si no es posible crearlo, lo indica con un error.
	if(mkdir(ruta, 0777)==-1)
		perror("Ocurrio un error al intentar crear el directorio.\n");
	printf("Se creo el directorio con el nombre : %s.\n",ruta);
		
}





int main(int argc, char* arg[]){
	printf("Escriba el nombre del nuevo directorio\n");
	char rutaCrear[20];
	scanf("%s", rutaCrear);
	//Llama a la funcion directorio.
	crearDirectorio(rutaCrear);
	exit(0);

	










}
