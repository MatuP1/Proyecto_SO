#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


//Funcion que crea un directorio
void crearDirectorio(char *ruta){
	//Crea un archivo con los permisos 0777 por defecto, si no es posible crearlo, lo indica con un error.
	if(mkdir(ruta, 0777)==-1)
		perror("Ocurrio un error al intentar crear el directorio");
		
}

//Funcion que elimina un directorio
void eliminarDirectorio(char *ruta){
	if(rmdir(ruta)==-1)
		perror("Ocurrio un error al inentar eliminar el directorio");
}
//Funcion que crea un archivo
void crearArchivo(char *nombre){
	FILE *fl;
	fl = fopen(nombre, "w");
	fclose(fl);
}
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
			printf(" %s\n", entry ->d_name);
		//Cierra el stream creado anteriormente.
		closedir(dir);
		}
}
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
//Funcion que modifica los permisos de un archivo.
void modificarPermisos(char *nombre, char *modo){
	int i;
	i= strtol(modo, 0, 8);
	if(chmod(nombre,i)<0)
		perror("Error en chmod");
	else
		printf("Se cambiaron los permisos del archivo %s",nombre);
	
}

int main(){
	//El tamaño maximo de los comandos es de 20 caracteres al igual que los nombres de archivos o directorios.
	char action[20];
	while(!(strcmp(action, "exit") ==0)){
		//Lee de la consola el comando a ejecutar.
		scanf("%s", action);
		//Crea un directorio.
		if(strcmp(action, "createD") ==0){
			printf("Escriba el nombre del nuevo directorio\n");
			char rutaCrear[20];
			scanf("%s", rutaCrear);
			crearDirectorio(rutaCrear);
		}//Elimina un directorio.
		else if(strcmp(action, "eliminateD") ==0){
				char rutaElim[20];
				printf("Escriba el nombre del archivo a eliminar\n");
				scanf("%s", rutaElim);
				eliminarDirectorio(rutaElim);
			}//Crea un archivo.
			else if(strcmp(action, "createF") ==0){
				printf("Escriba el nombre del nuevo archivo\n");
				char rutaCrear[20];
				scanf("%s", rutaCrear);
				crearArchivo(rutaCrear);
				}//Muestra el contenido de un directorio.
				else if(strcmp(action, "listCont") ==0){
					char directorio[20];
					printf("Escriba el nombre del directorio del que se quiera conocer el contenido.\n");
					scanf("%s",directorio);
					listarContenido(directorio);
					}//Muestra el contenido de un archivo.
					else if(strcmp(action, "showCont") ==0){
						char archivo[20];
						printf("Escriba el nombre del archivo del que quiera conocer su contenido. \n");
						scanf("%s",archivo);
						mostrarContenido(archivo);
						}//Muestra los comandos disponibles.
						else if(strcmp(action, "help") ==0){
							printf("[createD] : Crea un Directorio.\n");
							printf("[eliminateD] : Elimina un Directorio.\n");
							printf("[createF] : Crea un archivo.\n");
							printf("[listCont] : Lista el contenido de un directorio.\n");
							printf("[showCont] : Muestra el contenido de un archivo.\n");
							printf("[help] : Muestra una lista con los posibles comandos.\n");
							printf("[modPer] : modifica los permisos de un archivo.\n");
							}//Permite cambiar los permisos de un archivo.
							else if(strcmp(action, "modPer") ==0){
									char archivo[20];
									char modo[40];
									printf("Escriba el nombre del archivo al que se le modificara los permisos.\n");
									scanf("%s", archivo);
									printf("Escriba el modo en que quiera modificarlo.\n");
									scanf("%s",modo);
									modificarPermisos(archivo,modo);
								}//Muestra error al utilizar un comando no implemento o inexistente.
								else if(strcmp(action, "exit") !=0)
									printf("Comando incorrecto, escriba 'help' para mostrar los posibles comandos.\n");
	}
	printf("Termino la ejecucion del miniShell.\n");
	return 1;
		
						
					
	
}
