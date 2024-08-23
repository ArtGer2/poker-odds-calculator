#include "game.h"
#include <iostream>
#include <random>
#include <algorithm>
#include<QDebug>>
using namespace std;

class Deck {
public:
    std::vector<Card> cards;
    Deck() {
        for (int s = CLUBS; s <= SPADES; ++s) {
            for (int r = TWO; r <= ACE; ++r) {
                cards.emplace_back(static_cast<Rank>(r), static_cast<Suit>(s));
            }
        }
        shuffle();
    }

    void shuffle(){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card dealCard() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }


    std::vector<Card> dealCards(int n) {
        std::vector<Card> dealtCards;
        for (int i = 0; i < n; ++i) {
            dealtCards.push_back(dealCard());
        }
        return dealtCards;
    }


    void removeCard(const Card& card) {
        cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
    }
};

string Game::rankToString(Rank r) {
    switch (r) {
    case TWO: return "2";
    case THREE: return "3";
    case FOUR: return "4";
    case FIVE: return "5";
    case SIX: return "6";
    case SEVEN: return "7";
    case EIGHT: return "8";
    case NINE: return "9";
    case TEN: return "10";
    case JACK: return "J";
    case QUEEN: return "Q";
    case KING: return "K";
    case ACE: return "A";
    default: return "";
    }
}

string Game::suitToString(Suit s) {
    switch (s) {
    case HEARTS: return "Hearts";
    case DIAMONDS: return "Diamonds";
    case CLUBS: return "Clubs";
    case SPADES: return "Spades";
    default: return "";
    }
}



Game::Game(const std::vector<Card>& playerCards, const std::vector<Card>& tableCards)
    : PlayerCards(playerCards), TableCards(tableCards) {

}



std::pair<double, double> Game::calculateWinProbability(int numOpponents, int numSimulations) {


    int wins = 0;
    int ties = 0;
    Deck deck;




    for (int i = 0; i < numSimulations; ++i) {
        std::vector<Hand> opponentHands;
        std::vector<Card> takenCards;
        std::vector<Card> allCards = PlayerCards;
        std::vector<Card> CurTable= TableCards;


        std::vector<Card> TableFull;
        if(CurTable.size()<5){
            TableFull= deck.dealCards(5-CurTable.size());
            CurTable.insert(CurTable.end(),TableFull.begin(),TableFull.end());
            takenCards.insert(takenCards.end(),TableFull.begin(),TableFull.end());
        }

        allCards.insert(allCards.end(), CurTable.begin(), CurTable.end());
        for (const auto& card : allCards) {
            deck.removeCard(card);
        }


        Hand bestPlayerHand = Hand::findBestHand(allCards);


        for (int j = 0; j < numOpponents; ++j) {
            std::vector<Card> opponentCards = deck.dealCards(2);
            takenCards.insert(takenCards.end(),opponentCards.begin(),opponentCards.end());
            opponentCards.insert(opponentCards.end(), CurTable.begin(), CurTable.end());

            Hand opponentHand = Hand::findBestHand(opponentCards);
            opponentHands.push_back(opponentHand);
        }



        bool playerWins = true;
        bool tie = false;

        for (const auto& opponentHand : opponentHands) {
            if (opponentHand == bestPlayerHand) {
                tie = true ;
            }
            else {
                if (opponentHand > bestPlayerHand) {

                    playerWins = false;
                    break;
                }
            }
        }

        if (playerWins) {
            if (tie) {
                ties++;
            } else {
                wins++;
            }
        }

        for (auto cards: TableFull){
            CurTable.erase(std::remove( CurTable.begin(), CurTable.end(), cards),  CurTable.end());
        }
        for (auto cards: takenCards){
            deck.cards.push_back(cards);
        }
        deck.shuffle();

    }

    double winProbability = static_cast<double>(wins) / numSimulations;
    double tieProbability = static_cast<double>(ties) / numSimulations;


    return std::make_pair(winProbability, tieProbability);
}
