#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <QWidget>

class simplex : public QWidget
{
    Q_OBJECT
public:
    explicit simplex(QWidget *parent = 0);

signals:
    void wrongCheckSum();

public slots:

protected:
    void paintEvent(QPaintEvent * event);
};

#endif // SIMPLEX_H
