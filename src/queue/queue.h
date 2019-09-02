#pragma once
#include "../process/process.h"

//////////////////////////////////////////////////
//////             ESTRUCTURAS            ////////
//////////////////////////////////////////////////

/** Representa una cola de procesos*/
typedef struct queue
{
  /** Lista de procesos*/
  Process** process_array;
  /** Largo de la cola*/
  int len; 
} Queue;


//////////////////////////////////////////////////
//////        FUNCIONES PRIVADAS          ////////
//////////////////////////////////////////////////

/** Inicializa una cola vacia*/
Queue* init_queue(int len);

/** Funcion auxiliar que quita el salto de linea*/
void strip(char* string);

/** Intercambia dos valores de la cola de procesos*/ 
void swap(Process** A,int i, int j);

//////////////////////////////////////////////////
///////        FUNCIONES PUBLICAS         ////////
//////////////////////////////////////////////////

/** Retorna una cola de procesos a partir del archivo*/
Queue* read_file(const char* name_file);

/** Destruye una cola de procesos*/
void destroy_queue(Queue* queue);

/** Verifica si la cola de procesos termino*/
int is_finished(Queue* q);

/** Ordena la cola de procesos*/
void selection_sort(Queue* q);