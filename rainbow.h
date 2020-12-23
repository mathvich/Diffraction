#ifndef RAINBOW_H
#define RAINBOW_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QTimer>
#include "point.h"
#include "plotwidget.h"

class rainbow : public QWidget
{
    Q_OBJECT

public:
    double *period;
    QPoint P;
    int Dots;
    bool LeftHole, RightHole;
    double h;
    double yMax;
    double boxSize;    
    double Color, Period, HoleWidth;
    double Intensities[2018];
    int Precision;
    plotWidget *PlotWidget;

    QTimer *ReplotTimer;

    double getIntensity(double y);
    explicit rainbow(QWidget *parent = 0);    
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void setDots(int _Dots);
    void setColor(int _Period);
    void setPeriod(int _Color);
    void setHoleWidth(int _HoleWidth);
    void setLeftHoleEnable(bool state);
    void setRightHoleEnable(bool state);
    void setPrecision(int _N);
    void handleZoom(int delta);
    void buildPlot();
    void timer();
};

#endif // RAINBOW_H
