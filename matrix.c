#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mat.h"
#include <sys/resource.h>

void checkArgs(int argc, char *argv[])
{
  if (argc < 6)
  {
    printf("Usage: %s <din> <cr> <ck> <totDevices> <text> [<effect>]\n", argv[0]);
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  checkArgs(argc, argv);
  
  initMatrix(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

  int effect;
  if (argc == 7)
  {
    effect = atoi(argv[6]);
  }
  else
  {
    effect = 1;
  }

  setpriority(PRIO_PROCESS, 0, -20);
  displayString(argv[5], strlen(argv[5]), effect);

  printf("--- DONE ---\n");
  tearDownMatrix();

  return 0;
}
