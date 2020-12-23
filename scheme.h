#ifndef schemeWidget_H
#define schemeWidget_H

#include <QWidget>
#include <QPainter>
#include "rainbow.h"

class schemeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit schemeWidget(QWidget *parent = 0);
    rainbow *Rainbow;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent * event);
};

#endif // schemeWidget_H
