#include <stdio.h>

int get_strindex1(char source[], char searchfor[]);
int get_strindex2(char source[], char searchfor[]);
void test_get_strindex1(char source[], char searchfor[], int value, char msg[]);
void test_get_strindex2(char source[], char searchfor[], int value, char msg[]);

int main(void)
{
  char line[] = "Would not we shatter it to bits -- and then titit\n";

  printf("\nTesting get_strindex1\n");
  printf("----------------------------------------\n\n");
  
  test_get_strindex1(line, "it", 21, "basic functionality");
  test_get_strindex1(line, "thene", -1, "out of range");

  printf("\nTesting get_strindex2\n");
  printf("----------------------------------------\n\n");

  test_get_strindex2(line, "it", 28, "basic functionality");
  test_get_strindex2(line, "tit", 46, "repeated pattern \"tit\"");
  
  return 0;
}

/* get_strindex1: search for string t in s and return the
   index of the leftmost occurrence of t in s, or -1 if
   there is none. */
int get_strindex1(char s[], char t[]) {
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i,  k= 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
    if (k > 0 && t[k] == '\0') return i; /* length must be at least 1 */
  }
  
  return -1; /* no match */
}

/* get_strindex2: search for string t in s and return the
   index of the rightmost occurrence of t in s, or -1 if
   there is none. By my understanding, the returned index
   should be the first index of the last occurrence */
int get_strindex2(char s[], char t[]) {
  int i, j, k;
  int index;

  /* no match at the beginning */
  index = -1;
  
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i,  k= 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
    if (k > 0 && t[k] == '\0') index = i; /* length must be at least 1 */
  }
  
  return index; /* no match */
}

void test_get_strindex1(char s[], char t[], int value, char msg[]) {
  printf("%s: ", msg);
  if (get_strindex1(s, t) == value)
    printf("PASS\n");
  else
    printf("FAIL\n");
}

void test_get_strindex2(char s[], char t[], int value, char msg[]) {
  printf("%s: ", msg);
  if (get_strindex2(s, t) == value)
    printf("PASS\n");
  else
    printf("FAIL\n");
}

/* strindex.c ends here */
