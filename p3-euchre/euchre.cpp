// Project UID 1d9f47bfc76643019cfbf037641defe1
#include<iostream>
#include<fstream>
#include<string>
#include "Player.h"
#include "Card.h"
#include "Pack.h"
class Game {
 public:
  Game(Player *a, Player *b, Player *c, Player *d) {
    players.push_back(a);
    players.push_back(b);
    players.push_back(c);
    players.push_back(d);
  }
  void play(std::string shuf, int pt, Pack p) {
    pack = p;
    ptw = pt;
    if (shuf == "shuffle") {
      shuff = true;
    } else shuff = false;
    while (check()==0) {
      play_full();
    }
    if (check()==1) {
      std::cout << players[0]->get_name() << " and "
      << players[2]->get_name() << " win!";
    } else {
      std::cout << players[1]->get_name() << " and "
      << players[3]->get_name() << " win!";
    }
    std::cout << std::endl;
  }
 private:
  std::vector<Player*> players;
  Pack pack;
  std::vector<int> points = {0, 0, 0, 0};
  int dealer = 0;
  int trump_maker;
  int mt_round = 1;
  Card upcard;
  std::string order_up_suit;
  int t1_point=0;
  int t2_point=0;
  int ptw;
  int hand = 0;
  bool shuff;
  // ...
  void shu() {
    pack.shuffle();
  }
  void deal_cards(int num, Player *pl) {
    for (int i = 0; i < num; i++) {
      upcard = pack.deal_one();
      pl->add_card(upcard);
    }
  }
  void batch(int dealer, int batch_round) {
    if (batch_round == 1) {
      deal_cards(3,players[(dealer+1)%4]);
      deal_cards(2,players[(dealer+2)%4]);
      deal_cards(3,players[(dealer+3)%4]);
      deal_cards(2,players[dealer%4]);
    } else if (batch_round == 2) {
      deal_cards(2,players[(dealer+1)%4]);
      deal_cards(3,players[(dealer+2)%4]);
      deal_cards(2,players[(dealer+3)%4]);
      deal_cards(3,players[dealer%4]);
    }
  }
  void deal() {
    if (shuff) {
      shu();
    }
    pack.reset();
    batch(dealer,1);
    batch(dealer,2);
  }
  void make_trump() {
    bool ordered_up = false;
    int i = 1;
    mt_round = 1;
    while (ordered_up == false && i<=4 && mt_round <= 2) {
        ordered_up = players[(dealer+i)%4]->
        make_trump(upcard, false, mt_round, order_up_suit);
        if (ordered_up) {
          std::cout << players[(dealer+i)%4]->get_name() 
          << " orders up " << order_up_suit << std::endl;
          std::cout << std::endl;
          trump_maker = (dealer+i)%4;
          break;
        } else {
          std::cout << players[(dealer+i)%4]->get_name() << " passes" << std::endl;
        }
        i++;
        if (mt_round == 1 && i > 4) {
          mt_round = 2;
          i = 1;
        }
    }
    if (ordered_up&&mt_round==1) {
      players[dealer%4]->add_and_discard(upcard);
    }
  }
  std::vector<Card> play_hand(int leader) {
    std::vector<Card> cards;
    Card c1 = players[leader]->lead_card(order_up_suit);
    cards.push_back(c1);
    std::cout << c1.get_rank() << " of " << c1.get_suit() 
    << " led by " << players[leader]->get_name() << std::endl;
    Card c2 = players[(leader+1)%4]->play_card(c1, order_up_suit);
    std::cout << c2.get_rank() << " of " << c2.get_suit() 
    << " played by " << players[(leader+1)%4]->get_name() << std::endl;
    Card c3 = players[(leader+2)%4]->play_card(c1, order_up_suit);
    std::cout << c3.get_rank() << " of " << c3.get_suit() 
    << " played by " << players[(leader+2)%4]->get_name() << std::endl;
    Card c4 = players[(leader+3)%4]->play_card(c1, order_up_suit);
    std::cout << c4.get_rank() << " of " << c4.get_suit() 
    << " played by " << players[(leader+3)%4]->get_name() << std::endl;
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c4);
    return cards;
  }
  int take_trick(int leader=1, int hand = 0) {
      Card highest, c1, c2, c3, c4;
      int index = 0;
      std::vector<Card> cards;
      cards=play_hand((leader)%4);
      c1 = cards[0];
      c2 = cards[1];
      c3 = cards[2];
      c4 = cards[3];
      highest = c1;
      if (Card_less(highest,c2,c1,order_up_suit)) {
        highest = c2;
        index = 1;
      }
      if (Card_less(highest,c3,c1,order_up_suit)) {
        highest = c3;
        index = 2;
      }
      if (Card_less(highest,c4,c1,order_up_suit)) {
        highest = c4;
        index = 3;
      }
      int true_index = (index+leader)%4;
      points[true_index] += 1;
      std::cout << players[true_index]->get_name() << " takes the trick" << std::endl;
      std::cout << std::endl;
    return true_index;
  }
  void print_hand() {
    std::cout << "Hand " << hand << std::endl;
    std::cout << players[hand%4]->get_name() << " deals" << std::endl;
    upcard = pack.deal_one();
    std::cout << upcard.get_rank() << " of " << upcard.get_suit() 
    << " turned up"<< std::endl;
  }
  void print_euchred (int index) {
    std::cout << "euchred!" << std::endl;
    if (index == 1) {
      t1_point+=2;
      std::cout << players[index-1]->get_name() << " and " 
      << players[index+1]->get_name() 
      << " have " << t1_point << " points" << std::endl;
    } else {
      t2_point+=2;
      std::cout << players[index-2]->get_name() << " and " << players[index]->get_name() 
      << " have " << t1_point << " points" << std::endl;
      std::cout << players[index-1]->get_name() << " and " 
      << players[index+1]->get_name() 
      << " have " << t2_point << " points" << std::endl;
    }
  }
  void play_full() {
    points = {0, 0, 0, 0};
    deal();
    print_hand();
    make_trump();
    int next = take_trick((dealer+1)%4);
    for (int i = 0; i < 4; i++) {
      next = take_trick(next, i+1);
    }
    
    if (points[0]+points[2] > 2) {
      std::cout << players[0]->get_name() << " and " << players[2]->get_name()
      << " win the hand" << std::endl;
      if (trump_maker == 1||trump_maker == 3) {
        print_euchred(1);
      } else {
        if (points[0] + points[2] == 5) {
          t1_point+=2;
          std::cout << "march!" << std::endl;
          std::cout << players[0]->get_name() << " and " << players[2]->get_name() 
          << " have " << t1_point << " points" << std::endl;
        } else {
          t1_point+=1;
          std::cout << players[0]->get_name() << " and " << players[2]->get_name() 
          << " have " << t1_point << " points" << std::endl;
        }
      }
      std::cout << players[1]->get_name() << " and " << players[3]->get_name() 
      << " have " << t2_point << " points" << std::endl;
    } else {
      std::cout << players[1]->get_name() << " and " << players[3]->get_name()
      << " win the hand" << std::endl;
      if (trump_maker == 0||trump_maker == 2) {
        print_euchred(2);
      } else {
        if (points[1] + points[3] == 5) {
          t2_point+=2;
          std::cout << "march!" << std::endl;
          std::cout << players[0]->get_name() << " and " << players[2]->get_name() 
          << " have " << t1_point << " points" << std::endl;
          std::cout << players[1]->get_name() << " and " << players[3]->get_name() 
          << " have " << t2_point << " points" << std::endl;
        } else {
          t2_point+=1;
          std::cout << players[0]->get_name() << " and " << players[2]->get_name() 
          << " have " << t1_point << " points" << std::endl;
          std::cout << players[1]->get_name() << " and " << players[3]->get_name() 
          << " have " << t2_point << " points" << std::endl;
        }
      }
    }
    hand += 1;
    dealer+=1;
    upcard = pack.deal_one();
    std::cout << std::endl;
  }
  int check() {
    if (t1_point >= ptw) {
      return 1;
    } else if (t2_point >= ptw) {
      return 2;
    } else return 0;
  }
};

