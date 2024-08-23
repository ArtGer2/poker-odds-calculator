#ifndef DROPLABEL_H
#define DROPLABEL_H
#include <QWidget>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QVBoxLayout>
#include <QApplication>
#include <QPoint>
#include <QPixmap>
#include "draggablelabel.h"
#include <QLayout>

class DropLabel : public QWidget
{
    Q_OBJECT
public:
    DraggableLabel *draggedWidget;
    explicit DropLabel(QWidget *parent = nullptr);
    QString getCardText() const;       // Возвращает текст карты
    void setCardText(const QString& text); // Устанавливает текст карты


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void textDropped(DropLabel* source, const QString& text);

public slots:
    void onTextDelete(const QString& text);

private:
    QLabel *imageLabel; // QLabel для отображения изображения
    QString currentCardText;

};

#endif // DROPLABEL_H
