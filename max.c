#include <time.h>
#include <stdio.h>
#include <wiringPi.h>
#include "max.h"

int COMMANDS_DIGIT[8] = {COMMAND_DIGIT_0, COMMAND_DIGIT_1, COMMAND_DIGIT_2, COMMAND_DIGIT_3, COMMAND_DIGIT_4, COMMAND_DIGIT_5, COMMAND_DIGIT_6, COMMAND_DIGIT_7};

void writeToPin(int pin, int value)
{
  digitalWrite(pin, value);
}

void setCK(int value)
{
  writeToPin(PIN_CK, value);
}

void setCR(int value)
{
  writeToPin(PIN_CR, value);
}

void setDIN(int value)
{
  writeToPin(PIN_DIN, value);
}

void microSleep(int microseconds)
{
  delayMicroseconds(microseconds);
}

void sendBit(int value)
{
  setCK(0);
  microSleep(1);
  setDIN(value);
  microSleep(1);
  setCK(1);
}

void sendBits(int bits, int n)
{
  if (n != 0)
  {
    sendBit(bits & 1);
    int newBits = bits >> 1;
    microSleep(1);
    sendBits(newBits, n - 1);
  }
}

int reverse(int number, int index)
{
  if (index < 0) return 0;
  int shiftedNumber = number >> 1;
  return (number & 1) << (index - 1) | reverse(shiftedNumber, index - 1);
}

void sendCommand(int command, int data)
{
  setCR(0);
  microSleep(1);
  sendBits(reverse((command << 8) | data, 16), 16);
  microSleep(1);
}

void initMax(int DIN, int CR, int CK)
{
  PIN_DIN = DIN;
  PIN_CR = CR;
  PIN_CK = CK;

  wiringPiSetupGpio();

  pinMode(PIN_CK, OUTPUT);
  pinMode(PIN_DIN, OUTPUT);
  pinMode(PIN_CR, OUTPUT);
}

void tearDownMax()
{
}

void maxWrite()
{
  setCR(0);
  microSleep(1);
  setCR(1);
  microSleep(1);
}
