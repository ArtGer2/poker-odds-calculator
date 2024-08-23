#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H


#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPixmap>

class DraggableLabel : public QWidget
{
    Q_OBJECT
public:
    QLabel *label;
    QLabel TextLabel;

    explicit DraggableLabel(QWidget *parent = nullptr);
    void SaveLastPosition();
    void restoreLastPosition();
signals:
    void textDelete(const QString& text);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    QWidget *lastParent;
    QPoint lastPosition;
    QSize lastSize;
};

#endif // DRAGGABLELABEL_H
