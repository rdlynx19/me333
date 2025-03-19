# ME333 Assignment 3

Author: Pushkar Dave

**Q3: Describe the four functions that pin 12 of the PIC32MX7170F256B can have. Is it 5 V tolerant?** \
Ans: SOSCO: 32.768kHz low power oscillator crystal output \
RPA4: Remappable Analog Pin 4\
T1CK: Timer1 external clock input\
CTED9: CTMU External edge input\
PMA1: Parallel Master Port Address bit 1 input
(Buffered Slave modes) and output
(Master modes) \
RA4:  bidirectional I/O pin \
No, the pin is **not** 5V tolerant.

**Q4: Referring to the Data Sheet section on I/O Ports, what is the name of the SFR you have to modify if you want to change pins on PORTC from output to input?**\
Ans: The SFR we have to modify to change pins on PORTC from output to input is TRISC.

**Q5: The SFR CM1CON controls comparator behavior. Referring to the Memory Organization section of the Data Sheet, what is the reset value of CM1CON in hexadecimal?**\
Ans: 0x00C3

**Q6: In one sentence each, without going into detail, explain the basic function of the following items shown in the PIC32 architecture block diagram Figure 2.2: SYSCLK, PBCLK, PORTA to PORTG (and indicate which of these can be used for analog input on the NU32’s PIC32), Timer1 to Timer5, 10-bit ADC, PWM OC1-5, Data RAM, Program Flash Memory, and Prefetch Cache Module.**\
Ans: SYSCLK: The primary timing source for the system and peripherals \
PBCLK: The peripheral bus clock drives the operation of peripheral modules like UART\
PORTA-PORTG: GPIO ports for digital input/output. PORTA-PORTC can also serve as analog input\
Timer1-Timer5: External clock inputs for counting or interrupts\
10-bit ADC: Converts analog to 10bit digital signals\
PWM OC1-5: Output compare modules generating PWM signals\
Data RAM: Volatile memory for temporary storage of variables and data\
Program Flash Memory: Non volatile memory for storage of programs and constant data\
Prefetch Cache Module: Preloads data from flash memory to improve program execution speed


**Q7: List the peripherals that are not clocked by PBCLK**\
Ans: USB, DMAC, ICD, PORTA-PORTC and the remappable pins.


**Q8: If the ADC is measuring values between 0 and 3.3 V, what is the largest voltage difference that it may not be able to detect? (It’s a 10-bit ADC.)**\
Ans: If it is a 10-bit ADC, largest voltage difference, it will not be able to measure is $3.3/2^{10} = 3.22mV$

**Q9: Refer to the Reference Manual chapter on the Prefetch Cache. What is the maximum size of a program loop, in bytes, that can be completely stored in the cache**\
Ans: 256 bytes

**Q10: Explain why the path between flash memory and the prefetch cache module is 128 bits wide instead of 32, 64, or 256 bits.**\
Ans: The data path from prefetch cache module to the CPU is 32 bits wide, so the path between flash memory and prefetch cache module is 128 bits wide and provides bandwidth to the CPU. 128 bits is a balance between hardware cost and memory access efficiency.

**Q11: Explain how a digital output could be configured to swing between 0 and 4 V, even though the PIC32 is powered by 3.3 V**\
Ans: If connected in an open drain configuration, with a pull up resistor, the output can be brought to 4V.


**Q12: PIC32’s have increased their flash and RAM over the years. What is the maximum amount of flash memory a PIC32 can have before the current choice of base addresses in the physical memory map (for RAM, flash, peripherals, and boot flash) would have to be changed? What is the maximum amount of RAM? Give your answers in bytes in hexadecimal**\
Ans: The maximum RAM would be 0x1D0 and the maximum flash memory would Ox1DB

**Q13: Examine the Special Features section of the Data Sheet.**\
**(a)If you want your PBCLK frequency to be half the frequency of SYSCLK, which bits of which Device Configuration Register do you have to modify? What values do you give those bits?**\
**(b) Which bit(s) of which SFR set the watchdog timer to be enabled? Which bit(s) set the postscale that determines the time interval during which the watchdog must be reset to prevent it from restarting the PIC32? What values would you give these bits to enable the watchdog and to set the time interval to be the maximum?**\
**(c)The SYSCLK for a PIC32 can be generated several ways, as discussed in the Oscillator chapter in the Reference Manual and the Oscillator Configuration section in the Data Sheet. The PIC32 on the NU32 uses the (external) primary oscillator in HS mode with the phase-locked loop (PLL) module. Which bits of which device configuration register enable the primary oscillator and turn on the PLL module?**\
Ans: (a) Bits 13-12 FPBDIV<1:0>: Peripheral Bus Clock Divisor Default Value bits of the DEVCFG2 Register. The bits should be set to **01**\
(b) Bit 23 FWDTEN of DEVCFG1 Register set the watchdog timer to be enabled. Bits 20-16 WDTPS<4:0> set the postscale that determines the time interval during which the watchdog must be reset to prevent it from restarting the PIC32. To set the time interval to maximum, these bits must be given the value **10100**.  
(c) Bits 9-8 POSCMOD<1:0> of the DEVCFG1 register are used to enable the primary oscillator. Bit 15 UPLLEN enables the USB PLL module.

**Q14: Your NU32 board provides four power rails - GND, regulated 3.3 V, regulated 5 V, and the unregulated input voltage (e.g., 6 V). You plan to put a load from the 5 V output to ground. If the load is modeled as a resistor, what is the smallest resistance that would be safe? An approximate answer is fine. In a sentence, explain how you arrived at the
answer**\
Ans: Max current output by Vss is 300mA, and for a voltage of 5V, safe resistance value would be found using Ohm's law, which is 17 $\Omega$

**Q15:The PIC32MX170F256B could be powered by different voltages. Give a reasonable range of voltages that could be used, minimum to maximum, and explain the reason for the limits.**\
Ans: The reasonable range of voltages is 2.3V to 3.6V. The internal components require a minimum voltage of 2.3V to remain operational, and can handle a maximum of 3.6V before excedding safety limits.

**Q16: Two buttons and two LEDs are interfaced to the PIC32 on the NU32. Which pins are they connected to? Give the actual pin numbers, 1-64, as well as the name of the pin function as it is used on the NU32. For example, pin 37 on the PIC32MX795F512H could have the function D+ (USB data line) or RG2 (Port G digital input/output), but only one of these functions could be active at a given time**
Ans: The Green LED is connected to pin B4 (11), and the Yellow LED is connected to pin B5 (14), the user button is connected to A4 (12) and the reset button is connected to MCLR (1). 


