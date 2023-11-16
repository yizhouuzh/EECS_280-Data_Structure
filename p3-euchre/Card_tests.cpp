// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_suit_and_rank) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(two_spades.get_suit(), Card::SUIT_SPADES);

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), Card::RANK_THREE);
    ASSERT_EQUAL(three_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(three_spades.get_suit(Card::SUIT_CLUBS), Card::SUIT_SPADES);
}

TEST(test_card_type) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(three_spades.is_trump(Card::SUIT_CLUBS));
}

TEST(test_card_self_comparison) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
}

TEST(test_Card_less_self) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(Card_less(three_spades, three_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(three_spades, three_spades, three_spades,
                           Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}
// Add more test cases here
TEST(test_card_1) {
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(ace_spades.get_rank(), Card::RANK_ACE);
    ASSERT_EQUAL(ace_spades.get_suit(), Card::SUIT_SPADES);
}

TEST(test_card_2) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_CLUBS),Card::SUIT_CLUBS);
}

TEST(test_card_3) {
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_FALSE(ten_spades.is_face_or_ace());
    ASSERT_TRUE(jack_spades.is_face_or_ace());
    ASSERT_TRUE(queen_spades.is_face_or_ace());
    ASSERT_TRUE(king_spades.is_face_or_ace());
    ASSERT_TRUE(ace_spades.is_face_or_ace());
}

TEST(test_card_4) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(jack_clubs.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_hearts.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_FALSE(ace_spades.is_left_bower(Card::SUIT_CLUBS));
}

TEST(test_card_5) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(ace_spades.is_trump(Card::SUIT_SPADES));
    ASSERT_FALSE(ace_spades.is_trump(Card::SUIT_CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(Card::SUIT_CLUBS));
}

TEST(test_operator_1) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(jack_spades<jack_clubs);
    ASSERT_FALSE(jack_clubs>=jack_diamonds);
    ASSERT_TRUE(jack_diamonds>jack_hearts);
    ASSERT_TRUE(jack_spades<jack_clubs);
    ASSERT_TRUE(jack_spades<=jack_spades);
    ASSERT_TRUE(jack_diamonds<ace_clubs);
    ASSERT_TRUE(jack_spades==jack_spades);

}

TEST(test_card_less_1) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ace_clubs, jack_hearts, Card::SUIT_HEARTS));
}

TEST(test_card_less_2) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card ten_spades = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card ten_clubs = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card ten_diamonds = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(jack_hearts, jack_diamonds, ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(ace_diamonds, jack_hearts, ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(jack_spades, ace_diamonds, ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(ace_clubs, jack_spades, ten_spades, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(ace_diamonds, jack_hearts, ten_hearts, Card::SUIT_DIAMONDS));
}
TEST_MAIN()
