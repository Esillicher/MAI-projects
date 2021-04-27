#ifndef PIRAMID_H
#define PIRAMID_H

#include "body.h"

struct Piramid: public Body
{
    void calculate()
    {
        QVector3D b(0, 6, 0), c(0, 0, 0), d(10, 0, 0), e(10, 6, 0), a(5,3,10);
        faces.push_back(Triangle(b,e,d));
        faces.push_back(Triangle(d,c,b));
        faces.push_back(Triangle(b,c,a));
        faces.push_back(Triangle(c,d,a));
        faces.push_back(Triangle(d,e,a));
        faces.push_back(Triangle(e,b,a));
    }
};

#endif // PIRAMID_H
