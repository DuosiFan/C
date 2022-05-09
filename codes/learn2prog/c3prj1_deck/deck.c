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

/* add_card_to: assume deck is allocated outside and is initialized */
void add_card_to(deck_t *deck, card_t c) {
  card_t * new_card = malloc(sizeof(*new_card));
  /* copy the card (deep copy) */
  new_card->suit = c.suit;
  new_card->value = c.value;

  /* reallocate the array ptr */
  deck->cards = realloc(deck->cards, (deck->n_cards + 1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = new_card; /* shallow copy */
  ++deck->n_cards;
}

void free_deck(deck_t *deck) {
  if (!deck) {
    return;
  } /* handle NULL case */  
  for (size_t i = 0; i < deck->n_cards; ++i) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

card_t *add_empty_card(deck_t *deck) {
  card_t c = {.value = 0, .suit = 0};
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t *make_deck_exclude(deck_t *excluded_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;

  for (unsigned c = 0; c < 52; ++c) {
    card_t card = card_from_num(c);
    if (!deck_contains(excluded_cards, card)) {
      add_card_to(deck, card);
    }    
  }
  
  return deck;
}

deck_t *build_remaining_deck(deck_t **hands, size_t n_hands) {
  deck_t * known_cards = malloc(sizeof(*known_cards));
  known_cards->cards = NULL;
  known_cards->n_cards = 0;
  for (size_t i = 0; i < n_hands; ++i) {
    for (size_t j = 0; j < hands[i]->n_cards; ++j) {
      card_t c = *hands[i]->cards[j];
	if (!deck_contains(known_cards, c)) {
	  add_card_to(known_cards, c);
	}
    }
  }
  deck_t * deck = make_deck_exclude(known_cards);
  free_deck(known_cards);
  
  return deck;
}
