#ifndef CARD_H
#define CARD_H

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };


class Card {
public:
    Rank rank;
    Suit suit;

    // Конструктор карты
    Card(Rank r, Suit s);

    // Оператор сравнения меньше
    bool operator<(const Card& other) const;

    // Оператор сравнения на равенство
    bool operator==(const Card& other) const;
};


#endif // CARD_H
