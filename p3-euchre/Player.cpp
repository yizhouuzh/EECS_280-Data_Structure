// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Card.h"
class SimplePlayer: public Player {
 private:
  std::string name;
  std::vector<Card> hand;
 public:
  SimplePlayer(const std::string &name): name(name) {
  }
  //EFFECTS returns player's name
  const std::string & get_name() const override {
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
                            int tmp_num = 0;
                            int smc_num = 0;
                            std::string upcard_suit = upcard.get_suit();
                            std::string same_color_suit;
                            if (upcard_suit == Card::SUIT_DIAMONDS) 
                            same_color_suit = Card::SUIT_HEARTS;
                            else if (upcard_suit == Card::SUIT_HEARTS) 
                            same_color_suit = Card::SUIT_DIAMONDS;
                            else if (upcard_suit == Card::SUIT_CLUBS) 
                            same_color_suit = Card::SUIT_SPADES;
                            else if (upcard_suit == Card::SUIT_SPADES) 
                            same_color_suit = Card::SUIT_CLUBS;
                            for (Card i : hand) {
                              if (i.is_face_or_ace()&&i.is_trump(upcard_suit)) {
                                tmp_num += 1;
                              }
                            }
                            for (Card i : hand) {
                              if (i.is_face_or_ace()&&i.is_trump(same_color_suit)) {
                                smc_num += 1;
                              }
                            }
                            bool orderup = false;
                            bool orderup2 = false;
                            if (tmp_num >= 2) {
                              orderup = true;
                            } 
                            if (smc_num >= 1) {
                              orderup2 = true;
                            }
                            if (round == 1) {
                              if (orderup) {
                                order_up_suit = upcard_suit;
                                return true;
                              }
                            } else if (round == 2) {
                              if (is_dealer) {
                                order_up_suit = same_color_suit;
                                return true;
                              } else if (orderup2) {
                                order_up_suit = same_color_suit;
                                return true;
                              }
                            }
                            return false;
                          }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    std::string trump_suit = upcard.get_suit();
    int hand_size = hand.size();
    Card small = upcard;
    int small_index = -1;
    for (int i = 0; i < hand_size; i++) {
      if (Card_less(hand[i], small, trump_suit)) {
        small = hand[i];
        small_index = i;
      }
    }
    if (small_index >= 0) {
      hand.erase(hand.begin() + small_index);
      hand.push_back(upcard);
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override {
    bool all_trump = true;
    Card non_trump;
    int hand_size = hand.size();
    int index;
    for (int k = 0; k < hand_size; k++) {
      if (!hand[k].is_trump(trump)) {
        if (hand[k].is_left_bower(trump)) {
        } else {
          non_trump = hand[k];
          index = k;
          all_trump = false;
          break;
        }
      }
    }
    if (all_trump) {
      int high_index = 0;
      Card high = hand[0];
      for (int i = 0; i < hand_size; i++) {
        if (Card_less(high, hand[i], trump)) {
          high = hand[i];
          high_index = i;
        }
      }
      hand.erase(hand.begin()+high_index);
      return high;
    } else {
      for (int j = 0; j < hand_size; j++) {
        if (!hand[j].is_trump(trump) && 
        Card_less(non_trump, hand[j], trump)) {
          non_trump = hand[j];
          index = j;
        }
      }
      hand.erase(hand.begin()+index);
      return non_trump;
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) override {
    bool have_led = false;
    std::string led_suit = led_card.get_suit(trump);
    for (Card k : hand) {
      if (k.get_suit(trump)==led_suit) {
        have_led = true;
      }
    }
    int hand_size = hand.size();
    if (have_led) {
      std::vector <Card> led;
      std::vector <int> index;
      for (int j = 0; j < hand_size; j++) {
        if (hand[j].get_suit(trump)==led_suit) {
            led.push_back(hand[j]);
            index.push_back(j);
        }
      }
      int led_size = led.size();
      Card high = led[0];
      int high_index = index[0];
      for (int m = 0; m < led_size; m++) {
        if (Card_less(high, led[m], led_card, trump)) {
          high = led[m];
          high_index = index[m];
        }
      }
      hand.erase(hand.begin()+high_index);
      return high;
    } else {
      Card small = hand[0];
      int small_index = 0;
      for (int i = 0; i < hand_size; i++) {
        if (Card_less(hand[i], small, led_card, trump)) {
          small_index = i;
          small = hand[i];
        }
      }
      hand.erase(hand.begin()+small_index);
      return small;
    }
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;

  // Needed to avoid some compiler errors
  
};

class HumanPlayer: public Player {
  private:
  std::string name;
  std::vector<Card> hand;
  void print_hand() {
    std::sort(hand.begin(), hand.end());
    for (size_t i=0; i < hand.size(); ++i) {
      std::cout << "Human player " << name << "'s hand: "
          << "[" << i << "] " << hand[i] << "\n";
    }
  }
  void print_ns() const {
    for (size_t i=0; i < hand.size(); ++i) {
      std::cout << "Human player " << name << "'s hand: "
          << "[" << i << "] " << hand[i] << "\n";
    }
  }
  public:
   HumanPlayer(const std::string &name): name(name) {
  }
  //EFFECTS returns player's name
  const std::string & get_name() const override {
    return name;
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override {
    hand.push_back(c);
    std::sort(hand.begin(), hand.end());
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override {
                            print_ns();
                            std::cout << "Human player " << name 
                            << ", please enter a suit, or \"pass\":\n";
                            std::string input;
                            std::cin >> input;
                            if (input == "pass") {
                              return false;
                            } else if (input == "Spades") {
                              order_up_suit = Card::SUIT_SPADES;
                              return true;
                            } else if (input == "Hearts") {
                              order_up_suit = Card::SUIT_HEARTS;
                              return true;
                            } else if (input == "Clubs") {
                              order_up_suit = Card::SUIT_CLUBS;
                              return true;
                            } else if (input == "Diamonds") {
                              order_up_suit = Card::SUIT_DIAMONDS;
                              return true;
                            }
                            else {
                              return false;
                            }
                          }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override {
    std::sort(hand.begin(), hand.end());
    print_hand();
    int c;
    std::cout << "Discard upcard: [-1]\n";
    std::cout << "Human player " << name << ", please select a card to discard:\n";
    std::cin >> c;
    if (c==-1) {
      return;
    } else {
      hand.erase(hand.begin() + c);
      hand.push_back(upcard);
      std::sort(hand.begin(), hand.end());
    }
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump) override {
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Human player " << name << ", please select a card:\n";
    int num;
    std::cin >> num;
    Card discard = hand[num];
    hand.erase(hand.begin() + num);
    return discard;
  }

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump) override {
    std::sort(hand.begin(), hand.end());
    print_hand();
    std::cout << "Human player " << name << ", please select a card:\n";
    int num;
    std::cin >> num;
    Card discard = hand[num];
    hand.erase(hand.begin() + num);
    return discard;
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
};



Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  } else {
    return new HumanPlayer(name);
  }
}
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

