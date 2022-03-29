#include <stdio.h>
#include <assert.h>

#include "calc.h"

#define MAXDEPTH 100 /* maximum stack depth */
static int sp = 0;          /* next available stack position */
static double stack[MAXDEPTH];
void push(double f) {
  assert(sp < MAXDEPTH);
  stack[sp++] = f;
}

double pop() {
  assert(sp > 0);
  return stack[--sp];
}

/* stack.c ends here */
