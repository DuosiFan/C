#include <stdio.h>
#include <ctype.h>

#define BASE 10.0

double atof(char s[]);

int main(void)
{
  char s[] = ".45111";
  double val = atof(s);

  printf("%7.5f\n", val);
  return 0;
}

/* atof: conver string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign;

  for (i = 0; isspace(s[i]); i++); /* skip blanks */

  /* check sign */
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '-' || s[i] == '+')
    i++;

  /* read integer part */
  for (val = 0.0; isdigit(s[i]); i++)
    val = BASE*val + (s[i] - '0');

  /* check the decimal point exists */
  if (s[i] == '.')
    i++;

  /* read fraction part */
  for (power = 1.0; isdigit(s[i]); i++) {
    val = BASE*val + (s[i] - '0');
    power *= BASE;
  }
  
  return  sign*val/power;
}

/* string2numeric.c ends here */
