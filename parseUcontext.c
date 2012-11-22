#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <ucontext.h>

#define SOL 99

#ifndef REG_EIP
#define REG_EIP 0
#define REG_EBP 0
#define REG_ESP 0
#define REG_UESP 0
#endif

long unsigned int probeUCStack(ucontext_t *mycontext);

int main(int argc, char **argv)
{

  ucontext_t mycontext;
  int err;


  printf("WORDSIZE %d\n", __WORDSIZE);
  assert(__WORDSIZE == 32); // Do this project on a 32-bit x86 linux machine
  printf("NGREG %d\n", NGREG);
  assert(NGREG == 19);  // Do this project on a 32-bit x86 linux machine

  err = getcontext(&mycontext);
  assert(!err);

  printf("A ucontext_t is %d bytes\n", (int)sizeof(ucontext_t));
  // TBD: Fill in ucontext size above. Hint: use sizeof().

  unsigned int anotherSample = probeUCStack(&mycontext);

  /*
   * Now, look inside of the ucontext you just saved.
   *
   * Warning: The automated grading scrips won't check all of these.
   * Sanity check them yourself. Think about what they mean and what
   * they must be!
   *
   * For example, are both argc and err on the stack?
   */
  /*
   * First, think about program counters (called eip in x86)
   */
  printf("The memory address of the function main() is 0x%lx\n", (long unsigned int)&main); /* once we're on the right architecture, make sure to cast this properly. It might have to be long unsigned int. */
  printf("The memory address of the program counter (EIP) saved in mycontext is 0x%x\n", (unsigned int)mycontext.uc_mcontext.gregs[REG_EIP]);

  /*
   * Now, think about stacks.
   *
   * Be able to answer the following questions: Does the stack grow up or down?
   * Does ucontext_t.uc_stack point to the current stack pointer? Top of the
   * stack? Bottom of the stack? None of the above? What are the stack related
   * things in mycontext.uc_mcontext.gregs[]? What's the difference between
   * REG_UESP and REG_ESP in the gregs array?
   *
   * Hint: It might help to run the program using gdb or xxx (a graphical
   * front end to gdb) and put a breakpoint at entry to main and/or the
   * call to getcontext().  Then use "info registers" to see the values
   * of the registers and use "next"/"step" to advance to the next instruction.
   * You can also use "print mycontext" to see the values stored in that struct.
   *
   * Anther experiment you might try is changing the various candidates for the
   * stack pointer to nonsensical values and (probably using a debugger) see
   * which one actually gets restored to the processor.
   *
   * Don't move on to the next part of the lab until you know how to change
   * the stack in a context when you manipulate a context to create a new thread.
   */
  printf("The memory address of the local variable err is 0x%8x\n", (unsigned int)(mycontext.uc_mcontext.gregs[REG_EBP] - 4 - sizeof(ucontext_t)));
  printf("The memory address of the argument argc is 0x%8x\n", (unsigned int)(mycontext.uc_mcontext.gregs[REG_EBP] + 8));
  printf("The value of ucontext_t.uc_stack.ss_sp is 0x%08lx\n", (long unsigned int)(mycontext.uc_stack.ss_sp)); /* change to appropriate casting if warnings persist on correct architecture */
  printf("The value of ucontext_t.uc_stack.ss_size is 0x%08x\n", (unsigned int)(mycontext.uc_stack.ss_size));
  printf("The value of anotherSample is 0x%08x\n", anotherSample);
  printf("The stack pointer stored as one of the registers (ESP) in uc_mcontext is 0x%08x\n", (unsigned int)mycontext.uc_mcontext.gregs[REG_ESP]);
  printf("The stack pointer stored as another one of the `registers` (UESP) in uc_mcontext is 0x%08x\n", (unsigned int)mycontext.uc_mcontext.gregs[REG_UESP]);


  printf("The number of bytes pushed onto the stack between argc and err was 0x%x\n", (unsigned int)(12 + sizeof(ucontext_t)));
  /* Which is the right one to use? */
  printf("The number of bytes pushed onto the stack between err and when the stack was saved to mycontext was 0x%x\n",
         (unsigned int)(mycontext.uc_mcontext.gregs[REG_ESP] - (mycontext.uc_mcontext.gregs[REG_ESP] - 4 - sizeof(ucontext_t))));


         return 0;  
}


/*
 * This function should call getcontext and
 * return the value of the uc_stack.ss_sp.
 *
 * Is this the current stack pointer? no. The
 * top of the stack? no. The bottom of the stack? no.
 * One thing to do is to compare it to the
 * uc_stack.ss_sp saved in main().
 */
long unsigned int
probeUCStack(ucontext_t *mycontext)
{
  int err;
  
  err = getcontext(mycontext); /*pass pointer of mycontext to function */
  assert(!err);
  return (long unsigned int)mycontext->uc_stack.ss_sp; /* be sure to use proper casting on the final machine. */
}

