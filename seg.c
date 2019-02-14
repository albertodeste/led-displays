#include "max.h"
#include "seg.h"

#define DIGIT_0 0b01111110
#define DIGIT_1 0b00110000
#define DIGIT_2 0b01101101
#define DIGIT_3 0b01111001
#define DIGIT_4 0b00110011
#define DIGIT_5 0b01011011
#define DIGIT_6 0b01011111
#define DIGIT_7 0b01110000
#define DIGIT_8 0b01111111
#define DIGIT_9 0b01111011
#define LETTER_E_UPPERCASE 0b01001111
#define LETTER_R_LOWERCASE 0b00000101

int DIGITS[10] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9};
int DEVICES_NUMBER, CONTROLLED_DEVICE;

int digitMap(int number)
{
  return DIGITS[number];
}

void commandDevice(int command, int data, int deviceId)
{
  if (deviceId == CONTROLLED_DEVICE)
  {
    sendCommand(command, data);
  }
  else
  {
    sendCommand(COMMAND_NOOP, 0);
  }

  if (deviceId == DEVICES_NUMBER)
  {
    maxWrite();
  }
  else
  {
    commandDevice(command, data, deviceId + 1);
  }
}

void command(int command, int data)
{
  commandDevice(command, data, 1);
  microSleep(100);
}

void initSeg(int DIN, int CR, int CK, int deviceNumber, int controlledDevice)
{
  DEVICES_NUMBER = deviceNumber;
  CONTROLLED_DEVICE = controlledDevice;
  initMax(DIN, CR, CK);
}

void startupSeg()
{
  command(COMMAND_SCAN_LIMIT, 7);
  command(COMMAND_DECODE, 0);
  command(COMMAND_SHUTDOWN, 1);
  command(COMMAND_TEST, 0);
  command(COMMAND_INTENSITY, 8);
}

void tearDownSeg()
{
  tearDownMax();
}

void showError(int code)
{
  command(COMMAND_SCAN_LIMIT, 3);
  command(COMMAND_DIGIT_0, digitMap(code));
  command(COMMAND_DIGIT_1, LETTER_R_LOWERCASE);
  command(COMMAND_DIGIT_2, LETTER_R_LOWERCASE);
  command(COMMAND_DIGIT_3, LETTER_E_UPPERCASE);
}

int digits(int number)
{
  if (number <= 9)
  {
    return 1;
  }
  else
  {
    return 1 + digits(number / 10);
  }
}

void displayLSDigit(int number, int displayNumber)
{
  command(COMMANDS_DIGIT[displayNumber], digitMap(number % 10));
  if (number >= 10)
  {
    displayLSDigit(number / 10, displayNumber + 1);
  }
}

void displayInteger(int number)
{
  if (number <= 99999999)
  {
    command(COMMAND_SCAN_LIMIT, digits(number) - 1);
    displayLSDigit(number, 0);
  }
  else
  {
    showError(1);
  }
}


