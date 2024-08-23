#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cardchoise.h"
#include <QMainWindow>
#include <QFutureWatcher>
#include <QtConcurrent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    CardChoise *cards ;


public:
    void GameStart();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onTextDropped(DropLabel* source, const QString& text);
    void onCalculationFinished();
private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:

    Ui::MainWindow *ui;
    std::vector<QString> playerCards = {NULL,NULL};
    std::vector<QString> tableCards= {NULL,NULL,NULL,NULL,NULL};


    QFutureWatcher<void> futureWatcher;

};
#endif // MAINWINDOW_H
