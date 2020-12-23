#include "plotwidget.h"
//#include <QPainter>

plotWidget::plotWidget()
{
    //this->setFixedWidth(500);
    xCross = 0.0;
    yCross = 0.0;    
}

/*
QSize plotWidget::minimumSizeHint()
{
    return QSize(600, 300);
}

QSize plotWidget::sizeHint()
{
    return QSize(700, 400);
}*/

void plotWidget::mousePressEvent(QMouseEvent *event)
{
    Cross = event->pos();
    xCross = xAxis->pixelToCoord(Cross.x());
    yCross = yAxis->pixelToCoord(Cross.y());

    //qDebug() << event->pos().x();
    /*
    if (event->buttons() & Qt::RightButton)
    {
        qDebug() << this->xAxis->pixelToCoord(event->pos().x());
    }
    */

    QCustomPlot::mousePressEvent(event);

    this->replot();
}

void plotWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePressEvent(event);
}

void plotWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    emit wheelRotated(delta);

    this->replot();
}

void plotWidget::paintEvent(QPaintEvent *event)
{
    QCustomPlot::paintEvent(event);    
    if (1)
    {
        QPainter painter;
        painter.begin(this);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setPen(QPen(QColor(255, 0, 0), 2));            
            painter.drawText(Cross+QPoint(20, 20), "X = " + QString::number(xCross, 'f', 2) + " мм     I * 10^10 = " + QString::number(yCross * 1e+10, 'f', 3) + " ед.");
            double crossSize = 15;
            //painter.drawLine(xCross-crossSize, yCross, xCross+crossSize, yCross);
            painter.drawLine(this->xAxis->coordToPixel(xCross)-crossSize,
                             this->yAxis->coordToPixel(yCross),
                             this->xAxis->coordToPixel(xCross)+crossSize,
                             this->yAxis->coordToPixel(yCross));
            painter.drawLine(this->xAxis->coordToPixel(xCross),
                             this->yAxis->coordToPixel(yCross)-crossSize,
                             this->xAxis->coordToPixel(xCross),
                             this->yAxis->coordToPixel(yCross)+crossSize);

            // comfort-sugar
            int h = 50;
            int xMin = this->xAxis->coordToPixel(this->xAxis->range().lower);
            int xMax = this->xAxis->coordToPixel(this->xAxis->range().upper);

            painter.fillRect(xMin, 0, xMax-xMin, h, QBrush(QColor(0, 0, 0)));
            //qDebug() << (*Color - 381.0)/320.0;
            for (int i=xMin; i<xMax; ++i)
            {
                double I = Arr[int(1 + double(i-xMin)/double(xMax-xMin)*double(*Prec * 0.9995)) % (*Prec)] / Arr[0];


                //painter.setPen(QColor(int(I*254.0), 0, 0));
                double R=I, G=I, B=I;
                double II = 1.0 - (*Color - 381.0)/320.0;

                if (II < 0.5)
                {
                    G = I*(II*2.0)*255.0;
                    R = I*(255.0-G);
                    B = 0.0;
                }
                else
                {
                    II -= 0.5;
                    R = 0.0;
                    B = I*II*2.0*255.0;
                    G = I*(255.0-B);
                }

                if (R>255)
                    R=255;
                if (G>255)
                    G=255;
                if (B>255)
                    B=255;

                painter.setPen(QColor(R, G, B));
                painter.drawLine(i, 0, i, h);
            }
        painter.end();
    }    
}
