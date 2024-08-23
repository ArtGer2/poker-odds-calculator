#ifndef CARDCHOISE_H
#define CARDCHOISE_H

#include <QDialog>
#include "ui_cardchoise.h"
#include "draggablelabel.h"
#include <QString>
#include <QMimeData>
#include <QGridLayout>
#include <QDebug>>
#include "droplabel.h"

namespace Ui {
class CardChoise;
}

class CardChoise : public QDialog
{
    Q_OBJECT

public:

    explicit CardChoise(QWidget *parent = nullptr);
    ~CardChoise();

private:
    Ui::CardChoise *ui;
    void createCard(QGridLayout *gridLayout, int &row, int &column, const QString &cardText, const QString &imagePath);
    void make_card_table();
};

#endif // CARDCHOISE_H
