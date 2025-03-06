// config bits, constants, funcs for startup and UART
#include "encoder.h"
#include "utilities.h"
#include "ina219.h"
// include other header files here
#define BUF_SIZE 200
#define CPR 334
#define INA219_REG_CURRENT 0x04

volatile int dutyCycle = 0;

const char *modeToString(enum mode_t mode)
{
	switch (mode)
	{
	case IDLE:
		return "IDLE";
	case PWM:
		return "PWM";
	case ITEST:
		return "ITEST";
	case HOLD:
		return "HOLD";
	case TRACK:
		return "TRACK";
	default:
		return "UNKNOWN";
	}
}

void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void)
{
	enum mode_t currentMode = get_mode();
	switch (currentMode)
	{
	case IDLE:
	{
		dutyCycle = 0;
		OC1RS = PR3 * dutyCycle / 100;
		break;
	}
	case PWM:
	{
		if (dutyCycle > 0)
		{
			OC1RS = PR3 * dutyCycle / 100;
			LATAbits.LATA0 = 1;
		}
		else if (dutyCycle < 0)
		{
			OC1RS = -PR3 * dutyCycle / 100;
			LATAbits.LATA0 = 0;
		}
		break;
	}
	default:
	{
		break;
	}
	}

	// insert line to clear interrupt flag
	IFS0bits.T2IF = 0;
}

void Setup_PWM()
{
	PR3 = 2400 - 1; // 20kHz PWM Waveform
	__builtin_disable_interrupts();
	T2CONbits.TCKPS = 0;
	PR2 = 9600 - 1; // 5kHz ISR
	TMR2 = 0;
	// setting priority for the interrup timer
	IPC2bits.T2IP = 5;
	IPC2bits.T2IS = 0;
	IFS0bits.T2IF = 0;
	IEC0bits.T2IE = 1;
	RPB15Rbits.RPB15R = 0b0101;
	OC1CONbits.OCTSEL = 1;
	T3CONbits.TCKPS = 0;	// Timer3 prescaler N=1 (1:1)
	TMR3 = 0;				// initial TMR3 count is 0
	OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
	OC1RS = 0;				// duty cycle = OC1RS/(PR3+1)
	OC1R = 0;				// initialize before turning OC1 on; afterward it is read-only
	T3CONbits.ON = 1;		// turn on Timer3
	OC1CONbits.ON = 1;		// turn on OC1
	T2CONbits.ON = 1;
	__builtin_enable_interrupts();
}

int main()
{
	char buffer[BUF_SIZE];
	UART2_Startup();   // Pico and PIC32 communcation
	NU32DIP_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
	INA219_Startup();  // current sensor startup
	Setup_PWM();
	TRISAbits.TRISA0 = 0; // set pin A0 as output
	LATAbits.LATA0 = 1;	  // set the initial direction of the motor rotation (depends on pin state)
	NU32DIP_YELLOW = 1;	  // turn off the LEDs
	NU32DIP_GREEN = 1;
	set_mode(IDLE);
	__builtin_disable_interrupts();
	// in future, initialize modules or peripherals here
	__builtin_enable_interrupts();

	while (1)
	{
		NU32DIP_ReadUART1(buffer, BUF_SIZE); // we expect the next character to be a menu command
		NU32DIP_GREEN = 1;					 // clear the error LED
		switch (buffer[0])
		{
		case 'a':
		{
			// read the current sensor (ADC counts)
			float adcReading = readINA219(INA219_REG_CURRENT);
			sprintf(buffer, "%f\r\n", adcReading);
			NU32DIP_WriteUART1(buffer);
			break;
		}

		case 'b':
		{
			// read the current sensors (mA current)
			float currentReading = INA219_read_current();
			sprintf(buffer, "%f\r\n", currentReading);
			NU32DIP_WriteUART1(buffer);
			break;
		}
		case 'c':
		{
			// read the encoder count
			WriteUART2("a");
			while (!get_encoder_flag())
			{
			}
			set_encoder_flag(0);
			sprintf(buffer, "%d\r\n", get_encoder_count());
			NU32DIP_WriteUART1(buffer);
			break;
		}

		case 'd':
		{
			// read the encoder count (degrees)
			WriteUART2("a");
			while (!get_encoder_flag())
			{
			}
			set_encoder_flag(0);
			int cnt = get_encoder_count();
			float degreesPerCount = 360.0 / (CPR * 4);
			float encoderAngle = cnt * degreesPerCount;
			sprintf(buffer, "%f\r\n", encoderAngle);
			NU32DIP_WriteUART1(buffer);
			break;
		}

		case 'e':
		{
			// reset the encoder count
			WriteUART2("b");
			break;
		}

		case 'f':
		{
			// set PWM duty cycle
			NU32DIP_ReadUART1(buffer, BUF_SIZE);
			sscanf(buffer, "%d", &dutyCycle);
			set_mode(PWM);
			break;
		}

		case 'p':
		{
			// set PIC mode
			set_mode(IDLE);
			break;
		}

		case 'q':
		{
			// handle q for quit. Later you may want to return to IDLE mode here.
			enum mode_t currentMode = IDLE;
			set_mode(currentMode);
			break;
		}
		case 'r':
		{
			// read the current mode of the PIC32
			enum mode_t currentMode = get_mode();
			sprintf(buffer, "%s\r\n", modeToString(currentMode));
			NU32DIP_WriteUART1(buffer);
			break;
		}

		default:
		{
			NU32DIP_GREEN = 0; // turn on LED2 to indicate an error
			break;
		}
		}
	}
	return 0;
}
