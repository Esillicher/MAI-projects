#ifndef N_PRIZM_H
#define N_PRIZM_H
#include "body.h"

struct N_prizm: public Body

{
    void calculate()
    {
        int n = 7;
        int level = 0;
        int level2 = 10;
        int r = 6;
        float da = 2.*M_PI/n;

        for (float phi = -M_PI ; phi < M_PI +da ; phi += da)
        {

            faces.push_back(Triangle(QVector3D(0,0,level),QVector3D(r*cos(phi+da),r*sin(phi+da),level),QVector3D(r*cos(phi),r*sin(phi),level)));
            faces.push_back(Triangle(QVector3D(0,0,level2),QVector3D(r*cos(phi),r*sin(phi),level2),QVector3D(r*cos(phi +da),r*sin(phi+da),level2)));
            faces.push_back(Triangle(QVector3D(r*cos(phi),r*sin(phi),level),QVector3D(r*cos(phi +da),r*sin(phi+da),level),QVector3D(r*cos(phi),r*sin(phi),level2)));
            faces.push_back(Triangle(QVector3D(r*cos(phi+da),r*sin(phi+da),level),QVector3D(r*cos(phi +da),r*sin(phi+da),level2),QVector3D(r*cos(phi),r*sin(phi),level2)));


        }
    }



};

#endif // N_PRIZM_H
