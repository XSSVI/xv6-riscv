# Lottery Scheduling en XV6

## Funcionamiento y Lógica
El lottery scheduling asigna "tickets" a cada proceso. La probabilidad de que un proceso sea seleccionado es proporcional a sus tickets respecto al total. Se usa un generador de números aleatorios para seleccionar el proceso ganador en cada ciclo del scheduler. El scheduler recorre la tabla de procesos, calcula el total de tickets de los procesos RUNNABLE, genera un número aleatorio en el rango [1, total] y luego selecciona el proceso cuyo acumulado de tickets alcanza o supera el número aleatorio.

## Modificaciones Realizadas

### Archivos modificados:
- **kernel/proc.h**: Agregados campos `tickets` y `run_slices` en struct proc
- **kernel/proc.c**: 
  - Inicialización en allocproc() (tickets=100, run_slices=0)
  - Implementación del lottery scheduler en scheduler()
- **kernel/sysproc.c**: Implementación de sys_settickets()
- **kernel/syscall.h**: Definición de SYS_settickets (24)
- **kernel/syscall.c**: Declaración y registro del syscall
- **kernel/rand.c**: Generador de números aleatorios (LCG)
- **kernel/defs.h**: Declaraciones de random() y srand()
- **kernel/main.c**: Inicialización de semilla aleatoria
- **user/user.h**: Declaración de settickets() para espacio de usuario
- **user/usys.pl**: Entrada para generar el trampolín del syscall
- **user/test_tickets.c**: Programa de prueba del syscall
- **user/demo.c**: Demo con 10 procesos y tickets variables
- **Makefile**: Agregados rand.o, _test_tickets, _demo

### Cambios clave:
1. **Estructura de procesos**: Cada proceso ahora tiene tickets y contador de ejecuciones
2. **Syscall settickets**: Permite modificar tickets desde espacio de usuario
3. **Scheduler**: Reemplazó Round-Robin por selección aleatoria proporcional
4. **Generador aleatorio**: Implementado con LCG para la lotería
5. **Robustez**: Si no hay procesos RUNNABLE o el total de tickets es 0, el scheduler continúa al siguiente ciclo sin bloquearse.

## Dificultades Encontradas y Soluciones a los problemas

1. **Generador de números aleatorios**: 
   - Problema: XV6 no tiene generador aleatorio
   - Solución: Implementé un genrador de numeros usando LCG en rand.c

2. **Sincronización en scheduler**:
   - Problema: Race conditions al acceder a la lista de procesos
   - Solución: Uso adecuado de locks al recorrer la tabla de procesos

3. **Syscall implementation**:
   - Problema: Falta de declaraciones en múltiples archivos
   - Solución: Verificación exhaustiva de todos los archivos involucrados (syscall.h, syscall.c, user.h, usys.pl, etc.)

4. **Compilación y enlace**:
   - Problema: Errores de compilación por falta de archivos o declaraciones
   - Solución: Revisar cuidadosamente cada error y asegurar que todos los archivos necesarios estén incluidos en el Makefile.

## Resultados de la Prueba (demo)
Al ejecutar el programa `demo` se crean 10 procesos con tickets que van desde 50 hasta 500. Se observa que los procesos con más tickets (ej. 500) aparecen con mayor frecuencia en la salida, mientras que los de menos tickets (ej. 50) aparecen menos. Esto demuestra que el lottery scheduling está funcionando correctamente, asignando más tiempo de CPU a los procesos con más tickets. Aunque la salida es concurrente y un poco desordenada, la distribución proporcional es evidente.

## Posibles Problemas de Lottery Scheduling

1. **Injusticia a corto plazo**: Debido a la naturaleza aleatoria, es posible que un proceso con muchos tickets gane varias veces consecutivas, mientras que un proceso con pocos tickets pueda no ejecutarse por un tiempo. Sin embargo, a largo plazo la distribución es justa.

2. **Overhead computacional**: En cada ciclo del scheduler, se debe calcular la suma total de tickets de todos los procesos RUNNABLE. Esto tiene un costo O(n) en el número de procesos, que puede ser significativo si hay muchos procesos.

3. **Predictibilidad**: El comportamiento no determinista dificulta el debugging y la reproducción de problemas. No se puede predecir qué proceso se ejecutará en un momento dado.

4. **Starvation teórica**: Aunque es improbable, un proceso con muy pocos tickets podría nunca ser seleccionado. En la práctica, esto es poco común, pero es una posibilidad teórica en caso de que los tickets totales nunca se acaben.

5. **Dependencia del generador aleatorio**: La calidad de la aleatoriedad del generador de números aleatorios afecta directamente la equidad del scheduler. Un generador de baja calidad podría llevar a distribuciones no uniformes (el caso actual).

6. **Problemas de sincronización**: Si un proceso con muchos tickets se vuelve RUNNABLE frecuentemente, puede monopolizar la CPU, afectando a otros procesos.

A pesar de estos problemas, lottery scheduling es una alternativa simple y efectiva a los schedulers más complejos, y proporciona una distribución de CPU proporcional a la asignación de tickets.
