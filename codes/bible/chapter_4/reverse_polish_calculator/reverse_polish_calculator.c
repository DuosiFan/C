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


/* 1. read the input until the first non blank character */
/*     (named c) put the character in s[0] and put '\0' */
/*     at s[1] */

/* 2. If c is not a digit (0-9) or a decimal point, return */
/*     c the procedure is done */

/* 3. read the integer part */

/* 4. read the decimal point */

/* 5. read the fraction part */

/* 6. put '\0' at the end */

#include <ctype.h>
/* getop: get next character or numeric operand */
int getop(char s[]) {
  int c, i;

  while (isblank(s[0] = c = getchar()));
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;

  i = 0;
  /* read integer part */
  if (isdigit(c))
    while (isdigit(s[++i] = c = getchar()));

  /* read fraction part */
  if (c == '.')
    while (isdigit(s[++i] = c = getchar()));

  /* put '\0' at the end */
  s[i] = '\0';
  
  return NUMBER;
}
