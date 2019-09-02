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
    }

    //Variable auxiliar para ver si un proceso ya corrio en el ciclo 
    bool run = false; 
    for(int i=0;i<queue->len;i++){
      Process* p = queue->process_array[i];

      // Corremos el proceso
      if((p->status == RUNNING || p->status == READY) && run == false){
        if(p->status == RUNNING){
          p->A[p->n]--;
        }
        // Proceso a correr saco a otro proceso
        else if (p->status == READY){
          p->status = RUNNING;
          p->A[p->n]--;
          p->cpu_shifts++;
          p->waiting_time++;
        }

        // Asignamos tiempo de respuesta
        if(p->response_time == -1){
          p->response_time = current_time - p->start_time;
        }
        run = true;
      }

      // Veo si el proceso fue sacado
      else if(p->status == RUNNING){
        p->status = READY;
        p->cpu_interruption++;
      }
      // Reduzco un tiempo de espera
      if(p->status == WAITING){
        p->B[p->n]--;
        p->waiting_time++;
      }
      // Aumento un tiempo de espera
      else if(p->status == READY){
        p->waiting_time++;
      } 


      // Revisamos si algun proceso termina
      if(p->n == p->N-1 && p->A[p->n] == 0 && p->status == RUNNING){
        p->status = FINISHED;
        p->turn_around_time = current_time + 1 - p->start_time; //Reviasar el +1
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
      fprintf(file, "%s,%d,%d,%d,%d,%d\n", p->name,p->cpu_shifts, p->cpu_interruption, p->turn_around_time, p->response_time,p->waiting_time);
    }
  // Cerramos el archivo de salida
  fclose(file);
  // Liberamos la memoria
  destroy_queue(queue);
  return 0;
}