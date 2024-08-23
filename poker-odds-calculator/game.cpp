#include "game.h"
#include <iostream>
#include <random>
#include <algorithm>
#include<QDebug>>
using namespace std;

class Deck {
public:
    std::vector<Card> cards;  // Вектор, содержащий все карты в колоде

    // Конструктор Deck, инициализирующий колоду из 52 карт и перемешивающий её
    Deck() {
        for (int s = CLUBS; s <= SPADES; ++s) {
            for (int r = TWO; r <= ACE; ++r) {
                cards.emplace_back(static_cast<Rank>(r), static_cast<Suit>(s)); // Добавляем карту в колоду
            }
        }
        shuffle();  // Перемешиваем колоду
    }

    void shuffle(){
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    // Метод для выдачи одной карты из колоды
    Card dealCard() {
        Card card = cards.back();  // Берем последнюю карту из колоды
        cards.pop_back();  // Удаляем карту из колоды
        return card;  // Возвращаем карту
    }

    // Метод для выдачи нескольких карт из колоды
    std::vector<Card> dealCards(int n) {
        std::vector<Card> dealtCards;
        for (int i = 0; i < n; ++i) {
            dealtCards.push_back(dealCard());  // Добавляем карту в вектор
        }
        return dealtCards;  // Возвращаем вектор карт
    }

    // Метод для удаления карты из колоды (например, чтобы исключить карты, которые уже в игре)
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


    int wins = 0;  // Счетчик побед
    int ties = 0;  // Счетчик ничьих
    Deck deck;



    // Симуляция раздач
    for (int i = 0; i < numSimulations; ++i) {
        std::vector<Hand> opponentHands;
        std::vector<Card> takenCards;
        std::vector<Card> allCards = PlayerCards;  // Получаем карты игрока
        std::vector<Card> CurTable= TableCards;

         // Заполнение стола
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

        // Генерация возможных рук для каждого соперника
        for (int j = 0; j < numOpponents; ++j) {
            std::vector<Card> opponentCards = deck.dealCards(2);// Раздаем две карты сопернику
            takenCards.insert(takenCards.end(),opponentCards.begin(),opponentCards.end());
            opponentCards.insert(opponentCards.end(), CurTable.begin(), CurTable.end());  // Добавляем карты со стола

            Hand opponentHand = Hand::findBestHand(opponentCards);  // Определяем лучшую руку соперника с учетом карт на столе
            opponentHands.push_back(opponentHand);  // Сохраняем руку соперника
        }




        // Проверяем, выиграл ли игрок в данной симуляции
        bool playerWins = true;
        bool tie = false;

        for (const auto& opponentHand : opponentHands) {
            if (opponentHand == bestPlayerHand) {  // Если руки равны по силе
                tie = true ;
            }
            else {
                if (opponentHand > bestPlayerHand) {
                    // Если рука соперника сильнее
                    playerWins = false;
                    break;
                }
            }
        }

        if (playerWins) {
            if (tie) {
                ties++;  // Увеличиваем счетчик ничьих
            } else {
                wins++;  // Увеличиваем счетчик побед
            }
        }

        // Возврат к исхoдному состоянию
        for (auto cards: TableFull){
            CurTable.erase(std::remove( CurTable.begin(), CurTable.end(), cards),  CurTable.end());
        }
        for (auto cards: takenCards){
            deck.cards.push_back(cards);
        }
        deck.shuffle();

    }

    double winProbability = static_cast<double>(wins) / numSimulations;  // Вероятность победы
    double tieProbability = static_cast<double>(ties) / numSimulations;  // Вероятность ничьей
    //::cout << "Win probability: " << winProbability << std::endl;
    //std::cout << "Tie probability: " << tieProbability << std::endl;

    return std::make_pair(winProbability, tieProbability);  // Возвращаем суммарную вероятность победы или ничьей
}
