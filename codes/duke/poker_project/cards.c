#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"

/* local functions */
int value_is_valid(unsigned value);
int suit_is_valid(suit_t suit);

void assert_card_valid(card_t c) {
  assert(value_is_valid(c.value) && suit_is_valid(c.suit));
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r) {
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING   : return "NOTHING";
  default: return "";
  }
}

char value_letter(card_t c) {

  switch (c.value) {
  case VALUE_JACK: return 'J';
  case VALUE_QUEEN: return 'Q';
  case VALUE_KING: return 'K';
  case VALUE_ACE: return 'A';
  case 10: return '0';
  default: return c.value + '0';
  }
}


char suit_letter(card_t c) {
  switch (c.suit) {
  case SPADES: return 's';
  case HEARTS: return 'h';
  case DIAMONDS: return 'd';
  case CLUBS: return 'c';
  default: return '\0';
  }
}

void print_card(card_t c) {
  assert_card_valid(c);

  putchar(value_letter(c));
  putchar(suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  /* value of letter to unsigned */
  unsigned value = 100;
  if (value_let >= '2' && value_let <= '9')
    value = value_let - '0';
  else if (value_let == '0')
    value = 10;
  else if (value_let == 'A')
    value = VALUE_ACE;
  else if (value_let == 'K')
    value = VALUE_KING;
  else if (value_let == 'Q')
    value = VALUE_QUEEN;
  else if (value_let == 'J')
    value = VALUE_JACK;
  assert(value >= 2 && value <= VALUE_ACE);

  /* suit */
  suit_t suit;
  switch (suit_let) {
  case 's':
    suit = SPADES;
    break;
  case 'h':
    suit = HEARTS;
    break;
  case 'd':
    suit = DIAMONDS;
    break;
  case 'c':
    suit = CLUBS;
    break;
  default:
    suit = NUM_SUITS;
    break;
  }
  assert(suit != NUM_SUITS);

  
  card_t temp;
  temp.value = value;
  temp.suit = suit;
  return temp;
}

card_t card_from_num(unsigned c) {
  assert(c >= 0 && c < 52);

  card_t temp;

  temp.value = c % 13 + 2;
  temp.suit = c / 13;
  
  return temp;
}

/* self-defined functions */
int value_is_valid(unsigned value) { return value >= 2 && value <= VALUE_ACE; }

int suit_is_valid(suit_t suit) {
  return suit >= SPADES && suit <= CLUBS;
}
