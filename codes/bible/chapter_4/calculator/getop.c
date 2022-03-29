#include <stdio.h>
#include <ctype.h>

#include "calc.h"
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

/* getop.c ends here */
