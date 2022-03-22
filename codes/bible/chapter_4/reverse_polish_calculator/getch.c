#include <stdio.h>


/* function prototype */
int getch();
void ungetch(int c);

int main(void)
{
  char s[] = "abcd";

  for (int i = 0; s[i] != '\0'; i++)
    ungetch(s[i]);
  
  return 0;
}

#define BUFFER_SIZE 10
char buffer[BUFFER_SIZE]; /* input stream buffer */
int buffer_pos = 0;       /* next available position in the buffer */

/* getch: a buffered version of getchar */
int getch() { return buffer_pos > 0 ? buffer[--buffer_pos] : getchar(); }

/* ungetch: put char reading from input stream in a buffer. */
void ungetch(int c) {
  if (buffer_pos >= BUFFER_SIZE)
    printf("ungetch: input stream buffer is full\n");
  else
    buffer[buffer_pos++] = c;
}

/* getch.c ends here */
