#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include <QPointF>
#include "matrix4x4.hpp"

using std::vector;

class Vector3D
{
private:
    vector<double> coords;

public:
    Vector3D()
    {
        coords.resize(3);
    }
    Vector3D(double x, double y, double z)
    {
        coords.resize(3);
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }

    QPointF GetPointF()
    {
        return QPointF(coords[0], coords[1]);
    }

    Vector3D& operator =(const Vector3D& source)
    {
        this->coords[0] = source.coords[0];
        this->coords[1] = source.coords[1];
        this->coords[2] = source.coords[2];
        return *this;
    }
    Vector3D& operator *(Matrix4x4 m)
    {
        coords[0] = coords[0]*m.M[0][0] + coords[1]*m.M[1][0] + coords[2]*m.M[2][0] + m.M[3][0];
        coords[1] = coords[0]*m.M[0][1] + coords[1]*m.M[1][1] + coords[2]*m.M[2][1] + m.M[3][1];
        coords[2] = coords[0]*m.M[0][2] + coords[1]*m.M[1][2] + coords[2]*m.M[2][2] + m.M[3][2];

        double denom = coords[0]*m.M[0][3] + coords[1]*m.M[1][3] + coords[2]*m.M[2][3] + m.M[3][3];
        if (denom != 1.0)
        {
            coords[0] /= denom;
            coords[1] /= denom;
            coords[2] /= denom;
        }

        return *this;
    }
};

#endif // VECTOR3D_H
