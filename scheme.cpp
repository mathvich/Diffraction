#include "scheme.h"
#include <QPaintEvent>

//#include <QDebug>

schemeWidget::schemeWidget(QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(296, 243);
    Rainbow = NULL;
}

void schemeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), QBrush(QColor(0, 0, 0)));

    // comfort-sugar
    int h = this->height();
    int w = this->width();

    if (1)
    {
        if (Rainbow)
        {
            const double a=0.2;//*(1.0-Rainbow->h);
            double d = 0.4*Rainbow->Period/100.0;
            if (d > 0.4)
                d = 0.4;
            double z = 0.005+0.05*Rainbow->HoleWidth/30.0;

            painter.setPen(QColor(255, 255, 255));

            // holes screen
            painter.drawLine(0, a*h, w, a*h);
            painter.drawLine(0, a*h+1, w, a*h+1);

            // image screen
            painter.drawLine(0, (1.0-a)*h, w, (1.0-a)*h);
            painter.drawLine(0, (1.0-a)*h+1, w, (1.0-a)*h+1);

            // left hole
            if (Rainbow->LeftHole)
                painter.fillRect((0.5-d)*w - z*w/2.0, (1.0-a)*h-1, z*w, 5, QColor(0,0,0));
            // right hole
            if (Rainbow->RightHole)
                painter.fillRect((0.5+d)*w - z*w/2.0, (1.0-a)*h-1, z*w, 5, QColor(0,0,0));

            painter.setPen(QColor(255, 255, 255));
            painter.drawText(w/3.5, (a+0.1)*h, "Экран для наблюдения");
            painter.drawText(w/3.75, (a+0.2)*h, "дифракционной картины");
            painter.drawText(w/2.55, (1-a-0.05)*h, "Отверстия");

            //qDebug() << "replotting scheme";
        }
    }

    painter.end();
}