int main(int argc, char *argv[]) {
  std::string filename = argv[1];
  std::string shuffle = argv[2];
  std::string str_ptw = argv[3];
  int ptw = std::stoi(str_ptw);
  std::string name0 = argv[4];
  std::string type0 = argv[5];
  std::string name1 = argv[6];
  std::string type1 = argv[7];
  std::string name2 = argv[8];
  std::string type2 = argv[9];
  std::string name3 = argv[10];
  std::string type3 = argv[11];
  if (argc != 12 || ptw < 1 || ptw > 100 || 
  (shuffle != "shuffle" && shuffle != "noshuffle") || 
  (type0 != "Simple" && type0 != "Human") ||
  (type1 != "Simple" && type1 != "Human") ||
  (type2 != "Simple" && type2 != "Human") ||
  (type3 != "Simple" && type3 != "Human")) {
    std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
     return 1;
  }
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cout << "Error opening " << filename << std::endl;
    return 1;
  }
  Pack pack(fin);
  Player* p0 = Player_factory(name0, type0);
  Player* p1 = Player_factory(name1, type1);
  Player* p2 = Player_factory(name2, type2);
  Player* p3 = Player_factory(name3, type3);
  std::vector<Player*> players;
  players.push_back(p0);
  players.push_back(p1);
  players.push_back(p2);
  players.push_back(p3);
  // Read command line args and check for errors
  Game game(p0, p1, p2, p3);
  for (int i = 0; i < 12; i++) {
    std::cout << argv[i] << " ";
  }
  std::cout << std::endl;
  game.play(shuffle, ptw, pack);

  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
}