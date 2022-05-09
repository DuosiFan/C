#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "cards.h"
#include "future.h"
#include "input.h"

#define IN 1
#define OUT 0
#define STR_CARD_LENGTH 2 /* length of a string representation of a card */

static int check_card_type(char * token, int n);
static int is_valid_value(char value);
static int is_valid_suit(char suit);
static void free_at_reading(size_t n_hands, future_cards_t *fc, deck_t **decks,
                            FILE *f);

/* The string must be null- and newline-terminated. Unknown card has the form
   ?<digit> and <digit> must be a number between 0 and 9 (inclusive)
   return:
   1. a pointer to a hand if parsed successful
   2. NULL is any error while parsing (memory is freed)

   Modify: seems that ?___ can be more than 9 line ?10 */
#define BUFSIZE 5 /* long enough to hold a token */
deck_t *hand_from_string(const char *str, future_cards_t *fc) {
  deck_t * hand = malloc(sizeof(*hand));
  hand->cards = NULL;
  hand->n_cards = 0;

  int state = OUT;
  int token_length = BUFSIZE;
  int current_loc = 0; /* the location in the token buffer */
  char *token = malloc(token_length*sizeof(*token));
  for (size_t i = 0; i < strlen(str); ++i) {
    char c = str[i];
    if (!isspace(c)) {
      if (current_loc >= token_length - 1) {
	token_length *= 2;
	token = realloc(token, token_length*sizeof(*token));
      } /* buffer is not long enough */
      token[current_loc] = c;
      ++current_loc;
      state = IN;
    }
    else if (state == IN) {
      token[current_loc] = '\0'; /* make the string null terminated */
      int card_type = check_card_type(token, current_loc);		 
      if (card_type == 1) {
	card_t card = card_from_letters(token[0], token[1]);
	add_card_to(hand, card);
      } /* regular card */
      else if (card_type == -1) {
	card_t * ptr = add_empty_card(hand);
	size_t index = atoi(token + 1);
	add_future_card(fc, index, ptr);
      }
      else {
	fprintf(stderr, "card has the form: <value><suit>\n");
	free_deck(hand);
	free(token);
	return NULL;
      }
      
      current_loc = 0;
      state = OUT;
    }
  }
  free(token);
  return hand;
}

/* Though I hate aborting in a function except in main, it is the
   requirement anyway. If any error while parsing or cards is less that 5,
   clean all memory, close the file and abort
   if success, return decks (seems the file is handled by client ) */
deck_t **read_input(FILE *f, size_t *n_hands, future_cards_t *fc) {
  assert(*n_hands == 0);
  deck_t ** hands = NULL;

  char * line = NULL;
  size_t n = 0;
  while (getline(&line, &n, f) > 0) {
    /*check if newline terminated */
    size_t length = strlen(line);
    if (line[length-1] != '\n') {
      /* clean memory */
      free_at_reading(*n_hands, fc, hands, f);
      free(line);
      fprintf(stderr, "line is not newline terminated\n");
      exit(EXIT_FAILURE);
    }

    deck_t *hand = hand_from_string(line, fc);
    if (!hand || hand->n_cards < 5) {
      /* clean memory */
      free_at_reading(*n_hands, fc, hands, f);
      free(line);
      fprintf(stderr, "incorrect hand\n");
      exit(EXIT_FAILURE);
    }

    hands = realloc(hands, (*n_hands + 1) * sizeof(*hands));
    hands[*n_hands] = hand;
    ++(*n_hands);
  }
  free(line);
  return hands;
}

/* local functions */

/* return 1 if a regular known card
   return -1 if value is '?' and suit is a digit
   return 0, otherwise */
static int check_card_type(char * token, int n) {
  assert(n > 0);
  /* possible unknown (no error handling) */
  if (token[0] == '?') {
    return -1;
  }

  if (n == 2 && is_valid_value(token[0]) && is_valid_suit(token[1])) {
    return 1;
  }
  
  return 0;
}

/* if value is a valid card value, i.e. character
   2, ..., 9, 0, J, Q, K, A, return 1
   otherwise return 0*/
static int is_valid_value(char value) {
  if (value >= '2' && value <= '9')
    return 1;
  if (value == '0')
    return 1;
  if (value == 'A')
    return 1;
  if (value == 'K')
    return 1;
  if (value == 'Q')
    return 1;
  if (value == 'J')
    return 1;

  return 0;
}

static int is_valid_suit(char suit) {
  if (suit == 's')
    return 1;
  if (suit == 'h')
    return 1;
  if (suit == 'd')
    return 1;
  if (suit == 'c')
    return 1;
  
  return 0;
}

static void free_at_reading(size_t n_hands, future_cards_t *fc, deck_t **hands,
                            FILE *f) {
  for (size_t i = 0; i < n_hands; ++i) {
    free_deck(hands[i]);
  }
  free(hands);

  if (!fc) {
    if (fclose(f)) {
      fprintf(stderr, "Fail to close file\n");    
    }
    return;
  }
  for (size_t i = 0; i < fc->n_decks; ++i) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  if (fclose(f)) {
    fprintf(stderr, "Fail to close file\n");    
  }
}
