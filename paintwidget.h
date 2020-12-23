#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include "rainbow.h"

class paintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit paintWidget(QWidget *parent = 0);
    rainbow *Rainbow;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent * event);
};

#endif // PAINTWIDGET_H
