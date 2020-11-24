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


//Funcion que modifica los permisos de un archivo.
void modificarPermisos(char *nombre, char *modo){
	
	
	//Reset errno a 0 antes de la llamada
	errno=0;
	int largo = strlen(modo);
	char *endptr = NULL;
	int i;
	i= strtol(modo, &endptr, 8);
	//Verifico que modo es un numero octal (0+3 cifras)
	if(modo == endptr || largo != 4)
		printf("El modo ingresado no corresponde a un numero octal de 4 cifras.\n");
	else
		if( i<0 || i>999)
			printf("El modo ingresado no corresponde a un numero octal de 4 cifras.\n");
		else
			if(errno == ERANGE && i ==LONG_MIN)
				printf("Ocurrio un underflow.\n");
			else
				if(errno == ERANGE && i == LONG_MAX)
					printf("Ocurrio un overflow.\n");
				else
					if(errno == ERANGE)
						printf( "base contiene valor no soportado.\n");
					else
						if(errno != 0 && i == 0)
							printf("Ocurrio un error no especificado.\n");
						else
							if(errno == 0 && modo && *endptr != 0)
								printf("Contiene un modo pero tambien contiene caracteres.\n");
							else
								if(chmod(nombre,i)<0)
									perror("Error en chmod");
								else
									printf("Se cambiaron los permisos del archivo %s.\n",nombre);
	
}






int main(int argc, char* arg[]){

	char archivo[20];
	char modo[40];
	printf("Escriba el nombre del archivo al que se le modificara los permisos.\n");
	scanf("%s", archivo);
	printf("Escriba el modo en que quiera modificarlo.\n");
	scanf("%s",modo);
	modificarPermisos(archivo,modo);



	exit(0);
}
