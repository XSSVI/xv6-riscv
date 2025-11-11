#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
  printf("Probando syscall settickets...\n");
  
  printf("Tickets iniciales: 100 (por defecto)\n");
  
  if(settickets(200) == 0) {
    printf("settickets(200) exitoso\n");
  }
  
  if(settickets(-5) == 0) {
    printf("settickets(-5) exitoso (debería ser 1)\n");
  }
  
  if(settickets(150) == 0) {
    printf("settickets(150) exitoso\n");
  }
  
  printf("Prueba completada\n");
  exit(0);
}
