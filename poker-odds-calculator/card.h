#ifndef CARD_H
#define CARD_H

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };


class Card {
public:
    Rank rank;
    Suit suit;


    Card(Rank r, Suit s);


    bool operator<(const Card& other) const;

    bool operator==(const Card& other) const;
};


#endif // CARD_H
