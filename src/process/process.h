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
  int first_time;
  /** Posicion actual en que se va recorriendo A y B*/
  int n;
  /** Cantidad de veces que fue elegido para usar la CPU*/
  int cpu_shifts;
  /** Cantidad de veces que la CPU fue interrumpida*/
  int cpu_interruption;
} Process;


//////////////////////////////////////////////////
//////        FUNCIONES PRIVADAS          ////////
//////////////////////////////////////////////////

/** Inicializa un proceso*/
Process* init_process(char* name, int start_time, int N);

/** Destruye un proceso*/
void destroy_process(Process* process);

//////////////////////////////////////////////////
///////        FUNCIONES PUBLICAS         ////////
//////////////////////////////////////////////////

/** Prioridad long-sighted de un proceso*/
int ls_priority(Process* p);

/** Prioridad short-sigthed de un proceso*/
int ss_priority(Process* p);