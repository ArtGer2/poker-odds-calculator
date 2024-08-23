#ifndef GAME_H
#define GAME_H
#include <array>
#include "card.h"
#include "hand.h"
#include <iostream>
class Game
{
public:
    std::vector<Hand> Hands;
    std::vector<Card> PlayerCards;
    std::vector<Card> TableCards;

    Game(const std::vector<Card>& playerCards, const std::vector<Card>& tableCards);

    std::pair<double, double> calculateWinProbability( int numOpponents, int numSimulations = 10000);
    std::string rankToString(Rank r);
    std::string suitToString(Suit s);
};

#endif // GAME_H
