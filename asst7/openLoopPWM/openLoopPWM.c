#include "nu32dip.h"          // constants, functions for startup and UART
#define NUMSAMPS 1000           // number of points in waveform
static volatile int Waveform[NUMSAMPS];



void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) {
    static int counter = 0;

    // insert line(s) to set OC1RS
    OC1RS = Waveform[counter];   

    counter++;                  // add one to counter every time ISR is entered
    if (counter==NUMSAMPS) {
        counter = 0;            // roll the counter over when needed
    }
    // insert line to clear interrupt flag
    IFS0bits.T2IF = 0;
}

void makeWaveform() {
    int i = 0, center = (PR3+1)/2, A = (PR3+1)/4;
    for(i = 0; i < NUMSAMPS; ++i){
    if( i < NUMSAMPS / 2) {
        Waveform[i] = center + A;
    }
     else {
        Waveform[i] = center - A;
    }
    }
}


int main(void) {
  NU32DIP_Startup();          // cache on, interrupts on, LED/button init, UART init

  PR3 = 2400-1;              // period
  makeWaveform();
  __builtin_disable_interrupts();
  T2CONbits.TCKPS = 0;
  PR2 = 48000-1;
  TMR2 = 0;
  IPC2bits.T2IP = 5;
  IPC2bits.T2IS = 0;
  IFS0bits.T2IF = 0;
  IEC0bits.T2IE = 1;
  __builtin_enable_interrupts();
  RPB15Rbits.RPB15R = 0b0101;
  OC1CONbits.OCTSEL = 1;
  T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
  TMR3 = 0;               // initial TMR3 count is 0
  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
//   OC1RS = (2400*3)/4;             // duty cycle = OC1RS/(PR3+1)
//   OC1R = (2400*3)/4;              // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;        // turn on Timer3
  OC1CONbits.ON = 1;       // turn on OC1
  T2CONbits.ON = 1;

  while(1) {
    ;                      // infinite loop
  }
  return 0;
}

