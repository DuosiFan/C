#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

#define DEFAULT_TRIALS 10000

static void clean_memory(future_cards_t * fc, deck_t ** hands, size_t n_hands);

int main(int argc, char ** argv) {
  /* Check command line arguments/report errors */
  unsigned n_trials = DEFAULT_TRIALS;
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: ./poker inputfile <num trials>\n");
    return EXIT_FAILURE;
  }
  else if (argc == 3) {
    n_trials = atoi(argv[argc-1]);
  }

  /* read input file */
  FILE * f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "inputfile does not exist\n");
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** hands = read_input(f, &n_hands, fc);
  if (fclose(f)) {
    fprintf(stderr, "Fail to close file\n");    
  }
  if (n_hands < 2) {
    clean_memory(fc, hands, n_hands);
    fprintf(stderr, "You should have at least two hands\n");
    return EXIT_FAILURE;
  }

  /* remaining cards deck */
  deck_t * deck = build_remaining_deck(hands, n_hands);

  /* winning counts */
  unsigned * win_counts = malloc((n_hands + 1)*sizeof(*win_counts));
  for (size_t i = 0; i <= n_hands; ++i)
    win_counts[i] = 0;

  /* Monte Carlo */
  for (size_t i = 0; i < n_trials; ++i) {
    shuffle(deck);
    future_cards_from_deck(deck, fc);
    /* since at least two hands are ensured */
    int winner = 0;
    int is_tie = 0;
    for (size_t j = 1; j < n_hands; ++j) {
      int result = compare_hands(hands[j], hands[winner]);
      if (result > 0) {
	winner = j;
	is_tie = 0;
      }

      if (result == 0) {
	is_tie = 1;
      } /* more than one winner hands are also a tie */
    }

    if (is_tie) {
      ++win_counts[n_hands];
    }
    else {
      ++win_counts[winner];
    }
  }
  clean_memory(fc, hands, n_hands); /* useless in the following */
  free_deck(deck);

  for (size_t i = 0; i < n_hands; ++i) {
    double rate = 100.0*win_counts[i]/n_trials;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_counts[i], n_trials, rate);
  }
  printf("And there were %u ties\n", win_counts[n_hands]);
  free(win_counts);
  
  return EXIT_SUCCESS;
}

static void clean_memory(future_cards_t *fc, deck_t **hands, size_t n_hands) {
  for (size_t i = 0; i < n_hands; ++i) {
    free_deck(hands[i]);
  }
  free(hands);

  for (size_t i = 0; i < fc->n_decks; ++i) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);  
}
