#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#define TIME_UNIT 1
#define FILENAME "shared.h"
struct message {
	long type;
	char * body;
};
typedef struct message tMessage;
/*enlaza un bloque de memoria
**con un nombre de archivo
**lo crea si no existe*/
char* attach_memory(char* file, int size);

//desenlaza un bloque de memoria
int detach_memory(char* block);

//destruye un bloque de memoria
int destroy_memory(char* file);
#define SIZE_MSG sizeof(tMessage) - sizeof(long)
#endif
