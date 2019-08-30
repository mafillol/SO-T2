#pragma once

//////////////////////////////////////////////////
//////             ESTRUCTURAS            ////////
//////////////////////////////////////////////////
/** Representa el estado de un proceso */
enum status
{
  RUNNING = 0,
  READY = 1,
  WAITING = 2,
  FINISHED = 3,
  UNDEFINED = 4,
};
typedef enum status Status;

/** Representa un proceso */
typedef struct process
{

  /** nombre del proceso */
  char name[256];
  /** Estado del proceso */
  Status status;
  /** Pid del proceso*/
  int PID;
  /** Prioridad del proceso*/
  int priority;
  /** Cantidad de rafagas de CPU*/
  int N;
  /** Array de rafagas de ejecucion*/
  int* A;
  /** Array de bloqueos*/
  int* B;
  /** Tiempo en que el proceso llega a la simulacion*/
  int start_time;
  /** Tiempo en que el proceso ingresa por primera vez a la CPU*/
  int firts_time;
} Process;

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

/** Inicializa un proceso*/
Process* init_process(char* name, int start_time, int N);

/** Destruye un proceso*/
void destroy_process(Process* process);

/** Inicializa una cola vacia*/
Queue* init_queue(int len);

/** Funcion auxiliar que quita el salto de linea*/
void strip(char* string);

//////////////////////////////////////////////////
///////        FUNCIONES PUBLICAS         ////////
//////////////////////////////////////////////////

/** Retorna una cola de procesos a partir del archivo*/
Queue* read_file(const char* name_file);

/** Destruye una cola de procesos*/
void destroy_queue(Queue* queue);