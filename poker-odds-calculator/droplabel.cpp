#include "droplabel.h"
#include "draggablelabel.h"
#include <QDebug>

DropLabel::DropLabel(QWidget *parent): QWidget(parent) {
    setAcceptDrops(true);

    imageLabel = new QLabel(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    setLayout(layout);
}

void DropLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {
        event->acceptProposedAction();


    }
}
QString DropLabel::getCardText() const {
    return currentCardText;
}

void DropLabel::setCardText(const QString& text) {
    currentCardText = text;
}
void DropLabel::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-draggablewidget")) {

        QByteArray data = event->mimeData()->data("application/x-draggablewidget");
        QDataStream stream(&data, QIODevice::ReadOnly);
        quintptr ptr;
        stream >> ptr;
        draggedWidget = reinterpret_cast<DraggableLabel*>(ptr);
         connect(draggedWidget, &DraggableLabel::textDelete, this, &DropLabel::onTextDelete);

        setCardText(draggedWidget->TextLabel.text());
        emit textDropped(this,currentCardText);

        QList<DraggableLabel*> existingWidgets = findChildren<DraggableLabel*>();
        if (!existingWidgets.isEmpty()) {
            // Возвращаем старый виджет на его исходное место
            existingWidgets.first()->restoreLastPosition();

        }
        // Получаем текст из перетаскиваемого виджета




        draggedWidget->setParent(this);
        draggedWidget->show();

        event->acceptProposedAction();

    }

}
void DropLabel::onTextDelete(const QString& text){
    this->setCardText("");
    emit textDropped(this,currentCardText);
}
