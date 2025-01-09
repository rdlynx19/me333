# ME333 Assignment 1
Author: Pushkar Dave
## Exercises from A Crash Course in C
**Q2: Explain what a pointer variable is, and how it is different from a non-pointer variable**

A: A pointer variable is used to store the address of another variable. The syntax of declaring a pointer variable is:
```
int *ip;
```
Here, `int` represents the data type the pointer points to and `ip` is the name of the variable. To get the address value the pointer is pointing to you can print out the value of `ip`. To get the value at that address print `*ip` where `*` is the dereference operator.

Key difference from a non-pointer variable is that you can get both the address and the value from a pointer variable, however a non-pointer variable only has the value stored in it. Also, during declaration of a pointer, the compiler will assign memory needed to hold an address (a platform dependent value), where as declaring a non-pointer variable will allocate memory needed to hold data of the variable type (eg: int, float, double)

---
**Q3: Explain the difference between interpreted and compiled code**

A: Interpreted code means the commands are converted to machine code during run-time. Compiled code means commands are converted to machine code during compile time, that is before running the code. Example, MATLAB is an interpreted language, while C is a compiled language.

---

**Q4: Write the following hexadecimal (base-16) numbers in eight-digit binary (base-2) and
three-digit decimal (base-10). Also, for each of the eight-digit binary representations,
give the value of the most significant bit. (a) 0x1E. (b) 0x32. (c) 0xFE.
(d) 0xC4**

A:  

(a) Binary: 0001 1110 \
        Decimal: 30 
    
(b) Binary: 0011 0010 \
Decimal: 50

(c) Binary: 1111 1110 \
Decimal: 254

(d) Binary: 11000100 \
Decimal: 196

---

**Q6: Assume that each byte of memory can be addressed by a 16-bit address, and every 16-bit
address has a corresponding byte in memory. How many total bits of memory do you
have?**

A: $2^{16} * 8$ bits of memory!

---

**Q7: (Consult the ASCII table.) Let ch be of type char . (a) The assignment ch = ’k’ can be
written equivalently using a number on the right side. What is that number? (b) The
number for ’5’ ? (c) For ’=’ ? (d) For ’?’**

A:  (a) 97 \
(b) 53 \
(c) 61 \
(d) 63

---

**Q8: What is the range of values for an unsigned char , short , and double data type?**

A: unsigned char - 0 to 255, unsigned short - 0 to $2^{16}-1$, unsigned double - 0 to $2^{64} -1$


---

**Q10: Explain the difference between unsigned and signed integers.**

A: Unsigned integers have no sign attached to them, so they can represent only positive values (for example, 0 to $2^{32} - 1$), while signed integers have signs attached to them so they can represent both negative and positive values,(for example, $-2^{31}$ to $2^{31}+1$)

---

**Q11: a) For integer math, give the pros and cons of using char s vs. int s. (b) For floating point
math, give the pros and cons of using float s vs. double s. (c) For integer math, give the
pros and cons of using char s vs. float s**

A: a) For integer math, the advantage of using `char s` is that it uses only 1 byte of memory compared to 4 bytes of `int s`, so for low memory operations we can prefer char over int. However, it can also cause overflow issues easily, so for larger numbers we should prefer int.

b) For floating point math, `float s` can be preferred over `double s` when memory is a constraint since float is 4 bytes compared 8 bytes of double. Advantage in using double is it offers higher precision since it is bigger in size so there are less chances of any floating point error.

c) For integer math, `char s` is preferred over `float s` since it can provide correct values without any rounding off errors. char also has smaller memory usage compared to float. However, for larger numbers out of the range of char, we can use float provided we are taking care of not losing precision due to any rounding off errors.

---

**Q16: Technically the data type of a pointer to a double is “pointer to type double .” Of the
common integer and floating point data types discussed in this chapter, which is the most
similar to this pointer type? Assume pointers occupy eight bytes** 

A: If the pointer to type double occupies 8 bytes, the most similar data type to it is `long int, long long int`.

---
**Q17: To keep things simple, let us assume we have a microcontroller with only $(2^{8})$ = 256 bytes
of RAM, so each address is given by a single byte. Now consider the following code
defining four global variables:**
```
unsigned int i, j, *kp, *np;
```
**Let us assume that the linker places i in addresses 0xB0..0xB3, j in 0xB4..0xB7, kp in
0xB8, and np in 0xB9. The code continues as follows:**
```
                // (a) the initial conditions, all memory contents unknown
kp = &i;        // (b)
j = *kp;        // (c)
i = 0xAE;       // (d)
np = kp;        // (e)
*np = 0x12;     // (f)
j = *kp;        // (g)
```
**For each of the comments (a)-(g) above, give the contents (in hexadecimal) at the
address ranges 0xB0..0xB3 (the unsigned int i), 0xB4..0xB7 (the unsigned int j),
0xB8 (the pointer kp ), and 0xB9 (the pointer np ), at that point in the program, after
executing the line containing the comment. The contents of all memory addresses are
initially unknown or random, so your answer to (a) is “unknown” for all memory
locations. If it matters, assume little-endian representation**

A: (a) 
0xB0 to 0xB3 - unknown \
0xB4 to 0xB7 - unknown \
0xB8 - unknown \
0xB9 - unknown 

(b)
0xB0 to 0xB3 - unknown \
0xB4 to 0xB7 - unknown \
0xB8 - 0xB0 \
0xB9 - unknown

(c) 
0xB0 to 0xB3 - unknown \
0xB4 to 0xB7 - corresponding values from 0xB0 to 0xB3 (unknown) \
0xB8 - 0xB0 \
0xB9 - unknown

(d)
0xB0 to 0xB3 - 0xAE \
0xB4 to 0xB7 - unknown \
0xB8 - 0xB0 \
0xB9 - unknown

(e)
0xB0 to 0xB3 - 0xAE \
0xB4 to 0xB7 - unknown \
0xB8 - 0xB0 \
0xB9 - 0xB0

(f)
0xB0 to 0xB3 - 0x12 \
0xB4 to 0xB7 - unknown \
0xB8 - 0xB0 \
0xB9 - 0xB0

(g)
0xB0 to 0xB3 - 0x12 \
0xB4 to 0xB7 - 0x12 \
0xB8 - 0xB0 \
0xB9 - 0xB0

---