#include <stdio.h>

#define MAXOP 100
#define NUMBER '0' /* signal that a number is found */


int getop(char s[]);

int main(void)
{
  int type;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    printf("%s\n", s);
  }
  return 0;
}


#include <ctype.h>
int getch();
void ungetch(int c);

/* getop: get next character or numeric operand */
int getop(char s[]) {
  int c;
  
  while (isblank(c = getch()));
  s[0] = c;
  s[1] = '\0'; /* assume s is long enough */

  if (!isdigit(c) && c != '.')
    return c; /* not an operand */

  int pos = 1; /* next available position in s */
  /* collect integer */
  if (isdigit(c)) {
    int i;
    for (i = pos; isdigit(c = getch()); i++)
      s[i] = c;
    pos = i;
  }

  /* collect fraction if possible */
  if (c == '.') {
    s[pos] = '.';
    pos++;

    int i;
    for (i = pos; isdigit(c = getch()); i++)
      s[i] = c;
    pos = i;
  }

  s[pos] = '\0';

  /* buffer last non-digit char if not EOF */
  if (c != EOF)
    ungetch(c);
  
  return NUMBER;
}


/* external variables below are only visible to getch() and ungetch.
   Note that, in this application, the maximum length of buffer is
   1. */
#define BUFFER_SIZE 10
char buffer[BUFFER_SIZE]; /* input stream buffer */
int buffer_pos = 0;    /* next available position in the buffer */

/* getch: a buffered version of getchar */
int getch() { return buffer_pos > 0 ? buffer[--buffer_pos] : getchar(); }

/* ungetch: put char reading from input stream in a buffer. */
void ungetch(int c) {
  if (buffer_pos >= BUFFER_SIZE)
    printf("ungetch: input stream buffer is full\n");
  else
    buffer[buffer_pos++] = c;
}


/* reverse_polish_calculator.c ends here */
