// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Pack.h"
#include "Card.h"
// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
  for (int i = 0; i < PACK_SIZE;i++) {
    int j = i/6;
    int k = i - j*6;
    Card new_card(RANK_NAMES_BY_WEIGHT[k+7], SUIT_NAMES_BY_WEIGHT[j]);
    cards[i] = new_card;
  }
  next = 0;
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
  std::string rank;
  std::string of;
  std::string suit;
  for (int i = 0; i < PACK_SIZE; i++) {
    pack_input >> rank >> of >> suit;
    Card card(rank, suit);
    cards[i] = card;
  }
  next = 0;
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
  return cards[next++];
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
  next = 0;
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
  const int half = PACK_SIZE/2;
  std::array<Card, PACK_SIZE> cs;
  cs = cards;
  for (int i = 0; i < 7; i++) {
    std::array<Card, PACK_SIZE> css;
    css = cs;
    for (int j = 0; j < PACK_SIZE; j++) {
      if (j < half) {
        cs[2*j+1] = css[j];
      } else {
        cs[2*j-24] = css[j];
      } 
    }
  }
  cards = cs;
}

  // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
  if (next == PACK_SIZE) {
    return true;
  } else return false;
}

