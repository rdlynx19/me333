#include "nu32dip.h"          // constants, functions for startup and UART

int main(void) {
  NU32DIP_Startup();          // cache on, interrupts on, LED/button init, UART init

  RPB15Rbits.RPB15R = 0b0101;
  OC1CONbits.OCTSEL = 1;
  T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
  PR3 = 2400-1;              // period = (PR2+1) * N * 12.5 ns = 100 us, 10 kHz
  TMR3 = 0;               // initial TMR2 count is 0
  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = (2400*3)/4;             // duty cycle = OC1RS/(PR2+1) = 25%
  OC1R = (2400*3)/4;              // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;        // turn on Timer2
  OC1CONbits.ON = 1;       // turn on OC1

  while(1) {
    ;                      // infinite loop
  }
  return 0;
}

