#include "../queue/queue.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


/** Esta función es lo que se llama al ejecutar tu programa */
int main(int argc, char *argv[]){

  Queue* queue = read_file(argv[1]);

  int current_time = 0;
  int pid = 0;

  // Mientras no terminemos todos los procesos
  while(!is_finished(queue)){
    
    for(int i=0;i<queue->len;i++){
      Process* p = queue->process_array[i];
      //Revisamos si algun proceso "llega"
      if(p->start_time==current_time && p->status==UNDEFINED){
        p->status = READY;
        p->PID = pid;
        pid++;
      }
      
      // Revisamos si algun proceso termina
      if(p->n==p->N && p->status==RUNNING){
        p->status = FINISHED;
      }

      // Asignamos nueva prioridad
      if(p->priority)
    }

    for(int i=0;i<queue->len;i++){
      Process* p = queue->process_array[i];
      printf("%i\n", ss_priority(p) );
    }
    break;
  }

  destroy_queue(queue);
  return 0;
}