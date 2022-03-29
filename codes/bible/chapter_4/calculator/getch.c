#include <stdio.h>
#include <assert.h>

#define BUFSIZE 10
static char buff[BUFSIZE]; /* input buffer */
static int bufp = 0;      /* next free buffer position */

int getch() { return (bufp > 0) ? buff[--bufp] : getchar(); }
void ungetch(int c) {
  assert(bufp < BUFSIZE);
  buff[bufp++] = c;
}

/* getch.c ends here */
