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




//Muestra los comandos disponibles.
void helper(){
	printf("[createD] : Crea un Directorio.\n");
	printf("[eliminateD] : Elimina un Directorio.\n");
	printf("[createF] : Crea un archivo.\n");
	printf("[listCont] : Lista el contenido de un directorio.\n");
	printf("[showCont] : Muestra el contenido de un archivo.\n");
	printf("[help] : Muestra una lista con los posibles comandos.\n");
	printf("[modPer] : modifica los permisos de un archivo.\n");
}










int main(int argc, char* arg[]){
	helper();
	exit(0);
}
