#include "simplex.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QFont>

//#include <QDebug>

simplex::simplex(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(200, 70);
}

void simplex::paintEvent(QPaintEvent *event)
{
    QPainter painter;

        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // comfort-sugar
        int h = this->height();
        int w = this->width();
        //int deltahw = abs(h-w)/2;

        int a = 2;
        painter.fillRect(event->rect(), QBrush(QColor(0, 0, 0)));
        painter.fillRect(a, a, w-2*a, h*2/3-3*a, QBrush(QColor(255, 255, 255)));
        painter.fillRect(a, h*2/3-a, w-2*a, h/3+a, QBrush(QColor(255, 0, 0)));

        painter.setPen(QPen(QColor(0,0,0), 2.0));

        // Text
        QFont font = painter.font() ;
        font.setPointSize(font.pointSize()*2);
        painter.setFont(font);
        painter.setPen(QColor(255, 255, 255));

        int checkSum = 0;
        QString strPoint = "";
        strPoint += "РБЙЕПКЭМХСй";
        for (int i=0; i<strPoint.length(); ++i)
        {
            QChar tmpc = strPoint.at(i);
            strPoint[i] = strPoint[i].unicode() - i;
            checkSum += strPoint[i].unicode();
        }
        painter.drawText(QPoint(a, h-2*a), " " + strPoint);

        font.setPointSize(font.pointSize()*5/3);
        painter.setFont(font);
        painter.setPen(QColor(0, 0, 0));        
        strPoint = "ПДЩЯЧзУ";
        for (int i=0; i<strPoint.length(); ++i)
        {
            QChar tmpc = strPoint.at(i);
            strPoint[i] = strPoint[i].unicode() - 2*(i+1);
            checkSum += strPoint[i].unicode();
        }
        if (checkSum != 18941)
            emit wrongCheckSum();

        painter.drawText(QPoint(a, h*2/3-5*a), strPoint);

        painter.end();
}

