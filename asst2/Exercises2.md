# ME333 Assignment 2
Author: Pushkar Dave
## Exercises from A Crash Course in C
**Q18: Invoking the `gcc` compiler with a command like `gcc myprog.c -o myprog` actually initiates four steps. What are the four steps called, and what is the output of each step?**

A: The four steps are called **Preprocessing**, **Compiling**, **Assembling** and **Linking**.
- The Preprocessor takes the `myprog.c` source code and produces an equivalent .c source code, performing operations such as removing comments.
- The Compiling step turns the preprocessed code into assembly code for the specific processor. 
- In the Assembling step, the assembler converts the assembly instructions into processor-dependent machine-level binary object code.
- In the Linking step, the linker takes one or more object code files and produces a single executable file.

---
**Q19: What is main's return type and what is the meaning of its return value?**

A: The return type of the `main` function is `int`. This means that the main function should end by returning a value of type `int`.

---
**Q21: Consider three `unsigned char` i, j and k, with values 60, 80, and 200, respectively. Let `sum` also be an `unsigned char`. For each of the following, give the value of `sum` after performing the addition. (a) `sum = i + j`; (b) `sum = i + k`; (c) `sum = j + k`;**

A : (a) sum = 140 \
(b) sum = 4 \
(c) sum = 24

---

**Q22: For the variables defined as**
  ```
int a = 2, b = 3, c;
float d = 1.0, e = 3.5, f;
```
**give the values of the following expressions. (a) `f = a/b`; (b) `f = ((float) a)/b`; (c) `f = (float) (a/b)`; (d) `c = e/d`; (e) `c = (int) (e/d)`; (f) `f = ((int) e)/d`;**

A: (a) 0.0 \
(b) 0.6667 \
(c) 0.0 \
(d) 3 \
(e) 3 \
(f) 3 

---
**Q27: You have written a large program with many functions. Your program compiles without errors, but when you run the program with input for which you know the correct output, your program returns the wrong result. What do you do next? Describe your systematic strategy for debugging.**

A: The most simple step can be to print out the values of the variables within the functions. We can compare the values of the variables with the expected values (since we know the correct output), and check which particular variable might be causing an issue. When we can identify that variable, we check on all the functions which modify that variable and try to find the cause of error. Another common technique in modern IDEs is to use the debugger. In the debugger, we can set breakpoints, where we can stop the execution of the program and check the current values of variables and the call stack. This can help us isolate the line in the program which is causing the wrong result.

---
**Q28: Erase all the comments in `invest.c`, recompile, and run the program to make sure it still functions correctly. You should be able to recognize what is a comment and what is not. Turn in your modified `invest.c` code.**

A: Check `invest.c` file

---
**Q30: Consider this array definition and initialization:**
```
int x[4] = {4, 3, 2, 1};
```
**For each of the following, give the value or write "error/unknown" if the compiler will generate an error or the value is unknown. (a)`x[1]` (b)`*x` (c)`*(x+2)` (d)`(*x)+2` (e)`*x[3]` (f)`x[4]` (g)`*(&(x[1]) + 1)`**

A: (a) 3 \
(b) 4 \
(c) 2 \
(d) 6 \
(e) error \
(f) unknown \
(g) 2

---
**Q31: For the (strange) code below, what is the final value of i? Explain why.**
```
int i, k = 6;
i = 3*(5>1) + (k=2) + (k==6);
```

A:  i = 5 \
The first expression 3*(5 > 1) evaluates to 3, since (5 > 1) is true, and integer value of a true boolean is 1. The second expression is not a boolean, but an assignment operation, and so it evaluates to 2, the value of k. For the third and final expression, (k==6) is false, and so the integer value is zero. Therefore, i is equal to the sum of 3, 2 and 0, which is 5.

---
**Q32: As the code below is executed, give the value of `c` in hex at the seven break points indicated, (a)-(g)**

```
unsigned char a=0x0D, b=0x03, c;
c = ~a;     // (a)
c = a & b;  // (b)
c = a | b;  // (c)
c = a ^ b;  // (d)
c = a >> 3; // (e)
c = a << 3; // (f)
c &= b;     // (g)
```

A: (a) 0xF2 \
(b) 0x01 \
(c) 0x0F \
(d) 0x0E \
(e) 0x01 \
(f) 0x68 \
(g) 0x00 

---
**Q34**

**Q35**