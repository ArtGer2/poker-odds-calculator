#include "cardchoise.h"

CardChoise::CardChoise(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CardChoise)
{

    ui->setupUi(this);



    make_card_table();


}
void CardChoise::createCard(QGridLayout *gridLayout, int &row, int &column, const QString &cardText, const QString &imagePath) {
    DropLabel *drop = new DropLabel(this);

    DraggableLabel *draggableLabel = new DraggableLabel(drop);

    QSize initialSize(150, 225); // Пример размера, можно изменить в зависимости от потребностей
    draggableLabel->setFixedSize(initialSize);
    draggableLabel->label ->setFixedSize(initialSize);
    QPixmap pixmap(imagePath);
    draggableLabel->TextLabel.setText(cardText);
    draggableLabel->label->setPixmap(pixmap.scaled(draggableLabel->label->size()*0.9, Qt::KeepAspectRatio));


    draggableLabel->SaveLastPosition();

    gridLayout->addWidget(drop, row, column);

    column++;
    if (column == 12) {
        column = 0;
        row++;
    }
}

void CardChoise::make_card_table() {
    QGridLayout *gridLayout = new QGridLayout;
    ui->centralwidget->setLayout(gridLayout);

    int row = 0;
    int column = 0;

    // Карты от 2 до 9
    for (char num = '2'; num <= '9'; num++) {
        for (char suit : {'h', 'd', 'c', 's'}) {
            QString cardText = QString(QChar(num)) + QChar(suit);
            QString imagePath = QString(":/images/images/%1%2.png").arg(num).arg(suit);
            createCard(gridLayout, row, column, cardText, imagePath);
        }
    }

    // Карты 10, J, Q, K, A
    QStringList specialCards = {"10", "J", "Q", "K", "A"};
    for (const QString &card : specialCards) {
        for (char suit : {'h', 'd', 'c', 's'}) {
            QString cardText = card + QChar(suit);
            QString imagePath = QString(":/images/images/%1%2.png").arg(card).arg(suit);
            createCard(gridLayout, row, column, cardText, imagePath);
        }
    }

    // Задание фиксированного размера для ячеек
    for (int i = 0; i < 10; ++i) {
        gridLayout->setColumnMinimumWidth(i, 50); // Установите минимальную ширину для каждого столбца
        gridLayout->setRowMinimumHeight(i, 50);  // Установите минимальную высоту для каждой строки
    }
}


CardChoise::~CardChoise()
{
    delete ui;
}
