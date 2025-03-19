#include "nu32dip.h"
#include "sr04.h"

#define MAX_MESSAGE_LENGTH 200

int main(void) { 
  char message[MAX_MESSAGE_LENGTH];	
  
  NU32DIP_Startup();
  SR04_Startup();
  while (1) {
    _CP0_SET_COUNT(0);
    float dist = SR04_read_meters();
    while(_CP0_GET_COUNT() < 6000000){}
    sprintf(message, "The distance is %f meters", dist);
    NU32DIP_WriteUART1(message);                     // send message back
    NU32DIP_WriteUART1("\r\n");                      // carriage return and newline
    NU32DIP_GREEN = !NU32DIP_GREEN;                       // toggle the LEDs
    NU32DIP_YELLOW = !NU32DIP_YELLOW;
  }
  return 0;
}
