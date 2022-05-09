#include "cards.h"
#include "deck.h"
#include "future.h"
#include <stdio.h>
#include <stdlib.h>

/* assume decks[0] -- decks[n_decks-1] has been allocated and initialized */
void add_future_card(future_cards_t *fc, size_t index, card_t *ptr) {
  if (index >= fc->n_decks) {
    fc->decks = realloc(fc->decks, (index+1)*sizeof(*(fc->decks)));
    for (size_t i = fc->n_decks; i <= index; ++i) {
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
    }
    fc->decks[index].cards = malloc(sizeof(*(fc->decks[index].cards)));
    fc->decks[index].cards[0] = ptr;
    fc->decks[index].n_cards = 1;

    fc->n_decks = index + 1;
  } /* new deck */
  else if (index >= 0) {
    size_t n_cards = fc->decks[index].n_cards;
    card_t ** cards = fc->decks[index].cards;
    cards = realloc(cards, (n_cards+1)*sizeof(*cards));
    cards[n_cards] = ptr;
    
    ++fc->decks[index].n_cards;
    fc->decks[index].cards = cards;
  } /* old deck */
}

void future_cards_from_deck(deck_t *deck, future_cards_t *fc) {
  if (fc->n_decks > deck->n_cards) {
    fprintf(stderr, "Not enough cards in the deck\n");
    return;
  }

  for (size_t i = 0; i < fc->n_decks; ++i) {
    for (size_t j = 0; j < fc->decks[i].n_cards; ++j) {
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
    }
  }
}
