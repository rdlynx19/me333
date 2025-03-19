# ME333 Assignment 6
Author: Pushkar Dave

**Ch5 Q3: To write time-efficient code, it is important to understand that some mathematical operations are faster than others. We will look at the disassembly of code that performs simple arithmetic operations on different data types. Create a program with the following local variables in main :**
```
char c1=5, c2=6, c3;
int i1=5, i2=6, i3;
long long int j1=5, j2=6, j3;
float f1=1.01, f2=2.02, f3;
long double d1=1.01, d2=2.02, d3;
```
**Now write code that performs add, subtract, multiply, and divide for each of the five data types, i.e., for `char s`:**
```
c3 = c1+c2;
c3 = c1-c2;
c3 = c1*c2;
c3 = c1/c2;
```
**Build the program with no optimization and look at the disassembly. For each of the statements, you will notice that some of the assembly code involves simply loading the variables from RAM into CPU registers and storing the result (also in a register) back to RAM. Also, while some of the statements are completed by a few assembly commands in sequence, others result in a jump to a software subroutine to complete the calculation.(These subroutines are provided with our C installation and included in the linking process.) Answer the following questions.**

**a. Which combinations of data types and arithmetic functions result in a jump to a subroutine? From your disassembly file, copy the C statement and the assembly commands it expands to (including the jump) for one example.**

**b. For those statements that do not result in a jump to a subroutine, which combination(s) of data types and arithmetic functions result in the fewest assembly commands? From your disassembly, copy the C statement and its assembly commands for one of these examples. Is the smallest data type, char , involved in it? If not, what is the purpose of extra assembly command(s) for the char data type vs. the int data type? (Hint: the assembly command ANDI takes the bitwise AND of the second argument with the third argument, a constant, and stores the result in the first argument. Or you may wish to look up a MIPS32 assembly instruction reference.)**

**c. Fill in the following table. Each cell should have two numbers: the number of assembly commands for the specified operation and data type, and the ratio of this number (greater than or equal to 1.0) to the smallest number of assembly commands in the table. For example, if addition of two int s takes four assembly commands, and this is the fewest in the table, then the entry in that cell would be 1.0 (4). This has been filled in below, but you should change it if you get a different result. If a statement results in a jump to a subroutine, write J in that cell.** 

|| char | int |long long |float |long double|
|-|------|-----|----------|------|-----------|
|+ | |1.0 (4)| | | |
|− | | | | | |
|∗ | | | | | |
|/ | | | | | |

**d. From the disassembly, find out the name of any math subroutine that has been added to your assembly code. Now create a map file of the program. Where are the math subroutines installed in virtual memory? Approximately how much program memory is used by each of the subroutines? You can use evidence from the disassembly file and/or the map file. (Hint: You can search backward from the end of your map file for the name of any math subroutines.)**

Ans: (a) The arithmetic operation divide for the datatype long long; operations add, subtract, multiply and divide for datatypes float and long double result in a jump to a subroutine. Example used here is float addition.
```
    f3 = f1+f2;
9d0086dc:	8fc50034 	lw	a1,52(s8)
9d0086e0:	8fc40030 	lw	a0,48(s8)
9d0086e4:	0f4022a7 	jal	9d008a9c <__addsf3>
9d0086e8:	00000000 	nop
9d0086ec:	afc20058 	sw	v0,88(s8)

9d008a9c <__addsf3>:
9d008a9c:	00044dc2 312900ff 00055dc2 316b00ff     .M....)1.]....k1
9d008aac:	3c078000 00044200 01074025 00055200     ...<.B..%@...R..
9d008abc:	01475025 252dffff 2da100fe 10200061     %PG...-%...-a. .
9d008acc:	00000000                                ....
```

