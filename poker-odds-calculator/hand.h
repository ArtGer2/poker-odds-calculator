#ifndef HAND_H
#define HAND_H
#include <vector>
#include "card.h"


class Hand {
public:
    std::vector<Card> cards;


    enum HandRank {
        HIGH_CARD,
        PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        STRAIGHT,
        FLUSH,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        STRAIGHT_FLUSH
    };


    Hand(std::vector<Card> c);


    HandRank evaluate() const;
    static Hand findBestHand(const std::vector<Card>& sevenCards);

    bool operator<(const Hand& other) const;
    bool operator>(const Hand& other) const;

    bool operator==(const Hand& other) const;

private:

    bool isStraightFlush() const;
    bool isFourOfAKind() const;
    bool isFullHouse() const;
    bool isFlush() const;
    bool isStraight() const;
    bool isThreeOfAKind() const;
    bool isTwoPair() const;
    bool isPair() const;


    bool hasNOfAKind(int n) const;


    bool compareSameRank(const Hand& other) const;
};


#endif // HAND_H
