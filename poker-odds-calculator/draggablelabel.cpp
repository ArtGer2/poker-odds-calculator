#include "draggablelabel.h"


DraggableLabel::DraggableLabel(QWidget *parent) : QWidget(parent), lastParent(nullptr), lastPosition(QPoint()) {
    label = new QLabel(this);
}

void DraggableLabel::SaveLastPosition(){
    lastParent = parentWidget();
    lastPosition = pos();
}
void DraggableLabel::restoreLastPosition() {
    if (lastParent) {
        setParent(lastParent);
        move(lastPosition);
        show();
    }
}

void DraggableLabel::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        // Начало перетаскивания
        emit textDelete(this->label->text());
        restoreLastPosition();
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        // Установите необходимые данные в mimeData


        // Упаковываем указатель на виджет в MIME данные
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << (quintptr)this;
        mimeData->setData("application/x-draggablewidget", data);



        // Задайте изображение для перетаскивания
        drag->setMimeData(mimeData);
        drag->setPixmap(this->grab());

        // Выполните перетаскивание
        drag->exec(Qt::MoveAction);
    }
}

void DraggableLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit textDelete(this->label->text());
        restoreLastPosition();
    }
}
