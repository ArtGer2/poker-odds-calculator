#include "card.h"

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

// Реализация оператора сравнения меньше для класса Card
bool Card::operator<(const Card& other) const {
    return rank < other.rank;
}

// Реализация оператора сравнения на равенство для класса Card
bool Card::operator==(const Card& other) const {
    return rank == other.rank && suit == other.suit;
}
