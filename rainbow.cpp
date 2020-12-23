#include "rainbow.h"
#include <math.h>

//#include <QDebug>

rainbow::rainbow(QWidget *parent) : QWidget(parent)
{    
    ReplotTimer = new QTimer;
    ReplotTimer->setInterval(250);
    connect(ReplotTimer, SIGNAL(timeout()), this, SLOT(timer()));



    LeftHole = false;
    RightHole = false;

    h = 800.0 * 1e+3; // grid to screen distance
    Precision = 500;
    boxSize = 100.0*1e+3;
    Dots = 1;
    Period = 10.0;
    Color = 2.0*3.14159265*10.0;
    HoleWidth = 1.0;
    for (int i=0; i<2018; i++)
        Intensities[i] = 1.0;

    PlotWidget = new plotWidget;
    PlotWidget->xAxis->setLabel("Координата, мм");
    PlotWidget->yAxis->setLabel("Интенсивность света, ед.");
    PlotWidget->addGraph(PlotWidget->xAxis, PlotWidget->yAxis);
    PlotWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //PlotWidget->setMinimumSize(600, 400);
    PlotWidget->graph(0)->setPen(QPen(QColor(0, 110, 40), 2));
    PlotWidget->graph(0)->setName("Интенсивность");
    PlotWidget->Arr = Intensities;
    PlotWidget->Prec = &Precision;
    PlotWidget->Color = &this->Color;

    connect(PlotWidget, SIGNAL(wheelRotated(int)), this, SLOT(handleZoom(int)));

    //buildPlot();
}

void rainbow::timer()
{
    PlotWidget->graph(0)->data()->clear();

    //qDebug() << boxSize;
    double x = -boxSize;
    double dx = 2.0*boxSize/Precision;
    yMax = 0.0;
    double y0Max = 0.0;
    double y0Min = 1.0;

    int index=0;
    while (x < boxSize)
    {
        double y0 = getIntensity(x);
        double y = log(1e+9*y0 + 2.718281828459046) - 1.0;
        Intensities[1+index++] = y;
        PlotWidget->graph(0)->addData(x*1e-3, y0);
        //qDebug() << x << y;
        if (y>yMax)
            yMax = y;

        if (y0>y0Max)
            y0Max = y0;

        if (y0<y0Min)
            y0Min = y0;
        x += dx;
        //qDebug() << index;
    }

    if (fabs(y0Max) < 1e-15)
        yMax = 1.0;
    Intensities[0] = yMax;

    //Intensities[501] = 0;

    PlotWidget->xAxis->setRange(-boxSize*1e-3, boxSize*1e-3);
    PlotWidget->yAxis->setRange(-y0Max*0.01, y0Max*1.2);

    PlotWidget->replot();
    //qDebug() << "pl";
    ReplotTimer->stop();
}

void rainbow::handleZoom(int delta)
{
    if (delta > 0)
        boxSize /= 1.1;
    else
        boxSize *= 1.1;
    buildPlot();
}

double rainbow::getIntensity(double y)
{
    Period = *period;
    const double xMax = HoleWidth; //width
    const double dx = xMax/500.0;
    double k = 2.0*3.14159262 / (Color * 1e-3);

    //h = 800.0 * 1e+3; // grid to screen distance
    //qDebug() << h << Period << HoleWidth;
    int sign = -1;          // auxilary variable
    double answRe = 0.0;     // integral intensity
    double answIm = 0.0;

    for (int i=1; i<=2; ++i)
    {
        int jndex = int(i/2)*sign;
        sign *= -1;

        if ((LeftHole) && (i == 1))
        {
            double x = -Period/2.0 - xMax/2.0;
            while (x < -Period/2.0 + xMax/2.0)
            {
                double tmp = sqrt(h*h + (y-x)*(y-x));
                answRe += dx*cos(k*tmp)/tmp;
                answIm += dx*sin(k*tmp)/tmp;
                x += dx;
            }
        }

        if ((RightHole) && (i == 2))
        {
            double x = Period/2.0 - xMax/2.0;
            while (x < Period/2.0 + xMax/2.0)
            {
                double tmp = sqrt(h*h + (y-x)*(y-x));
                answRe += dx*cos(k*tmp)/tmp;
                answIm += dx*sin(k*tmp)/tmp;
                x += dx;
            }
        }
    }

    //qDebug() << Color << h << Period << HoleWidth;

    return (answRe*answRe + answIm*answIm)/(Color*Color/1e+6);
    //return log(1e+9*(answRe*answRe + answIm*answIm)/(Color*Color/1e+6)+ 3);
}

void rainbow::buildPlot()
{
    ReplotTimer->start(200);
}

void rainbow::mouseMoveEvent(QMouseEvent *event)
{
    P = event->pos();
    this->update();
}

void rainbow::setDots(int _Dots)
{
    Dots = _Dots;
}

void rainbow::setPeriod(int _Period)
{
    //if (_Period < 120000)
        //Period = _Period/1000.0;
}

void rainbow::setHoleWidth(int _HoleWidth)
{
    HoleWidth = _HoleWidth/1000.0;
}

void rainbow::setPrecision(int _N)
{
    Precision = _N;
}

void rainbow::setColor(int _Color)
{
    //Color = 2.0*3.14159265*10.0*2.0*_Color/1000.0;
    Color = 6.0*140000.0/(1200.0+_Color);
    //qDebug() << 6.0*140000.0/(1200.0+_Color) << Color;
}

void rainbow::setLeftHoleEnable(bool state)
{
    LeftHole = state;
}

void rainbow::setRightHoleEnable(bool state)
{
    RightHole = state;
}
