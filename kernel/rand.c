#include "types.h"

static unsigned long seed = 1;

void
srand(unsigned int s)
{
  seed = s;
}

int
random(void)
{
  // Generador lineal congruencial
  seed = (seed * 1103515245 + 12345) & 0x7fffffff;
  return (int)seed;
}
