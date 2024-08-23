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

        emit textDelete(this->label->text());
        restoreLastPosition();
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;


        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << (quintptr)this;
        mimeData->setData("application/x-draggablewidget", data);



        drag->setMimeData(mimeData);
        drag->setPixmap(this->grab());

        drag->exec(Qt::MoveAction);
    }
}

void DraggableLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit textDelete(this->label->text());
        restoreLastPosition();
    }
}
