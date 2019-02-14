#include "font.h"
#include <stdlib.h>
#include <stdio.h>

void checkArgs(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <char>\n", argv[0]);
    exit(1);
  }
}

void printLine(int line)
{
  if (line != 0)
  {
    printf("%s ", line % 2 == 1 ? "*" : " ");
    printLine(line >> 1);
  } 
}

void printChar(int * ch)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    printLine(ch[7 - i]);
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  checkArgs(argc, argv);

  printChar(font_chars[(int)argv[1][0]]);

  return 0;
}
