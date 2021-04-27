#ifndef CURVE3D_H
#define CURVE3D_H

#include <vector>
#include <QtMath>
#include "vector3d.hpp"
#include "matrix4x4.hpp"

class Curve3D
{
private:
    double const tn = 2 * M_PI * 4;

public:
    vector <Vector3D> points;
    vector <double> params;

    Matrix4x4 Scaling, RotationX, RotationY, Translation;

    Curve3D() {}
    Curve3D(int NumPoints, int NumParams)
    {
        points.resize(NumPoints);
        params.resize(NumParams);
    }

    Vector3D Curve1(double t)
    {
        double x = params[0] * cos(t);
        double y = params[1] * sin(t);
        double z = params[2] * t;
        return Vector3D(x, y, z);
    }
    Vector3D Curve2(double t)
    {
        double x = params[0] * sin(t);
        double y = params[1] * t;
        double z = cos(sqrt(x * x + y * y));
        return Vector3D(x, y, z);
    }

    void SetScaling(double a, double b)
    {
        Scaling = Matrix4x4::Scale2D(a, b);
    }
    void SetRotationX(double phi)
    {
        RotationX = Matrix4x4::RotateX(phi);
    }
    void SetRotationY(double psi)
    {
        RotationY = Matrix4x4::RotateY(psi);
    }
    void SetTranslation(double l, double u, double n)
    {
        Translation = Matrix4x4::Translate(l, u, n);
    }
    Matrix4x4 GetResultMatrix()
    {
        return Scaling * RotationX * RotationY * Translation;
    }

    void FillVector(int CurveID)
    {
        double dt = tn / points.size();
        for (uint i = 0; i < points.size(); ++i)
        {
            double t = dt * i;
            points[i] = CurveID ? Curve2(t) : Curve1(t);
            points[i] = points[i] * GetResultMatrix();
        }
    }
    void SetDefaultParams(int CurveID)
    {
        if (CurveID == 0)
        {
            params[0] = params[1] = 50;
            params[2] = 10;
        }
        if (CurveID == 1) params[0] = params[1] = 10;
    }
};

#endif // CURVE3D_H
