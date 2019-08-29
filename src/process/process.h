#pragma once
//////////////////////////////////////////////////
//////             ESTRUCTURAS            ////////
//////////////////////////////////////////////////
/** Representa el estado de un programa */
enum status
{
  RUNNING = 0,
  READY = 1,
  WAITING = 2,
  FINISHED = 3,
};
typedef enum status Status;

typedef struct proces
{

  /** nombre del programa */
  char name[256];
  /** Estado del proceso */
  Status status;
  /** Pid del proceso*/
  int PID;

} Process;

//////////////////////////////////////////////////
//////        FUNCIONES PRIVADAS          ////////
//////////////////////////////////////////////////


/** Crea un programa nuevo*/ 
Program* init_program(int n_arg, char* name);

/** Quita el salto de linea a un string*/
void strip(char* string);

//////////////////////////////////////////////////
///////        FUNCIONES PUBLICAS         ////////
//////////////////////////////////////////////////

/** Lee el archivo y entrega la lista de programas*/
Program** read_file(const char* name_file);
/** Destruimos el programa*/
void destroy_program(Program* program);