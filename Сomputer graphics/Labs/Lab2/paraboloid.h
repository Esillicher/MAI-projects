#ifndef PARABOLOID_H
#define PARABOLOID_H
#include "body.h"
#include "math.h"
struct Paraboloid: public Body
{
    float z = 20;
    float a = 2.;

    void calculate()
    {
       float steps = 10;

       float dz = z/steps;
       float r;
       float r_kr;
       float r_kr2;
       float da =0.2;
       for(float z_i = 0;z_i < z;z_i+=dz)
       {

           r = sqrt(z_i/a);
           float z_i2 = z_i + dz;
           float r2 = sqrt(z_i2/a);
           r_kr = sqrt((z-dz)/a);
           r_kr2 = sqrt (z/a);

           for (float phi = -M_PI ; phi < M_PI +da ; phi += da) {

                   faces_q.push_back(Quadrangle(QVector3D(r*cos(phi),r*sin(phi),z_i),QVector3D(r2*cos(phi),r2*sin(phi),z_i2),
                                                QVector3D(r2*cos(phi +da),r2*sin(phi+da),z_i2),QVector3D(r*cos(phi+da),r*sin(phi+da),z_i)));
                   faces.push_back(Triangle(QVector3D(0,0,z),QVector3D(r_kr2*cos(phi +da),r_kr2*sin(phi+da),z),
                                            QVector3D(r_kr2*cos(phi),r_kr2*sin(phi),z)));
           }

       }


    }
};

#endif // PARABOLOID_H
