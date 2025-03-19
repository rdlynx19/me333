# ME333 Assignment 5
Author: Pushkar Dave

**Q3: Refer to the Memory Organization section of the Data Sheet and Figure2.1**
**(a)Indicate which bits 0-31, can be used as inputs/outputs for ports A and B. For the PIC32MX170F256B, indicate which pin is B0**\
**(b)The SFR INTCON refers to "interrupt control". Which bits, 0-31 of this SFR are unimplemented? Of the bits that are implemented, give the numbers of the bits and their names.**

Ans:(a) For PORTA: bits 10-7 and 4-0 can be used as inputs/ouputs. However, bits 10-7 are only available on 44 pin devices so they cannot be used for the PIC we have.\
For PORTB: bits 15-0 can be used as inputs/outputs
Pin 4 is B0 for PIC32MX170F256B

(b) Bits 31-16, 15-13, 11, 7-5 of the INTCON register are unimplemented.\
Bit 12 : MVEC Multi Vector Configuration Bit\
Bit 10-8 : TPC<2:0> Interrupt Proximity Timer Control bits\
Bit 4: INT4EP External Interrupt 4 Edge Polarity Control Bit\
Bit 3: INT3EP External Interrupt 3 Edge Polarity Control Bit\
Bit 2: INT2EP External Interrupt 2 Edge Polarity Control Bit\
Bit 1: INT1EP External Interrupt 1 Edge Polarity Control Bit\
Bit 0: INT0EP External Interrupt 0 Edge Polarity Control Bit

**Q4: Modify `simplePIC.c` so that both lights are on or off at the same time, instead of opposite each other. Turn in only the code that changed.**

Ans: The line for the bit 5 of LATB is change from 0 to 1, to turn on both the green and yellow at the same time.
```
LATBbits.LATB4 = 0;
LATBbits.LATB5 = 0; 
```

**Q5:Modify simplePIC.c so that the function delay takes an int cycles as an argument. The for loop in delay executes cycles times, not a fixed value of 1,000,000. Then modify main so that the first time it calls delay , it passes a value equal to MAXCYCLES . The next time it calls delay with a value decreased by DELTACYCLES, and so on, until the value is less than zero, at which time it resets the value to MAXCYCLES . Use #define to define the constants MAXCYCLES as 1,000,000 and DELTACYCLES as 100,000. Turn in your code.**

Ans: Check file `delayPIC.c`

**Q7: The processor.o file linked with your simplePIC project is much larger than your final .hex file. Explain how that is possible.**

Ans: 
The processor.o file linked with the simplePIC project is much larger than the final .hex file because the final .hex file contains the writable machine code which has all the necessary addresses and data for the code to run. The processor.o file contains other data used by the compiler including metadata and information about all memory addresses and their types. This is a lot of extra information, which is not needed in the final .hex file.


**Q9: Give three C commands, using TRISBSET, TRISBCLR, and TRISBINV, that set bits 2 and 3 of TRISB to 1, clear bits 1 and 5, and flip bits 0 and 4.**

Ans: TRISBSET = 0x000C\
TRISBCLR = 0x0022\
TRISBINV = 0x0011


**Ch4 Q1: Identify which functions, constants, and global variables in `nu32dip.c` are private to `nu32dip.c` and which are meant to be used in other C files.**

Ans: Functions `NU32DIP_Startup()` is used for initialisation purposes. Other files, are meant to call the function to start up the board, but cannot access or modify any of the values. Functions `NU32DIP_ReadUART1(char* message, int maxLength)` and `NU32DIP_WriteUART1(const char* string)` are meant to be used in other c files, to read from and write to the UART. Thus, all functions are meant to public.

**Ch4 Q2: You will create your own libraries.**\
**a. Remove the comments from invest.c in Appendix A. Now modify it to work on the NU32 using the NU32 library. You will need to replace all instances of printf and scanf with appropriate combinations of sprintf , sscanf , NU32_ReadUART3 and NU32_WriteUART3. Verify that you can provide data to the PIC32 with your keyboard and display the results on your computer screen. Turn in your code for all the files, with comments where you altered the input and output statements.**

Ans: Check folder `invest1`. Comments are added to the modified lines.

**b. Split invest.c into two C files, main.c and helper.c , and one header file, helper.h . helper.c contains all functions other than main . Which constants, function prototypes, data type definitions, etc., should go in each file? Build your project and verify that it works. For the safety of future helper library users, put an include guard in helper.h . Turn in your code and a separate paragraph justifying your choice for where to put the various definitions.**

Ans: Check folder `invest2`. The helper.h file contains the declaration for all the utility functions, including the Investment struct, and the (#define) constants. The helper.c file then contains the implementation of these functions, and includes the header file. The main.c file just contains the main function, and calls the NU32DIP_Startup() function and calls the other functions implemented in helper.c

**c. Break invest.c into three files: main.c , io.c , and calculate.c. Any function which handles input or output should be in io.c . Think about which prototypes, data types, etc., are needed for each C file and come up with a good choice of a set of header files and how to include them. Again, for safety, use include guards in your header files. Verify that your code works. Turn in your code and a separate paragraph justifying your choice of header files.**

Ans: Check folder `invest3`. The header file investment.h contains the definition of the Investment struct. The other two header files, io.h and calculate.h contain the declaration for the input/output functions and the calculation function and include investment.h. The io.c and calculate.c files, contain the implementation of these files and include the respective header files. The main.c file implements the main function for running the program loop. The main reason of having a separate investment.h header file, is that defining the struct in both the other header files, causes an error of double declaration in the main.c file, because both the header files need the Investment struct. 


