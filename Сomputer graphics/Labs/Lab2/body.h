#ifndef BODY_H
#define BODY_H

#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>
#include <QPainter>
#include <QtMath>

struct Triangle
{
    QVector3D a, b, c;
    Triangle(QVector3D a = QVector3D(), QVector3D b = QVector3D(), QVector3D c = QVector3D()): a(a), b(b), c(c){}

    QVector3D normal();
    bool isVisible();
};

struct Nprizm
{
    int n ; //задаваемый параметр
    int level; //координата z
    int r;
    QVector <QVector3D> N_prizm ;

    QVector<QVector3D> return_prizm()
        {
            return N_prizm;
        }

 void Nprizm_method(int n_v,int level_v,int r_v){
        n = n_v;
        level = level_v;
        r = r_v;
        float da = 2.*M_PI/n;

        for (float phi = -M_PI ; phi < M_PI +da ; phi += da) {


                QVector3D temp = QVector3D(r*cos(phi),r*sin(phi),level);
                N_prizm.push_back(temp);
        }
    }

    QVector3D normal();
    bool isVisible();
};

struct Quadrangle
{
    QVector3D e, b, c, d;
    Quadrangle(QVector3D e = QVector3D(), QVector3D b = QVector3D(), QVector3D c = QVector3D(), QVector3D d = QVector3D()): e(e), b(b), c(c), d(d){}

    QVector3D normal();
    bool isVisible();
};

Triangle operator*(QMatrix4x4 m, Triangle t);

 Quadrangle operator*(QMatrix4x4 m, Quadrangle q);

struct Body
{
    QVector<Triangle> faces;
    QVector<Quadrangle> faces_q;
    QVector<Nprizm> prizm;

    Body(){}
    virtual ~Body(){}

    virtual void calculate(){}
    void draw(QPainter *p);
};

Body operator*(QMatrix4x4 m, Body b);

#endif // BODY_H
