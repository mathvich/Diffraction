#include "window.h"

#include <string.h>
#include <math.h>

//#include <QDebug>

void window::closeEvent(QCloseEvent *event)
{
    //event->ignore();
}

window::window(QWidget *parent)
    : QWidget(parent)
{
    period = 1.0;
    scheme = new schemeWidget();
    scheme->setFixedSize(296, 200);
    Simplex = new simplex;
    plotButton = new QPushButton("Показать график");
    BoxLeft = new QCheckBox("Левая щель");
    BoxRight = new QCheckBox("Правая щель");
    BoxPeriodMult = new QComboBox();
    BoxPeriodMult->addItem("1x");
    BoxPeriodMult->addItem("10x");
    BoxPeriodMult->addItem("100x");
    BoxPeriodMult->addItem("1000x");


    this->setWindowTitle("Научные Развлечения - Схема Юнга");
    initControls();

    MainLayout = new QVBoxLayout;

    QVBoxLayout *controlsLayout = new QVBoxLayout;
    QHBoxLayout *dotsAndLogo = new QHBoxLayout;
    QHBoxLayout *tmpA = new QHBoxLayout;
    QHBoxLayout *tmpB = new QHBoxLayout;
    QVBoxLayout *tmpC = new QVBoxLayout;
    QHBoxLayout *tmpD = new QHBoxLayout;
    QHBoxLayout *tmpE = new QHBoxLayout;
    QHBoxLayout *tmpF = new QHBoxLayout;
    //QHBoxLayout *tmpG = new QHBoxLayout;

    int LabelWidth = 290;
    DotsLabel->setFixedWidth(LabelWidth);
    PrecisionLabel->setFixedWidth(LabelWidth);
    PeriodLabel->setFixedWidth(LabelWidth);
    HoleWidthLabel->setFixedWidth(LabelWidth);
    ColorLabel->setFixedWidth(LabelWidth);

    spacer = new QLabel(" ");
    spacer->setFixedWidth(70);

    //controlsLayout->addWidget(get);
    //tmpA->addWidget(DotsLabel);
    //tmpA->addWidget(Dots);
    //tmpA->addWidget(BoxLeft);
    //tmpA->addWidget(BoxRight);
    tmpB->addWidget(PrecisionLabel);
    tmpB->addWidget(Precision);
    tmpD->addWidget(PeriodLabel);
    tmpD->addWidget(BoxPeriodMult);
    tmpD->addWidget(Period);
    tmpE->addWidget(HoleWidthLabel);    
    tmpE->addWidget(HoleWidth);
    tmpF->addWidget(ColorLabel);
    tmpF->addWidget(Color);
    //tmpG->addWidget(DistanceLabel);

    //tmpC->addLayout(tmpA);
    tmpC->addWidget(BoxLeft);
    tmpC->addWidget(BoxRight);
    tmpC->addWidget(DistanceLabel);
    tmpC->addLayout(tmpE);
    tmpC->addLayout(tmpD);
    tmpC->addLayout(tmpF);
    tmpC->addLayout(tmpB);
    tmpC->addWidget(spacer);
    //tmpC->addWidget(DistanceLabel);
    dotsAndLogo->addLayout(tmpC);
    //dotsAndLogo->addWidget(scheme);

    //DistanceLabel->setMaximumHeight(100);

    controlsLayout->addLayout(dotsAndLogo);
    //controlsLayout->addWidget(PeriodLabel);
    //controlsLayout->addWidget(Period);
    //controlsLayout->addWidget(HoleWidthLabel);
    //controlsLayout->addWidget(HoleWidth);
    //controlsLayout->addWidget(ColorLabel);
    //controlsLayout->addWidget(Color);
    //controlsLayout->addWidget(DistanceLabel);
    controlsLayout->addWidget(Rainbow->PlotWidget);

    QHBoxLayout *screenLayout = new QHBoxLayout;    
    //screenLayout->addWidget(spacer);
    //screenLayout->addWidget(PaintWidget);
    controlsLayout->addLayout(screenLayout);

    MainLayout->addLayout(controlsLayout);
    //MainLayout->addWidget(plotButton);

    connect(plotButton, SIGNAL(clicked(bool)), Rainbow, SLOT(buildPlot()));
    connect(Precision, SIGNAL(valueChanged(int)), Rainbow, SLOT(setPrecision(int)));
    connect(Precision, SIGNAL(valueChanged(int)), Rainbow, SLOT(buildPlot()));
    connect(Dots, SIGNAL(valueChanged(int)), Rainbow, SLOT(setDots(int)));
    connect(Dots, SIGNAL(valueChanged(int)), Rainbow, SLOT(buildPlot()));
    connect(Period, SIGNAL(valueChanged(int)), Rainbow, SLOT(setPeriod(int)));
    connect(Period, SIGNAL(valueChanged(int)), Rainbow, SLOT(buildPlot()));
    connect(HoleWidth, SIGNAL(valueChanged(int)), Rainbow, SLOT(setHoleWidth(int)));
    connect(HoleWidth, SIGNAL(valueChanged(int)), Rainbow, SLOT(buildPlot()));
    connect(Color, SIGNAL(valueChanged(int)), Rainbow, SLOT(setColor(int)));
    connect(Color, SIGNAL(valueChanged(int)), Rainbow, SLOT(buildPlot()));
    connect(BoxLeft, SIGNAL(toggled(bool)), Rainbow, SLOT(setLeftHoleEnable(bool)));
    connect(BoxRight, SIGNAL(toggled(bool)), Rainbow, SLOT(setRightHoleEnable(bool)));
    connect(BoxLeft, SIGNAL(toggled(bool)), Rainbow, SLOT(buildPlot()));
    connect(BoxRight, SIGNAL(toggled(bool)), Rainbow, SLOT(buildPlot()));
    //connect(BoxPeriodMult, SIGNAL(currentIndexChanged()), this, SLOT(updateControls()));
    //connect(BoxPeriodMult, SIGNAL(currentIndexChanged()), this, SLOT(setPeriod()));
    //connect(BoxPeriodMult, SIGNAL(currentIndexChanged()), Rainbow, SLOT(buildPlot()));
    connect(BoxPeriodMult, SIGNAL(currentIndexChanged(int)), Rainbow, SLOT(buildPlot()));

    Rainbow->setDots(Dots->value());
    Rainbow->setPeriod(Period->value());
    Rainbow->setHoleWidth(HoleWidth->value());
    Rainbow->setColor(Color->value());
    scheme->Rainbow = Rainbow;

    //PaintWidget->setMinimumHeight(60);

    updateControls();
    Rainbow->buildPlot();

    //Applying Layout
    this->setLayout(MainLayout);

    TimerReplot = new QTimer();
    TimerReplot->setInterval(1000/60);
    connect(TimerReplot, SIGNAL(timeout()), this, SLOT(updatePlots()));
    TimerReplot->start();
    this->resize(800, 600);
}

