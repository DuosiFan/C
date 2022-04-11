#include <stdlib.h>

struct deck_tag {
  int **card;
};

typedef struct deck_tag deck_t;

void shuffle(deck_t *deck);

int main(void)
{
  int *pptr[10];
  int ptr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < 10; ++i)
    pptr[i] = &ptr[i];


  deck_t *hand = NULL;
  hand->card = pptr;


  shuffle(hand);
  return 0;
}


void shuffle(deck_t *deck) {
  int *tmp = deck->card[3];
  deck->card[3] = deck->card[5];
  deck->card[5] = tmp;
}
