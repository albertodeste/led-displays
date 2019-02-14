#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seg.h"

void checkArgs(int argc, char *argv[])
{
  if (argc < 6)
  {
    printf("Usage: %s <din> <cr> <ck> <totDevices> <deviceNr> [<number>]\n", argv[0]);
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  checkArgs(argc, argv);
  
  int number;
  if (argc > 6)
  {
    number = atoi(argv[6]);
  }
  else
  {
    time_t t;
    srand(time(&t));
    number = rand() % 99999999;
  }

  initSeg(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

  displayInteger(number);

  printf("--- DONE ---\n");
  tearDownSeg();

  return 0;
}
