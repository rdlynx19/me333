#include "nu32dip.h"          // constants, functions for startup and UART
#define NUMSAMPS 1000           // number of points in waveform
#define PLOTPTS 200 	      // number of data points to plot
#define DECIMATION 10 	      // plot every 10th point

//ADC information
# define MAXPLOTPTS 1000
# define SAMPLE_TIME 6 // 24MHz*250ns
void ADC_Startup();
unsigned int adc_sample_convert(int);

static volatile int Waveform[NUMSAMPS]; // waveform
static volatile int ADCarray[PLOTPTS];  // measured values to plot
static volatile int REFarray[PLOTPTS];  // reference values to plot
static volatile int StoringData = 0;   // if this flag = 1, currently storing plot data
static volatile float eint = 0.0; // integral error
static volatile float eintmax = 0.0;

static volatile float Kp = 0, Ki = 0;  // control gains


void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) {
    static int counter = 0;
    static int plotind = 0; // index for data arrays, counts up to PLOTPTS
    static int decctr = 0; // counts to store data one every DECIMATION
    static int adcval = 0; 

    adcval = adc_sample_convert(1); 
    
    // insert code for PID control
    float  e = Waveform[counter] - adcval;
    float u = Kp*e + Ki*eint;
    eint = eint + e;

    if (eint > eintmax){
    	eint = eintmax;
   }

    float unew = u + 50.0;
    if(unew > 100.0) {
    	unew = 100.0;
    } else if (unew < 0.0) {
    	unew = 0.0;
    } 
    
//    OC1RS = Waveform[counter]; 
    OC1RS = (unsigned int)((unew/100.0) * PR3);
    if (StoringData) {
    	decctr++;
	if (decctr == DECIMATION) {
		decctr = 0;
		ADCarray[plotind] = adcval;
		REFarray[plotind] = Waveform[counter];
		plotind++;
	}
	if (plotind == PLOTPTS) {
		plotind = 0;
		StoringData = 0;
	}
    }

    counter++;                  // add one to counter every time ISR is entered
    if (counter==NUMSAMPS) {
        counter = 0;            // roll the counter over when needed
    }
    // insert line to clear interrupt flag
    IFS0bits.T2IF = 0;
}

void makeWaveform() {
    int i = 0, center = 500, A = 300;
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
  char message[100];          // message to and from Python
  float kptemp = 0, kitemp = 0; // temporary local gains
  int i = 0;			// plot data loop counter
  ADC_Startup();
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
    NU32DIP_ReadUART1(message, sizeof(message));  // wait for a message from Python
    sscanf(message, "%f %f %f", &kptemp, &kitemp, &eintmax);
    __builtin_disable_interrupts();
    Kp = kptemp;
    Ki = kitemp;
    __builtin_enable_interrupts();
    StoringData = 1;     // message to ISR to start storing data
    while(StoringData) { // wait until ISR says storing data is done
    	;
    }
    for (i = 0; i<PLOTPTS; i++) {     // send plot data to Python
				      // when first number sent = 1, Python knows we're done
    	sprintf(message, "%d %d %d\r\n", PLOTPTS-i, ADCarray[i], REFarray[i]);
	NU32DIP_WriteUART1(message);
    }
  }
  return 0;
}

void ADC_Startup(){
   ANSELAbits.ANSA1 = 1; // AN0 is an adc pin
   AD1CON3bits.ADCS = 1; // ADC clock period is
   AD1CON1bits.ADON = 1;
}

unsigned int adc_sample_convert(int pin)
{
  unsigned int elapsed = 0, finish_time = 0;
  AD1CHSbits.CH0SA = pin;
  AD1CON1bits.SAMP = 1;
  elapsed = _CP0_GET_COUNT();
  finish_time = elapsed + SAMPLE_TIME;
  while (_CP0_GET_COUNT() < finish_time)
  {
    ;
  }
  AD1CON1bits.SAMP = 0;
  while (!AD1CON1bits.DONE)
  {
    ;
  }
  return ADC1BUF0;
}

