#include "paintwidget.h"
#include <QPaintEvent>

#include <QDebug>

paintWidget::paintWidget(QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(400, 263);
    Rainbow = NULL;
}

void paintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), QBrush(QColor(0, 0, 0)));

    // comfort-sugar
    int h = this->height();
    int w = this->width();

    //painter.setPen(QColor(0, 0, 0));
    //painter.drawText(w/2.5, h/2.0, "СХЕМА ЦЕПИ");

    if (Rainbow)
    {
        for (int i=0; i<w; ++i)
        {
            double I = Rainbow->getIntensity(((i-w/2.0)/double(w/2.0))*Rainbow->boxSize);
            painter.setPen(QColor(int(I/Rainbow->yMax*254.0), 0, 0));
            painter.drawLine(i, 0, i, h);
        }
    }

    painter.end();
}
