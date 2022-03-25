#include "cards.h"
#include <stdio.h>

int main(void) {
  card_t c;

  /* valid card */
  c.value = VALUE_ACE;
  c.suit = DIAMONDS;  
  assert_card_valid(c);

  /* invalid card */
  /* c.value = 100; */
  /* c.suit = 30; */
  /* assert_card_valid(c); */


  for (unsigned i = 0; i < 52; i++) {
    card_t card = card_from_num(i);
    print_card(card);
    putchar('\n');
  }
    
  
  return 0;
}
