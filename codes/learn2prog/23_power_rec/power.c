
unsigned power(unsigned x, unsigned y) {
  /* base case */
  if (y == 0U)
    return 1U;

  return x * power(x, y - 1);
}
