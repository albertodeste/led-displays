#define COMMAND_NOOP 0b0000
#define COMMAND_DIGIT_0 0b0001
#define COMMAND_DIGIT_1 0b0010
#define COMMAND_DIGIT_2 0b0011
#define COMMAND_DIGIT_3 0b0100
#define COMMAND_DIGIT_4 0b0101
#define COMMAND_DIGIT_5 0b0110
#define COMMAND_DIGIT_6 0b0111
#define COMMAND_DIGIT_7 0b1000
#define COMMAND_DECODE 0b1001
#define COMMAND_INTENSITY 0b1010
#define COMMAND_SCAN_LIMIT 0b1011
#define COMMAND_SHUTDOWN 0b1100
#define COMMAND_TEST 0b1111

int COMMANDS_DIGIT[8];

int PIN_DIN, PIN_CR, PIN_CK;

void initMax(int DIN, int CR, int CK);
void tearDownMax();
void sendCommand(int command, int data);
void maxWrite();
void microSleep(int microseconds);
