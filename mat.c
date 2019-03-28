#include <stdlib.h>
#include <stdio.h>
#include "max.h"
#include "font/font.h"
#include "mat.h"

int DEVICES_NUMBER;

void command(int command, int data)
{
  sendCommand(command, data);
}

void init8x8()
{
  command(COMMAND_SCAN_LIMIT, 7);
  maxWrite();
  command(COMMAND_DECODE, 0);
  maxWrite();
  command(COMMAND_SHUTDOWN, 1);
  maxWrite();
  command(COMMAND_TEST, 0);
  maxWrite();
  command(COMMAND_INTENSITY, 2);
  maxWrite();
}

void initMatrix(int DIN, int CR, int CK, int devicesNumber)
{
  DEVICES_NUMBER = devicesNumber;
  initMax(DIN, CR, CK);
  int i;
  for (i = 0; i < DEVICES_NUMBER * 4; i++)
  {
    init8x8();
  }
}

void tearDownMatrix()
{
  tearDownMax();
}

int imageSize(char * str, int strLength)
{
  int size = 0, i;
  for (i = 0; i < strLength; i++)
  {
    size += getCharSize(str[i]) + 1;
  }
  return size;
}

unsigned short int ** createImageBuffer(int width)
{
  unsigned short int ** image = (unsigned short int**) malloc(8 * sizeof(unsigned short int *));
  int i;
  for (i = 0; i < 8; i++)
  {
    image[i] = calloc(width, sizeof(unsigned short int));
  }
  return image;
}

int bitsToInt(unsigned short int * intStr, int index, int size)
{
  int i, result = 0;
  for (i = 0; i < 8; i++)
  {
    result <<= 1;
    result ^= (index + i < size && index + i >= 0) ? intStr[index + i] : 0;
  }
  return result;
}

unsigned short int * intToBits(int i, int size)
{
  unsigned short int * res = (unsigned short int *) calloc(size, sizeof(unsigned short int));
  int index;
  for (index = 0; index < size; index++)
  {
    res[size - index - 1] = i & 1;
    i >>= 1;
  }
  return res;
}

unsigned short int ** getCharBits(int * ch, int size)
{
  unsigned short int ** image = createImageBuffer(size);
  int i;
  for (i = 0; i < 8; i++)
  {
    image[i] = intToBits(ch[i], size);
  }
  return image;
}

unsigned short int ** buildImage(char * str, int size)
{
  unsigned short int ** image = createImageBuffer(imageSize(str, size));
  int width, height, strI, imageI = 0;
  for (strI = 0; strI < size; strI++)
  {
    int * ch = getChar(str[strI]);
    int size = getCharSize(str[strI]);
    unsigned short int ** chBits = getCharBits(ch, size);
    for (width = 0; width < size; width++)
    {
      for (height = 0; height < 8; height++)
      {
        image[height][imageI + width] = chBits[height][width];
      }
    }
    imageI += size + 1;
    for (height = 0; height < 8; height++)
    {
      image[height][imageI] = 0;
    }
  }
  return image;
}

void displayFixed(unsigned short int ** image, int size, int scroll)
{
  int i, display;
  for (i = 0; i < 8; i++)
  {
    for (display = 0; display < DEVICES_NUMBER; display++)
    {
      command(COMMANDS_DIGIT[i], bitsToInt(image[i], display * 8 + scroll, size));
    }
    maxWrite();
    microSleep(2000);
  }
}

void scrollRL(unsigned short int ** image, int size)
{
  int i;
  for (i = 0; i < size + 8 * DEVICES_NUMBER + 1; i++)
  {
    displayFixed(image, size, size - i);
  }
}

char * revertString(char * str, int size)
{
  char * res = calloc(size, sizeof(char));
  int i;
  for (i = 0; i < size; i++)
  {
    res[size - i - 1] = str[i];
  }
  return res;
}

void printImage(unsigned short int ** image, int size)
{
  int width, height;
  for (height = 7; height >= 0; height--)
  {
    for(width = 0; width < size; width ++)
    {
      printf(image[height][width] == 1 ? "* " : ". ");
    }
    printf("\n");
  }
}

void displayString(char * str, int size, int effect)
{
  unsigned short int ** image = buildImage(revertString(str, size), size);
  if (effect == 1)
  {
    scrollRL(image, imageSize(str, size));
  }
  else if (effect == 2)
  {
    displayFixed(image, imageSize(str, size), 0);
  }
  else
  {
    //TODO display error (! on every display)
  }
}
