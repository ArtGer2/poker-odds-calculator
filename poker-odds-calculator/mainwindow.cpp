#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "draggablelabel.h"
#include "game.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->cards = new CardChoise();

    connect(ui->PlayerLabel1, &DropLabel::textDropped, this, &MainWindow::onTextDropped);
    connect(ui->PlayerLabel2, &DropLabel::textDropped, this, &MainWindow::onTextDropped);

    connect(ui->TableLabel1, &DropLabel::textDropped, this, &MainWindow::onTextDropped);
    connect(ui->TableLabel2, &DropLabel::textDropped, this, &MainWindow::onTextDropped);
    connect(ui->TableLabel3, &DropLabel::textDropped, this, &MainWindow::onTextDropped);
    connect(ui->TableLabel4, &DropLabel::textDropped, this, &MainWindow::onTextDropped);
    connect(ui->TableLabel5, &DropLabel::textDropped, this, &MainWindow::onTextDropped);

    connect(&futureWatcher, &QFutureWatcher<void>::finished, this, &MainWindow::onCalculationFinished);
}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onTextDropped(DropLabel* source, const QString& text) {


    if (source == ui->PlayerLabel1) {
        playerCards[0] = text;
    }
    else if (source == ui->PlayerLabel2) {
        playerCards[1] = text;
    }

    else if (source == ui->TableLabel1) {
        tableCards[0] = text;
    }
    else if (source == ui->TableLabel2) {
        tableCards[1] = text;
    }
    else if (source == ui->TableLabel3) {
        tableCards[2] = text;
    }
    else if (source == ui->TableLabel4) {
        tableCards[3] = text;
    }
    else if (source == ui->TableLabel5) {
        tableCards[4] = text;
    }


    GameStart();
}

Card parseCard(const QString& cardStr) {
    // Проверка длины строки
    if (cardStr.length() < 2) {
        throw std::invalid_argument("Invalid card string format");
    }

    // Извлечение ранга
    QString rankStr = cardStr.left(cardStr.length() - 1);
    QChar suitChar = cardStr.back();

    Rank rank;
    Suit suit;

    // Преобразование строки ранга в перечисление Rank
    if (rankStr == "2") rank = TWO;
    else if (rankStr == "3") rank = THREE;
    else if (rankStr == "4") rank = FOUR;
    else if (rankStr == "5") rank = FIVE;
    else if (rankStr == "6") rank = SIX;
    else if (rankStr == "7") rank = SEVEN;
    else if (rankStr == "8") rank = EIGHT;
    else if (rankStr == "9") rank = NINE;
    else if (rankStr == "10") rank = TEN;
    else if (rankStr == "J") rank = JACK;
    else if (rankStr == "Q") rank = QUEEN;
    else if (rankStr == "K") rank = KING;
    else if (rankStr == "A") rank = ACE;
    else throw std::invalid_argument("Invalid rank");

    // Преобразование символа масти в перечисление Suit
    if (suitChar == 'h') suit = HEARTS;
    else if (suitChar == 'd') suit = DIAMONDS;
    else if (suitChar == 'c') suit = CLUBS;
    else if (suitChar == 's') suit = SPADES;
    else throw std::invalid_argument("Invalid suit");

    return Card(rank, suit);
}

void MainWindow::GameStart(){
    ui->winLabel->setText("calculating");
    ui->TieLabel->setText("calculating");
    std::vector<Card> Player;
    std::vector<Card> Table;
    for (auto a: playerCards){
        if (a.size()>=2){
            Player.push_back(parseCard(a));
        }
    }
    for (auto a: tableCards){
        if (a.size()>=2){
            Table.push_back(parseCard(a));
        }
    }
    if(Player.size()==2 && Table.size() >=3){
        int numOpponents = ui->spinBox->value();  // Получаем значение из QSpinBox

        QFuture<void> future = QtConcurrent::run([Player, Table, numOpponents, this]() {
            try {
                Game game(Player, Table);  // Создание объекта game внутри лямбда-функции
                auto result = game.calculateWinProbability(numOpponents-1, 1000);  // Используем значение из QSpinBox
                ui->winLabel->setText(QString::number(result.first * 100, 'f', 2) + '%');  // Преобразуем double в QString и добавляем знак процента
                ui->TieLabel->setText(QString::number(result.second * 100, 'f', 2) + '%'); // Преобразуем double в QString и добавляем знак процента

            } catch (const std::exception &e) {
                qDebug() << "Exception caught:" << e.what();
            } catch (...) {
                qDebug() << "Unknown exception caught";
            }
        });

        futureWatcher.setFuture(future);
    }
    else{
        ui->winLabel->setText("not enough cards");
        ui->TieLabel->setText("not enough cards");
    }


}

void MainWindow::onCalculationFinished() {

}
void MainWindow::on_pushButton_clicked()
{

    cards->show();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    GameStart();
}

