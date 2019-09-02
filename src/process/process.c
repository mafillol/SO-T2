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
	process->n = 0;
	process -> cpu_shifts = 0;
	process->response_time = -1;
	process->cpu_interruption = 0;
	process->turn_around_time = 0;
	process->waiting_time = 0;
	process->priority = 0;
	process->PID = -1;

	// Retornamos el proceso
	return process;
}

// Prioridad long-sighted
int ls_priority(Process* p){
	int count = 0;
	for(int i=p->n;i<p->N;i++){
		count += p->A[i];
	}
	return count;
}

// Prioridad short-sigthed
int ss_priority(Process* p){
	if(p->status == WAITING){
		return p->A[p->n+1];
	}
	return p->A[p->n];	
}

//Destruye el proceso
void destroy_process(Process* process){
	// Liberamos las rafagas de ejecucion
	free(process->A);
	// Liberamos los tiempos de espera
	free(process->B);
	// Liberamos el proceso
	free(process);
}