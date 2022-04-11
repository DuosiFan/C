#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  size_t n = hand->n_cards;
  for (size_t i = 0; i < n; ++i)
    print_card(*(hand->cards[i]));  
}

int deck_contains(deck_t * d, card_t c) {
  for (size_t i = 0; i < d->n_cards; ++i) {
    card_t current = *(d->cards[i]);
    if (current.suit == c.suit && current.value == c.value)
      return 1;
  }  
  return 0;
}

void shuffle(deck_t * d){
  size_t n = d->n_cards;  
  /* Fisher-Yates shuffle */
  for (size_t i = 0; i < d->n_cards; ++i) {
    /* generate a random number between i to n (exclusive) */
    int j = i + random()%(n-i);

    /* swap */
    card_t *swap = d->cards[i];
    d->cards[i] = d->cards[j];
    d->cards[j] = swap;
  }
}

void assert_full_deck(deck_t * d) {
  for (size_t i = 0; i < 52; ++i)
    assert(deck_contains(d, card_from_num(i)));
}
