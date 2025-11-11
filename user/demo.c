#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child_process(int tickets, int id)
{
  settickets(tickets);
  int count = 0;
  for(int i = 0; i < 1000000; i++) {
    count += i * i;
    if(i % 100000 == 0) {
      printf("Proceso %d (tickets: %d) trabajando...\n", id, tickets);
    }
  }
  printf("Proceso %d terminó\n", id);
  exit(0);
}

int main()
{
  int N = 10;
  printf("Iniciando demo con %d procesos...\n", N);
  
  for(int i = 0; i < N; i++) {
    int tickets = 50 * (i + 1);
    int pid = fork();
    
    if(pid == 0) {
      child_process(tickets, i);
    } else {
      printf("Creado proceso %d con PID %d y %d tickets\n", i, pid, tickets);
    }
  }
  
  for(int i = 0; i < N; i++) {
    wait(0);
  }
  
  printf("Demo completado\n");
  exit(0);
}
