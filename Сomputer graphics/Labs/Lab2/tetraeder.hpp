#ifndef TETRAEDER_HPP
#define TETRAEDER_HPP

#include "body.h"
struct Tetraeder: public Body
{
    void calculate()
    {

        QVector3D a(0, 0, 8), b(0, 6, 0), c(0, 0, 0), d(10, 0, 0);
        faces.push_back(Triangle(b, c, a));
        faces.push_back(Triangle(c, d, a));
        faces.push_back(Triangle(d, b, a));
        faces.push_back(Triangle(c, b, d));

    }
};

#endif // TETRAEDER_HPP