(b) The smallest combination of assembly commands is for operations add, subtract and multiply with data type int. Example user here is for int addition.
```
   i3 = i1+i2;
9d0085d0:	8fc30014 	lw	v1,20(s8)
9d0085d4:	8fc20018 	lw	v0,24(s8)
9d0085d8:	00621021 	addu	v0,v1,v0
9d0085dc:	afc2004c 	sw	v0,76(s8)
``` 
No, the smallest data type `char` takes one extra assembly line compared to `int`. The extra assembly command for the char data type used is `andi` which ensures the result of the char addition fits within the 8-bit range of char. Without this step, the result might incorrectly include the upper 24 bits, leading to incorrect results. 

(c) 

|| char | int |long long |float |long double|
|-|------|-----|----------|------|-----------|
|+ | 1.25(5)|1.0 (4)| 2.75(11)| J|J |
|− | 1.25(5)| 1.0 (4)| 2.75(11)| J| J|
|∗ | 1.25(5)| 1.0 (4)| 4.5(18)| J| J|
|/ | 1.0(7)| 1.0 (7)| J| J| J|

(d) The name of the subroutine for float addition is `__addsf3`. It is installed at address `0x9d008a9c` in the virtual memory. It takes approximately, `0x30` bytes of data.

**Ch5 Q4:Let us look at the assembly code for bit manipulation. Create a program with the following local variables:**
```
unsigned int u1=33, u2=17, u3;
```
and look at the assembly commands for the following statements:
```
u3 = u1 & u2; // bitwise AND
u3 = u1 | u2; // bitwise OR
u3 = u2 << 4; // shift left 4 spaces, or multiply by 2ˆ4 = 16
u3 = u1 >> 3; // shift right 3 spaces, or divide by 2ˆ3 = 8
```
**How many commands does each use? For unsigned integers, bit-shifting left and right make for computationally efficient multiplies and divides, respectively, by powers of 2.**

Ans: bitwise AND uses 4 commands, bitwise OR uses 3 commands, bit-shifting left uses 3 commands and bit-shifting right uses 9 commands.

**Ch6 Q1:Interrupts can be used to implement a fixed frequency control loop (e.g., 1 kHz). Another method for executing code at a fixed frequency is polling: you can keep checking the core timer, and when some number of ticks has passed, execute the control routine. Polling can also be used to check for changes on input pins and other events. Give pros and cons (if any) of using interrupts vs. polling.**

Ans: Interrupts allow the processor to perform other tasks, while waiting for an event. In polling, the processor has to constantly check for events, even when no event has occured. Interrupts are faster, and provide real time responsiveness to events, polling on the other end, are slower and the reponse is provided only after the next polling cycle.

**Ch6 Q4: (a) What happens if an IRQ is generated for an ISR at priority level 4, subpriority level 2 while the CPU is in normal execution (not executing an ISR)?**

**(b) What happens if that IRQ is generated while the CPU is executing a priority level 2, subpriority level 3 ISR?**

**(c) What happens if that IRQ is generated while the CPU is executing a priority level 4, subpriority level 0 ISR?**

**(d) What happens if that IRQ is generated while the CPU is executing a priority level 6, subpriority level 0 ISR?**

Ans: (a) When an IRQ is generated for an ISR at priority level 4, subpriority level 2 while the CPU is normal execution, it stops the normal execution, jumps to the interrupt execution, and then after executing the interrupt, comes back and resumes the normal execution.

(b) If that IRQ is generated while the CPU is executing a priority level 2, subpriority level 3, the CPU will stop the execution of the level 2 ISR, jump and execute the level 4 ISR, and then resume the execution of level 2 ISR.

(c) If that IRQ is generated while the CPU is executing a priority level 4, subpriority level 0 ISR, the CPU will jump to the execution of the new IRQ, and then come back and resume the current IRQ.

(d) If that IRQ is generated while the CPU is executing a priority level 6, subpriority level 0, then the cPU will first finish the execution of the current ISR, and then jump to the ISR which generated the new IRQ.

**Ch6 Q5: An interrupt asks the CPU to stop what it’s doing, attend to something else, and then return to what it was doing. When the CPU is asked to stop what it’s doing, it needs to remember “context” of what it was working on, i.e., the values currently stored in the CPU registers.**