window::~window()
{
}

void window::updateControls()
{
    char tmp[250];
    double val = Dots->value();
    sprintf(tmp, "%d", int(val));
    DotsLabel->setText("Число щелей N = " + QString(tmp) + " шт. : ");

    //val = Period->value()/1000.0;    
    double PM=1.0;
    switch (BoxPeriodMult->currentIndex())
    {
        case 1: PM = 10.0;
        break;
        case 2: PM = 100.0;
        break;
        case 3: PM = 1000.0;
        break;
    }
    period = PM * Period->value()/1000.0;
    val = period;
    sprintf(tmp, "%3.2f", val);
    PeriodLabel->setText("Расст. между центрами щелей D = " + QString(tmp) + " мкм : ");

    val = HoleWidth->value()/1000.0;
    if (val > period)
    {
            HoleWidth->setValue(PM*Period->value());
            val = HoleWidth->value()/1000.0;
    }
    sprintf(tmp, "%4.3f", val);
    HoleWidthLabel->setText("Ширина щели d = " + QString(tmp) + " мкм : ");

    val = 6.0*140000.0/(1200.0+Color->value());
    sprintf(tmp, "%3.0f", val);
    ColorLabel->setText("Длина волны падающего света (" + QString(tmp) + " нм) : ");

    val = Precision->value();
    sprintf(tmp, "%3.0f", val);
    PrecisionLabel->setText("Точек на графике (" + QString(tmp) + " шт.) : ");

    //FrequencyLabel->setText("Частота излучения (" + QString::number(Frequency->value()) + ") : ");
    //FrequencyRainbow->repaint();
}

void window::initControls()
{
    PrecisionLabel = new QLabel("Точность (точек на графике)");
    Precision = new QSlider(Qt::Horizontal);
    Precision->setRange(50, 2000);
    Precision->setValue(500);

    DotsLabel = new QLabel("Число щелей N");
    Dots = new QSlider(Qt::Horizontal);
    Dots->setMinimum(1);
    Dots->setMaximum(10);
    Dots->setValue(1);
    //Diameter->setMaximumWidth(500);
    //Diameter->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);


    PeriodLabel = new QLabel("Период решетки");
    Period = new QSlider(Qt::Horizontal);
    Period->setMinimum(1000);
    Period->setMaximum(120000);
    Period->setValue(80000);
    //Length->setMaximumWidth(500);

    HoleWidthLabel = new QLabel("Ширина отверстий");
    HoleWidth = new QSlider(Qt::Horizontal);
    HoleWidth->setMinimum(200);
    HoleWidth->setMaximum(40000);
    HoleWidth->setValue(20000);

    ColorLabel = new QLabel("Длина волны");
    Color = new QSlider(Qt::Horizontal);
    Color->setMinimum(1);
    Color->setMaximum(1000);
    Color->setValue(500);
    //Density->setMaximumWidth(500);

    DistanceLabel = new QLabel("Расстояние до экрана L = 800 мм");

    Rainbow = new rainbow;
    Rainbow->period = &period;
    Rainbow->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //Rainbow->setMaximumWidth(500);
    //Rainbow->setMinimumHeight(400);
    //Rainbow->setMinimumWidth(400);

    //PaintWidget = new paintWidget;
    //PaintWidget->Rainbow = Rainbow;
    //Rainbow->repaint();
    //Rainbow->update();
    updatePlots();
}

void window::updatePlots()
{        
    updateControls();

    this->update();
}

void window::keyPressEvent(QKeyEvent *event)
{    
    if (Qt::Key_Escape == event->key())
        this->close();
}
