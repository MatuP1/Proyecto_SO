#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



void crearDirectorio(char *ruta){
	mkdir(ruta, 0777);
}


void eliminarDirectorio(char *ruta){
	rmdir(ruta);
}

void crearArchivo(char *nombre){
	FILE *fl;
	fl = fopen(nombre, "w");
	fclose(fl);
}

void listarContenido(char *nombre){
	DIR *dir;
	struct dirent *entry;
	
	if((dir = opendir (nombre))== NULL)
		perror("opendir() error");
	else {
		puts("Contenido de el directorio");
		while ((entry = readdir(dir)) !=NULL)
			printf(" %s\n", entry ->d_name);
		closedir(dir);
		}
}

void mostrarContenido(char *nombre){
	FILE * arch;
	
	arch = fopen(nombre, "r");
	
	char ch;
	
	if(arch == NULL)
		printf("No es posible abrir el archivo");
	
	else{
		
		do
		{
			ch = fgetc(arch);
			
			putchar(ch);
			
		}while(ch!=EOF);
		
		fclose(arch);
	}
	
	
}

void modificarPermisos(char *nombre, char *modo){
	int i;
	i= strtol(modo, 0, 8);
	if(chmod(nombre,i)<0)
		perror("Error en chmod");
	else
		printf("Se cambiaron los permisos del archivo %s",nombre);
	
}

int main(){
	char action[20];
	while(!(strcmp(action, "exit") ==0)){
		scanf("%s", action);
		if(strcmp(action, "createD") ==0){
			printf("Escriba el nombre del nuevo directorio\n");
			char rutaCrear[20];
			scanf("%s", rutaCrear);
			crearDirectorio(rutaCrear);
		}
		else if(strcmp(action, "eliminateD") ==0){
				char rutaElim[20];
				printf("Escriba el nombre del archivo a eliminar\n");
				scanf("%s", rutaElim);
				eliminarDirectorio(rutaElim);
			}
			else if(strcmp(action, "createF") ==0){
				printf("Escriba el nombre del nuevo archivo\n");
				char rutaCrear[20];
				scanf("%s", rutaCrear);
				crearArchivo(rutaCrear);
				}
				else if(strcmp(action, "listCont") ==0){
					char directorio[20];
					printf("Escriba el nombre del directorio del que se quiera conocer el contenido.\n");
					scanf("%s",directorio);
					listarContenido(directorio);
					}	
					else if(strcmp(action, "showCont") ==0){
						char archivo[20];
						printf("Escriba el nombre del archivo del que quiera conocer su contenido. \n");
						scanf("%s",archivo);
						mostrarContenido(archivo);
						}
						else if(strcmp(action, "help") ==0){
							printf("[createD] : Crea un Directorio.\n");
							printf("[eliminateD] : Elimina un Directorio.\n");
							printf("[createF] : Crea un archivo.\n");
							printf("[listCont] : Lista el contenido de un directorio.\n");
							printf("[showCont] : Muestra el contenido de un archivo.\n");
							printf("[help] : Muestra una lista con los posibles comandos.\n");
							printf("[modPer] : modifica los permisos de un archivo.\n");
							}
							else if(strcmp(action, "modPer") ==0){
									char archivo[20];
									char modo[40];
									printf("Escriba el nombre del archivo al que se le modificara los permisos.\n");
									scanf("%s", archivo);
									printf("Escriba el modo en que quiera modificarlo.\n");
									scanf("%s",modo);
									modificarPermisos(archivo,modo);
								}
								else if(strcmp(action, "exit") !=0)
									printf("Comando incorrecto, escriba 'help' para mostrar los posibles comandos.\n");
	}
	return 1;
		
						
					
	
}