**(a) Assuming no shadow register set, what is the first thing the CPU must do before executing the ISR and the last thing it must do upon completing the ISR?**

**(b) How does using the shadow register set change the situation?**

Ans: (a) If there is no shadow register set, the CPU first saves the current cached variables in the RAM, this is known as context save. Then the CPU jumps to execute the ISR, after finishing that, it comes back and restores the cached variables from the RAM. This is known as context restore.

(b) If there is a shadow register set, we can specify the interrupt to use the shadow register set, instead of the cached registers, this prevents delay in the interrupt request and its execution, since the CPU does not have to perform context save and restore.

**Ch6 Q8:For the problems below, use only the SFRs IECx, IFSx, IPCy, and INTCON, and their CLR, SET, and INV registers (do not use other registers, nor the bit fields as in IFS0bits.INT0IF). Give valid C bit manipulation commands to perform the operations without changing any uninvolved bits. Also indicate, in English, what you are trying to do, in case you have the right idea but wrong C statements. Do not use any constants defined in Microchip XC32 files; just use numbers.**

**a. Enable the Timer2 interrupt, set its flag status to 0, and set its vector’s priority and subpriority to 5 and 2, respectively.**

**b. Enable the Real-Time Clock and Calendar interrupt, set its flag status to 0, and set its vector’s priority and subpriority to 6 and 1, respectively.**

**c. Enable the UART4 receiver interrupt, set its flag status to 0, and set its vector’s priority and subpriority to 7 and 3, respectively.**

**d. Enable the INT2 external input interrupt, set its flag status to 0, set its vector’s priority and subpriority to 3 and 2, and configure it to trigger on a rising edge**

Ans: 
```
(a) IEC0SET = 0x0100
    IFS0CLR = 0x0100
    IPC2SET = 0x0012

(b) IEC1SET = 0x8000
    IFS1CLR = 0x8000
    IPC8SET = 0x19000000

(c) IEC0SET = 0x8000000
    IFS0CLR = 0x8000000
    IPC6SET = 0x001F

(d) IEC0SET = 0x0800
    IFS0CLR = 0x0800
    IPC2SET = 0x0E000000
    INTCONSET = 0x4
```

**Ch6 Q9: Edit Code Sample 6.3 so that each line correctly uses the “bits” forms of the SFRs. In other words, the left-hand sides of the statements should use a form similar to that used in step 5, except using INTCONbits, IPC0bits, and IEC0bits**

Ans: Check `INT_timing.c` file

**Ch6 Q16: Modify Code Sample 6.2 so the USER button is debounced. How can you change the ISR so the LEDs do not flash if the falling edge comes at the beginning of a very brief, spurious down pulse? Verify that your solution works. (Hint: Any real button press should last much more than 10 ms, while the mechanical bouncing period of any decent switch should be much less than 10 ms. See also Chapter B.2.1 for a hardware solution to debouncing.)**

Ans: Check `INT_ext_int.c` file

**Ch6 Q17: Using your solution for debouncing the USER button (Exercise 16), write a stopwatch program using an ISR based on INT2. Connect a wire from the USER button pin to the INT2 pin so you can use the USER button as your timing button. Using the NU32 Interrupts 111 library, your program should send the following message to the user’s screen: Press the USER button to start the timer. When the USER button has been pressed, it should send the following message: Press the USER button again to stop the timer. When the user presses the button again, it should send a message such as 12.505 seconds elapsed. The ISR should either (1) start the core timer at 0 counts or (2) read the current timer count, depending on whether the program is in the “waiting to begin timing” state or the “timing state.” Use priority level 6 and the shadow register set. Verify that the timing is accurate. The stopwatch only has to be accurate for periods of less than the core timer’s rollover time. You could also try using polling in your main function to write out the current elapsed time (when the program is in the “timing state”) to the user’s screen every second so the user can see the running time.**

Ans: Check `stopwatch.c` file