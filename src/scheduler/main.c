#include "../queue/queue.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/** Esta función es lo que se llama al ejecutar tu programa */
int main(int argc, char *argv[]){

  Queue* queue = read_file(argv[1]);

  char* version = argv[3];

  int current_time = 0;
  int pid = 0;

  // Mientras no terminemos todos los procesos
  while(!is_finished(queue)){
    //Variable auxiliar para ver si un proceso ya corrio en el ciclo 
    bool run = false; 
    for(int i=0;i<queue->len;i++){
      Process* p = queue->process_array[i];
      //Revisamos si algun proceso "llega"
      if(p->start_time==current_time && p->status==UNDEFINED){
        p->status = READY;
        p->PID = pid;
        pid++;
      }
      // Asignamos nueva prioridad
      if(strcmp(version,"ss") == 0){
        if(p->priority != ss_priority(p)){
          p->priority = ss_priority(p);
        }
      }
      else{
        if(p->priority != ls_priority(p)){
          p->priority = ls_priority(p);
        }
      }
      // Ordenamos la cola
      selection_sort(queue);

      // Corremos el proceso
      if((p->status == RUNNING || p->status == READY) && run == false){
        if(p->status == RUNNING){
          p->A[p->n]--;
        }
        else{
          p->status = RUNNING;
          p->A[p->n]--;
        }
        if(p->first_time == -1){
          p->first_time = current_time;
        }
        run = true;
      }
      // Veo si el proceso fue sacado
      else if(p->status == RUNNING){
        p->status = READY;
        p->cpu_interruption++;
      }
      // Reduzco un tiempo de espera
      else if(p->status == WAITING){
        p->B[p->n]--;
      } 


      // Revisamos si algun proceso termina
      if(p->n == p->N-1 && p->A[p->n] == 0 &&p->status == RUNNING){
        p->status = FINISHED;
      }

      // Revisamos si algun poceso pasa a waiting
      else if(p->status == RUNNING && p->A[p->n] == 0){
        p->status = WAITING;
      }

      // Revisamos si algun proceso pasa a ready
      else if(p->status == WAITING && p->n<p->N+2 && p->B[p->n] == 0){
        p->status = READY;
        p->n ++;
      }

    }

    //Actualizamos el tiempo
    current_time++;
  }

  // Escribimos el archivo de salida
  FILE* file = fopen(argv[2], "w");

    for(int i=0; i<queue->len; i++){
      Process* p = queue->process_array[i];
      fprintf(file, "%s,%d,%d\n", p->name,p->cpu_shifts, p->cpu_interruption);
    }
  // Cerramos el archivo de salida
  fclose(file);
  // Liberamos la memoria
  destroy_queue(queue);
  return 0;
}