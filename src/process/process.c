////////////////////////////////////////////////////////////////////////////////////////
// IMPORTANTE - REFERENCIA                                                            //
// Quita el salto de linea a un string obtenida de                                    //
// https://cboard.cprogramming.com/c-programming/70320-how-remove-newline-string.html //
////////////////////////////////////////////////////////////////////////////////////////

#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Entrega un puntero a un prceso 
Process* init_process(char* name, int start_time, int N){
	// Pido memoria para el proceso
	Process* process = malloc(sizeof(Process));

	strcpy(process->name, name);
	process->status = UNDEFINED;
	process->N = N;
	process->A = (int*)calloc(N, sizeof(int));
	process->B = (int*)calloc(N-1, sizeof(int));
	process->start_time = start_time;

	// Retornamos el proceso
	return process;
}
Queue* init_queue(int len){
	// Pido memoria para la cola
	Queue* q = malloc(sizeof(Queue));

	q->process_array =(Process**)calloc(len,sizeof(Process*));
	q->len = len;

	// Retornamos la cola
	return q;
}
//Lee el archivo y retorna una cola con procesos
Queue* read_file(const char* name_file){

	//Inicializo variables auxiliares para leer el archivo
	char* line = NULL; 
	size_t size = 0;

	// Abro el archivo
	FILE* file = fopen(name_file, "r");
	getline(&line, &size, file);
	strip(line);
	// Cantidad de procesos en el archivo
	int M = atoi(line);

	//Declaramos una cola de procesos
	Queue* queue = init_queue(M);

	//Por cada uno de los procesos
	for(int i=0; i<M; i++){
		getline(&line, &size, file);
		//strip(line);
		char* name = strtok(line, " ");
		int start_time = atoi(strtok(NULL, " "));
		int N = atoi(strtok(NULL, " "));

		// Inicializamos un nuevo proceso
		Process* process = init_process(name, start_time, N);

		for(int j=0;j<N;j++){
			// Asignamos rafaga de ejecucion
			process->A[j] = atoi(strtok(NULL, " "));
			if(j+1<N){
				// Asignamos tiempo de espera
				process->B[j] = atoi(strtok(NULL, " "));
			}
		}

		queue->process_array[i] = process;
	}

	//Liberamos la linea
	free(line);
	//Cerramos el archivo
	fclose(file);	
	//Retornamos la cola con los procesos
	return queue;
}

//Destruye el proceso
void destroy_process(Process* process){
	// Liberamos las rafagas de ejecucion
	free(process->A);
	// Liberamos los tiempos de espera
	free(process->B);
	// Liberamos el nombre
	free(process->name); //// VERIFICAR SI ES NECESARIO
	// Liberamos el proceso
	free(process);
}

//Destruye la cola de procesos
void destroy_queue(Queue* queue){
	// Destruimos cada uno de los procesos
	for(int i=0; i<queue->len; i++){
		destroy_process(queue->process_array[i]);
	}
	// Liberamos el array de procesos
	free(queue->process_array);
	// Liberamos la cola
	free(queue);
}

//Funcion auxiliar. Quita el salto de linea a un string
//Obtenida del link: 
//https://cboard.cprogramming.com/c-programming/70320-how-remove-newline-string.html
void strip(char* string){
  string[strcspn (string,"\n")] = '\0';
}




////////////////////////////////////////////////////////////////////////////////////////
// IMPORTANTE - REFERENCIA                                                            //
// Quita el salto de linea a un string obtenida de                                    //
// https://cboard.cprogramming.com/c-programming/70320-how-remove-newline-string.html //
////////////////////////////////////////////////////////////////////////////////////////