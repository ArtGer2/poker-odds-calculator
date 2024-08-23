#include "card.h"

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

bool Card::operator<(const Card& other) const {
    return rank < other.rank;
}

bool Card::operator==(const Card& other) const {
    return rank == other.rank && suit == other.suit;
}
