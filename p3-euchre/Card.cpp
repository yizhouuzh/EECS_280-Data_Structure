// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these


// add your code below
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

Card::Card(){
  rank = RANK_TWO;
  suit = SUIT_SPADES;
}

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in){
  rank = rank_in;
  suit = suit_in;
}

  //EFFECTS Returns the rank
std::string Card::get_rank() const{
  return rank;
}

  //EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const{
  return suit;
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const{
  if (Card::get_suit()==trump) return trump;
  else if (Card::is_left_bower(trump)) return trump;
  else return Card::get_suit();
}

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
  if (get_rank()==RANK_JACK||get_rank()==RANK_QUEEN||
  get_rank()==RANK_KING||get_rank()==RANK_ACE) return true;
  else return false;
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
  if (get_suit()==trump && get_rank()==RANK_JACK) {
    return true;
  } else return false;
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
  if (get_rank()==RANK_JACK) {
    if (get_suit()==SUIT_DIAMONDS && trump==SUIT_HEARTS) return true;
    else if (trump==SUIT_DIAMONDS && get_suit()==SUIT_HEARTS) return true;
    else if (get_suit()==SUIT_SPADES && trump==SUIT_CLUBS) return true;
    else if (trump==SUIT_SPADES && get_suit()==SUIT_CLUBS) return true;
    else return false;
  } else return false;
}

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
  if(get_suit()==trump) return true;
  else if (is_left_bower(trump)) return true;
  else return false;
}



//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
  int lhs_rank;
  int rhs_rank;
  int lhs_suit;
  int rhs_suit;
  for (int i = 0; i < NUM_RANKS; i++) {
      if (RANK_NAMES_BY_WEIGHT[i]==lhs.get_rank()) {
        lhs_rank = i;
      }
      if (RANK_NAMES_BY_WEIGHT[i]==rhs.get_rank()) {
        rhs_rank = i;
      }
  }
  for (int i = 0; i < NUM_SUITS; i++) {
      if (SUIT_NAMES_BY_WEIGHT[i]==lhs.get_suit()) {
        lhs_suit = i;
      }
      if (SUIT_NAMES_BY_WEIGHT[i]==rhs.get_suit()) {
        rhs_suit = i;
      }
  }
  if (lhs_rank < rhs_rank) {
    return true;
  } else if (lhs_rank == rhs_rank) {
    if (lhs_suit < rhs_suit) {
      return true;
    } else return false;
  } else return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  if (lhs < rhs || lhs == rhs) {
    return true;
  } else return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  int lhs_rank;
  int rhs_rank;
  int lhs_suit;
  int rhs_suit;
  for (int i = 0; i < NUM_RANKS; i++) {
      if (RANK_NAMES_BY_WEIGHT[i]==lhs.get_rank()) {
        lhs_rank = i;
        break;
      }
  }
  for (int i = 0; i < NUM_RANKS; i++) {
      if (RANK_NAMES_BY_WEIGHT[i]==rhs.get_rank()) {
        rhs_rank = i;
        break;
      }
  }
  for (int i = 0; i < NUM_SUITS; i++) {
      if (SUIT_NAMES_BY_WEIGHT[i]==lhs.get_suit()) {
        lhs_suit = i;
        break;
      }
  }
  for (int i = 0; i < NUM_SUITS; i++) {
      if (SUIT_NAMES_BY_WEIGHT[i]==rhs.get_suit()) {
        rhs_suit = i;
        break;
      }
  }
  if (lhs_rank > rhs_rank) {
    return true;
  } else if (lhs_rank == rhs_rank) {
    if (lhs_suit > rhs_suit) {
      return true;
    } else return false;
  } else return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
  if (lhs > rhs || lhs == rhs) {
    return true;
  } else return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() == rhs.get_rank()&&lhs.get_suit()==rhs.get_suit()) {
    return true;
  } else return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
  if (lhs == rhs) return false;
  else return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
  int suit_num = 0;
  for (int i = 0; i < NUM_SUITS; i++) {
      if (SUIT_NAMES_BY_WEIGHT[i]==suit) {
        suit_num = i;
        break;
      }
  }
  if (suit_num < 2) {
    return SUIT_NAMES_BY_WEIGHT[suit_num+2];
  } else {
    return SUIT_NAMES_BY_WEIGHT[suit_num-2];
  }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
  if (a==b) return false;
  if (b.Card::is_right_bower(trump)) {
    return true;
  } else if (b.Card::is_left_bower(trump)) {
    if (!a.Card::is_right_bower(trump)) return true;
  } else if (b.get_suit(trump)==trump) {
    if (a.get_suit(trump)!=trump && !a.Card::is_left_bower(trump)) {
      return true;
    } else if (a.get_suit(trump)==trump) {
      if (a.Card::is_left_bower(trump)) {
        return false;
      } else if (!a.Card::is_right_bower(trump)) {
        if (a < b) return true;
      }
    }
  } else {
    if (a.get_suit() != trump) {
      if (!a.Card::is_left_bower(trump)) {
        if (a < b) return true;
      }
    }
  }
  return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
                if (a==b) return false;
                if (led_card.get_suit(trump) == trump) {
                  return Card_less(a, b, trump);
                }
                  if (b.Card::is_right_bower(trump)) {
                    return true;
                  } else if (b.Card::is_left_bower(trump) && 
                  !a.Card::is_right_bower(trump)) { return true;
                  } else if (b.get_suit(trump)==trump) {
                    if (a.get_suit(trump)!=trump && !a.Card::is_left_bower(trump)) {
                      return true;
                    } else if (a.get_suit(trump)==trump) {
                      if (!a.Card::is_right_bower(trump)&& 
                      !a.Card::is_left_bower(trump) && a < b) return true;
                    } 
                  } else if (b.get_suit(trump)==led_card.get_suit(trump)) {
                    if (a.get_suit(trump)!=trump && !a.Card::is_left_bower(trump)) {
                      if (a.get_suit(trump)!=led_card.get_suit(trump)) {
                        return true;
                      } else if (a.get_suit(trump)==led_card.get_suit(trump)&&a<b) 
                      return true;
                    }
                  } else {
                    if (a.get_suit(trump)!=trump && !a.Card::is_left_bower(trump) 
                        && a.get_suit(trump)!=led_card.get_suit(trump) && a < b) 
                        return true;
                  }
                
                return false;
              }

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
