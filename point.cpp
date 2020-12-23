#include "point.h"
#include <math.h>

double point::module()
{
    return sqrt(x*x + y*y + z*z);
}

double point::sqrmodule()
{
    return (x*x + y*y +z*z);
}

point::point(const double &_x, const double &_y, const double &_z):x(_x), y(_y), z(_z){}

point point::operator+(const point &b)
{
    return point(x + b.x, y + b.y, z + b.z);
}

point point::operator-(const point &b)
{
    return point(x - b.x, y - b.y, z - b.z);
}

point point::operator*(const double &c)
{
    return point(c*x, c*y, c*z);
}

point point::operator*(const point &b)
{
    point answ;
    answ.x = y*b.z - z*b.y;
    answ.y = b.x*z - b.z*x;
    answ.z = x*b.y - y*b.x;
    return answ;
}
