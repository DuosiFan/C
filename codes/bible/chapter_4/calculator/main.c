#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAXOP 100    /* maximum operand length */
#define NUMBER '0'   /* number flag */


/* function prototype */
int getop(char s[]);
void push(double f);
double pop(void);

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
      printf("error: invalid command\n");
      break;
    }
  }
  
  return 0;
}

#define MAXDEPTH 100 /* maximum stack depth */
int sp = 0;          /* next available stack position */
double stack[MAXDEPTH];
void push(double f) {
  if (sp < MAXDEPTH)
    stack[sp++] = f;
  else
    printf("error: full stack\n");
}

double pop() {
  if (sp > 0)
    return stack[--sp];
  else {
    printf("error: empty stack\n");
    return 0.0;
  }
}


#include <ctype.h>
int getch(void);
void ungetch(int c);

int getop(char s[]) {
  int c;
  /* skip blanks */
  while (isblank(s[0] = c = getch()));
  s[1] = '\0';

  /* not a number */
  if (!isdigit(c) && c != '.')
    return c;

  int i = 0;
  /* collect integer part */
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()));
  /* collect fraction part */
  if (c == '.')
    while (isdigit(s[++i] = c = getch()));
  /* add termintor */
  s[i] = '\0';

  if (c != EOF)
    ungetch(c);

  return NUMBER;
}

#define BUFSIZE 10
int buff[BUFSIZE]; /* input buffer */
int bufp = 0;      /* next free buffer position */

int getch() { return (bufp > 0) ? buff[--bufp] : getchar(); }
void ungetch(int c) {
  if (bufp < BUFSIZE)
    buff[bufp++] = c;
  else
    printf("ungetch: too many characters\n");
}
