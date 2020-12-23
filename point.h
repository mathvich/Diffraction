#ifndef POINT_H
#define POINT_H

class point
{
public:
    double x,y,z;
    point(const double &_x=0, const double &_y=0, const double &_z=0);
    point operator+(const point &b);
    point operator-(const point &b);
    point operator*(const double &c);
    point operator*(const point &b);
    bool operator!=(const point& b);

    double module();
    double sqrmodule();
};

#endif
