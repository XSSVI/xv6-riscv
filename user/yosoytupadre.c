#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid, ppid;
  
  printf("=== Prueba de getppid() ===\n");
  
  pid = getpid();
  ppid = getppid();
  
  printf("Mi PID: %d\n", pid);
  printf("PID de mi padre: %d\n", ppid);
  
  // Crear un proceso hijo para probar más
  int child_pid = fork();
  
  if(child_pid == 0) {
    // Proceso hijo
    printf("\n=== En el proceso hijo ===\n");
    printf("Mi PID: %d\n", getpid());
    printf("PID de mi padre: %d\n", getppid());
    
    // Pruebas de getancestor
    printf("\n=== Prueba de getancestor() ===\n");
    printf("getancestor(0): %d (yo mismo)\n", getancestor(0));
    printf("getancestor(1): %d (mi padre)\n", getancestor(1));
    printf("getancestor(2): %d (mi abuelo)\n", getancestor(2));
    printf("getancestor(3): %d (bisabuelo)\n", getancestor(3));
    printf("getancestor(10): %d (debe ser -1)\n", getancestor(10));
    printf("getancestor(-1): %d (debe ser -1)\n", getancestor(-1));
    
    exit(0);
  } else {
    // Proceso padre
    wait(0);  // Esperar al hijo
    printf("\n=== Proceso hijo terminado ===\n");
  }
  
  exit(0);
}
