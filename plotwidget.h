#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <qcustomplot.h>
//#include <QObject>

class plotWidget : public QCustomPlot
{
    Q_OBJECT

public:
    double xCross, yCross;
    QPoint Cross;
    plotWidget();
    double *Arr;
    int *Prec;
    double *Color;
    //QSize minimumSizeHint();
    //QSize sizeHint();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void paintEvent(QPaintEvent *event);

signals:
    void wheelRotated(int delta);
};

#endif // PLOTWIDGET_H
