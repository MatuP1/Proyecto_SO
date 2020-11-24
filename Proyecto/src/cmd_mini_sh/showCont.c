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


//Funcion que muestra el contenido de un archivo
void mostrarContenido(char *nombre){
	FILE * arch;
	//Abre el archivo con el nombre recibido.
	arch = fopen(nombre, "r");
	char ch;
	//Si es NULL es porque no existe el archivo o no se pude acceder a el.
	if(arch == NULL)
		printf("No es posible abrir el archivo");
	else{
		//Mientras no llegue al final del archivo, imprime su contenido en pantalla.
		do
		{
			ch = fgetc(arch);
			putchar(ch);
		}while(ch!=EOF);
		//Cierra el archivo.
		fclose(arch);
	}
	
	
}










int main(int argc, char* arg[]){
	char archivo[20];
	printf("Escriba el nombre del archivo del que quiera conocer su contenido. \n");
	scanf("%s",archivo);
	mostrarContenido(archivo);
	printf("\n");


	exit(0);
}
