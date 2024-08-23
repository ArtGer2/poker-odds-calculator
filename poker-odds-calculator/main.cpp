#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "droplabel.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // lang
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "card_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }



    MainWindow w;
    w.show();
    return a.exec();
}
// #include "game.h"
// #include <iostream>

// int main() {
//     std::vector<Card> playerCards = {Card(ACE, CLUBS), Card(ACE, HEARTS)};
//     std::vector<Card> tableCards = {
//         Card(QUEEN, SPADES), Card(JACK, SPADES), Card(TEN, SPADES), Card(TWO, SPADES), Card(THREE, SPADES)
//     };

//     Game game(playerCards, tableCards);
//     double winProbability = game.calculateWinProbability(2,1000);

//     std::cout << "Winning probability: " << winProbability * 100 << "%" << std::endl;

//     return 0;
// }
