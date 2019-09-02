////////////////////////////////////////////////////////////////////////////////////////
// IMPORTANTE - REFERENCIA                                                            //
// Quita el salto de linea a un string obtenida de                                    //
// https://cboard.cprogramming.com/c-programming/70320-how-remove-newline-string.html //
////////////////////////////////////////////////////////////////////////////////////////

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
// Verifica si todos los procesos de la cola terminaron
int is_finished(Queue* q){
	for(int i=0; i<q->len;i++){
		if(q->process_array[i]->status != FINISHED){
			return 0;
		}
	}
	return 1;
}

// Funcion auxiliar para intercambiar dos valores de un array
void swap(Process** A,int i, int j){
	Process* temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

// Selection sort de una cola
// Forma de ordenar basado en diapos del curso Estructuras de Datos 2-2019
// usado en Tarea 0 de Estructuras de Datos 2-2019 por mi (github user: mafillol),
// pero tambien se puede encontrar en link: https://www.geeksforgeeks.org/selection-sort/
void selection_sort(Queue* q){

	for(int i=0; i< q->len-1; i++){
		int pos_min = i;

		for(int j=i+1; j<q->len; j++){

			if(q->process_array[j]->priority < q->process_array[pos_min]->priority){
				pos_min = j;
			}
			else if(q->process_array[j]->priority == q->process_array[pos_min]->priority){
				if(q->process_array[j]->PID > q->process_array[pos_min]->PID){
					pos_min = j; 
				}
			}
		}

		if(i != pos_min){
			swap(q->process_array, i, pos_min);
		}
	}
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