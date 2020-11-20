#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shared.h"

static int get_shared_block(char* file, int size){
	//creo la llave de la memoria compartida
	key_t key = ftok(FILENAME, 0);
	if (key == -1){
		perror("Fallo la creacion de la llave");
		return -1;
	}
	return shmget(key,size,0666|IPC_CREAT);
}

char* attach_memory(char* file, int size){
	int sh_mem_id = get_shared_block(file,size);
	char* ret;
	if(sh_mem_id == -1){
		perror("fallo la creacion de memoria");
		return (char*)-1;
	}
	
	ret = shmat(sh_mem_id,NULL,0);
	if(ret == (char*)-1){
		perror("No existe o no es posible acceder a la memoria compartida");
		return NULL;
	}
	return ret;
}

int detach_memory(char* block){
	int ret = 0;
	if(shmdt(block) != -1)
		ret = 1;
	return ret;
}

int destroy_memory(char* file){
	int sh_mem_id = get_shared_block(file,0);
	if(sh_mem_id == -1){
		perror("Fallo al eliminar la memoria compartida");
		return -1;
	}
	return (shmctl(sh_mem_id,IPC_RMID,NULL)!=-1);
}
