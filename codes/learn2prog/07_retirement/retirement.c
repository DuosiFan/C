#include <stdio.h>
#include <stdlib.h>

/* derived type definition */
struct _retire_info {
  int months; /* number of months it is applicable to */
  double contribution; /* contributed: +, spent: - */
  double rate_of_return;
};

typedef struct _retire_info retire_info;


/* function prototype */
void retirement(int startAge, double initial, retire_info working,
		retire_info retired);
double update_balance(double current_balance, double rate_of_return,
		      double contribution);

/* driver function */
int main(void)
{
  retire_info working, retired;
  int startAge;
  double initial;

  /* initialization */
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  startAge = 327;
  initial = 21345;

  retirement(startAge, initial, working, retired);
  return 0;
}

/* the required output */
void retirement(int startAge, double initial, retire_info working,
		retire_info retired) {
  int age = startAge; /* age in months */
  double balance = initial;
  int retire_at = startAge + working.months;
  int die_at = retire_at + retired.months;

  /* during working */
  while (age < retire_at) {
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, balance);
    balance = update_balance(balance, working.rate_of_return, working.contribution);
    age++;
  }

  while (age < die_at) {
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, balance);
    balance = update_balance(balance, retired.rate_of_return, retired.contribution);
    age++;
  }
}

double update_balance(double current_balance, double rate_of_return,
		      double contribution) {
  return current_balance + rate_of_return * current_balance + contribution;
}
