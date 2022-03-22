#include <stdio.h>
#include <ctype.h>

#define BASE 10.0

double atof(char s[]);

int main(void)
{
  char s[] = "1.2e+3";
  double val = atof(s);

  printf("%f\n", val);
  return 0;
}

/* atof: conver string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign, expsign, exp;

  for (i = 0; isspace(s[i]); i++); /* skip blanks */

  /* check sign */
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '-' || s[i] == '+')
    i++;

  /* read integer part */
  for (val = 0.0; isdigit(s[i]); i++)
    val = BASE*val + (s[i] - '0');

  /* check the decimal point exists and read fraction */
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = BASE*val + (s[i] - '0');
    power *= BASE;
  }

  /* exponent part */  
  if (s[i] == 'e' || s[i] == 'E')
    i++;
  expsign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '-' || s[i] == '+')
    i++;
  for (exp = 0; isdigit(s[i]); i++)
    exp = BASE*exp + (s[i] - '0');

  /* modify power based on the exp */
  if (expsign > 0)
    while (exp > 0) {
      power /= BASE;
      exp--;
    }
  else
    while (exp < 0) {
      power *= BASE;
      exp--;
    }
  
  return  sign*val/power;
}

/* string2numeric.c ends here */
