#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "calc.h"

#define MAXOP 100    /* maximum operand length */

/* reverse Polish calculator */
int main(void)
{
  int type; /* operator or operand or shit */
  char s[MAXOP];
  double op2;

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      assert(op2 != 0.0);
      push(pop() / op2);
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      type = EOF;
      break;
    }
    assert(type != EOF);
  }
  
  return 0;
}

/* main.c ends here */
