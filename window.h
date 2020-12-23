#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLayout>
#include <QSlider>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

#include "scheme.h"
#include "simplex.h"
#include "rainbow.h"
//#include "paintwidget.h"

class window : public QWidget
{
    Q_OBJECT

    QCheckBox *BoxLeft, *BoxRight;

    QVBoxLayout *MainLayout;
    QSlider *Dots;
    QLabel *DotsLabel;
    QSlider *Period;
    QLabel *PeriodLabel;
    QSlider *HoleWidth;
    QLabel *HoleWidthLabel;
    QSlider *Color;
    QLabel *ColorLabel;
    //QSlider *Scale;
    QLabel *DistanceLabel;
    QComboBox *BoxPeriodMult;
    double period;
    QSlider *Precision;
    QLabel *PrecisionLabel;

    schemeWidget *scheme;
    simplex *Simplex;
    rainbow *Rainbow;
    //paintWidget *PaintWidget;
    QLabel *spacer;
    QTimer *TimerReplot;
    QPushButton *plotButton;

    void initControls();

signals:


public:
    window(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    ~window();

public slots:
    void updateControls();
    void updatePlots();
};

#endif // WINDOW_H
