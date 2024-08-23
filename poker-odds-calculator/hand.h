#ifndef HAND_H
#define HAND_H
#include <vector>
#include "card.h"


class Hand {
public:
    std::vector<Card> cards;

    // Перечисление для ранжирования покерных комбинаций
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

    // Конструктор руки
    Hand(std::vector<Card> c);

    // Оценка руки (возвращает ранжирование покерной комбинации)
    HandRank evaluate() const;
    static Hand findBestHand(const std::vector<Card>& sevenCards);
    // Оператор сравнения меньше для рук
    bool operator<(const Hand& other) const;
    bool operator>(const Hand& other) const;

    bool operator==(const Hand& other) const;

private:
    // Проверки на различные покерные комбинации
    bool isStraightFlush() const;
    bool isFourOfAKind() const;
    bool isFullHouse() const;
    bool isFlush() const;
    bool isStraight() const;
    bool isThreeOfAKind() const;
    bool isTwoPair() const;
    bool isPair() const;

    // Вспомогательная функция для проверки N-карт одной масти
    bool hasNOfAKind(int n) const;

    // Сравнение рук с одинаковым рангом
    bool compareSameRank(const Hand& other) const;
};


#endif // HAND_H
