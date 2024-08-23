#include "hand.h"
#include <algorithm>
#include <map>

Hand::Hand(std::vector<Card> c) : cards(c) {
    std::sort(cards.begin(), cards.end());
}

Hand::HandRank Hand::evaluate() const {
    if (isStraightFlush()) return STRAIGHT_FLUSH;
    if (isFourOfAKind()) return FOUR_OF_A_KIND;
    if (isFullHouse()) return FULL_HOUSE;
    if (isFlush()) return FLUSH;
    if (isStraight()) return STRAIGHT;
    if (isThreeOfAKind()) return THREE_OF_A_KIND;
    if (isTwoPair()) return TWO_PAIR;
    if (isPair()) return PAIR;
    return HIGH_CARD;
}
bool Hand::operator<(const Hand& other) const {
    HandRank thisRank = evaluate();
    HandRank otherRank = other.evaluate();
    if (thisRank != otherRank) {
        return thisRank < otherRank;
    } else {
        return compareSameRank(other);
    }
}

bool Hand::operator >(const Hand& other) const {
    HandRank thisRank = evaluate();
    HandRank otherRank = other.evaluate();
    if (thisRank != otherRank) {
        return thisRank > otherRank;
    } else {
        return !compareSameRank(other);
    }
}


bool Hand::operator==(const Hand& other) const {
    HandRank thisRank = evaluate();
    HandRank otherRank = other.evaluate();

    if (thisRank != otherRank) {
        return false;
    }


    return !compareSameRank(other) && !other.compareSameRank(*this);
}

Hand Hand::findBestHand(const std::vector<Card>& cards) {
    size_t n = cards.size();

    Hand bestHand({cards[0], cards[1], cards[2], cards[3], cards[4]});


    std::vector<int> indices(n, 0);
    std::fill(indices.begin(), indices.begin() + 5, 1);

    do {
        std::vector<Card> currentCombination;
        for (size_t i = 0; i < n; ++i) {
            if (indices[i] == 1) {
                currentCombination.push_back(cards[i]);
            }
        }

        Hand currentHand(currentCombination);

        if (bestHand < currentHand) {
            bestHand = currentHand;
        }
    } while (std::prev_permutation(indices.begin(), indices.end()));

    return bestHand;
}



bool Hand::isStraightFlush() const {
    return isFlush() && isStraight();
}

bool Hand::isFourOfAKind() const {
    return hasNOfAKind(4);
}


bool Hand::isFullHouse() const {
    return hasNOfAKind(3) && hasNOfAKind(2);
}


bool Hand::isFlush() const {
    Suit firstSuit = cards[0].suit;
    return std::all_of(cards.begin(), cards.end(), [firstSuit](Card c) { return c.suit == firstSuit; });
}

bool Hand::isStraight() const {
    for (size_t i = 0; i < cards.size() - 1; ++i) {
        if (cards[i + 1].rank != cards[i].rank + 1) {
            return false;
        }
    }
    return true;
}


bool Hand::isThreeOfAKind() const {
    return hasNOfAKind(3);
}


bool Hand::isTwoPair() const {
    std::map<Rank, int> rankCounts;
    for (const auto& card : cards) {
        rankCounts[card.rank]++;
    }
    int pairCount = 0;
    for (const auto& entry : rankCounts) {
        if (entry.second == 2) pairCount++;
    }
    return pairCount == 2;
}

bool Hand::isPair() const {
    return hasNOfAKind(2);
}

bool Hand::hasNOfAKind(int n) const {
    std::map<Rank, int> rankCounts;
    for (const auto& card : cards) {
        rankCounts[card.rank]++;
    }
    for (const auto& entry : rankCounts) {
        if (entry.second == n) return true;
    }
    return false;
}
bool Hand::compareSameRank(const Hand& other) const {
    for (size_t i = 0; i < cards.size(); ++i) {
        if (cards[i].rank != other.cards[i].rank) {
            return cards[i].rank < other.cards[i].rank;
        }
    }
    return false;
}
