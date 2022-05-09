void rotate(char matrix[10][10]) {
  char matrixc[10][10]; /* local copy */

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrixc[i][j] = matrix[9-j][i];

  /* copy back */
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      matrix[i][j] = matrixc[i][j];
}
