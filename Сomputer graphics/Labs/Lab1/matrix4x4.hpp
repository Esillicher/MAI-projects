#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <vector>
#include <QtMath>

using std::vector;

class Matrix4x4
{
public:
    vector <vector<double>> M;

    Matrix4x4()
    {
        M.resize(4);
        for (int i = 0; i < 4; ++i)
        {
            M[i].resize(4);
            for (int j = 0; j < 4; ++j) M[i][j] = ((i == j) ? 1 : 0);
        }
    }
    Matrix4x4(double* a)
    {
        M.resize(4);
        for (int i = 0; i < 4; ++i)
        {
            M[i].resize(4);
            for (int j = 0; j < 4; ++j) M[i][j] = *(a + 4*i + j);
        }
    }

    Matrix4x4& operator =(const Matrix4x4 &N)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j) this->M[i][j] = N.M[i][j];
        }
        return *this;
    }
    friend Matrix4x4 operator *(const Matrix4x4& m1, const Matrix4x4& m2)
    {
        Matrix4x4 res;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                double sum = 0;
                for (int k = 0; k < 4; ++k) sum += m1.M[i][k] * m2.M[k][j];

                res.M[i][j] = sum;
            }
        }
        return res;
    }

    static Matrix4x4 Translate(double l, double u, double n)
    {
        double m[] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      l, u, n, 1};

        return Matrix4x4(m);
    }
    static Matrix4x4 Scale2D(double a, double b)
    {
        double m[] = {a, 0, 0, 0,
                      0, b, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};

        return Matrix4x4(m);
    }
    static Matrix4x4 RotateX(double phi)
    {
        double m[] = {1,    0,        0,      0,
                      0,  cos(phi), sin(phi), 0,
                      0, -sin(phi), cos(phi), 0,
                      0,    0,        0,      1};

        return Matrix4x4(m);
    }
    static Matrix4x4 RotateY(double psi)
    {
        double m[] = {cos(psi), 0, -sin(psi), 0,
                         0,     1,     0,     0,
                      sin(psi), 0,  cos(psi), 0,
                         0,     0,     0,     1};

        return Matrix4x4(m);
    }
    static Matrix4x4 RotateZ(double hi)
    {
        double m[] = { cos(hi), sin(hi),  0,   0,
                      -sin(hi), cos(hi),  0,   0,
                         0,       0,      1,   0,
                         0,       0,      0,   1};

        return Matrix4x4(m);
    }
};


#endif // MATRIX4X4_H
