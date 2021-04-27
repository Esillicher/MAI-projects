#include "body.h"
#include <QDebug>
QVector3D Triangle::normal()
{
    return QVector3D::crossProduct((b - a), (c - a));
}

QVector3D Quadrangle::normal()
{
    return QVector3D::crossProduct((c - b), (d - b));
}

QVector3D Nprizm::normal()
{
    return QVector3D::crossProduct((N_prizm[1] - N_prizm[0]), (N_prizm[2] - N_prizm[0]));
}

bool Nprizm::isVisible(){
    if (this->normal().z()>0)
    {
        return true;
    }
    else return false;

}

bool Triangle::isVisible()
{
    if (this->normal().z()>0){
        return true;
    }
    else return false;

}

bool Quadrangle::isVisible()
{
    if (this->normal().z()>0){
        return true;
    }
    return false;
}

Triangle operator*(QMatrix4x4 m, Triangle t)
{
    return Triangle(m * t.a, m * t.b, m * t.c);
}

Quadrangle operator *(QMatrix4x4 m, Quadrangle q)
{
    return Quadrangle(m * q.c, m * q.b, m * q.c, m * q.d);
}

Nprizm operator *(QMatrix4x4 m, Nprizm pr)
{
    foreach (QVector3D prizmeach, pr.N_prizm) {
        pr.N_prizm.push_back(m * prizmeach);
    }
    return pr;
}

void Body::draw(QPainter *p)
{
    foreach(Triangle face, faces)
    {
        if(face.isVisible())
        {
            p->drawLine(face.a.toPointF(), face.b.toPointF());
            p->drawLine(face.b.toPointF(), face.c.toPointF());
            p->drawLine(face.c.toPointF(), face.a.toPointF());
        }
    }

    foreach (Quadrangle face_q, faces_q)
    {
        if(face_q.isVisible())
        {
            p->drawLine(face_q.b.toPointF(), face_q.e.toPointF());
            p->drawLine(face_q.e.toPointF(), face_q.d.toPointF());
            p->drawLine(face_q.d.toPointF(), face_q.c.toPointF());
            p->drawLine(face_q.c.toPointF(), face_q.b.toPointF());
        }
    }

    foreach(Nprizm prizmeach,prizm)
    {
        if(prizmeach.isVisible())
        {
            for(int i = 0;i < prizmeach.N_prizm.size() - 1;i++){
                p->drawLine(prizmeach.N_prizm[i].toPointF(),prizmeach.N_prizm[i+1].toPointF());

            }
        }
    }

}

Body operator*(QMatrix4x4 m, Body b)
{
    Body res;
    foreach(Triangle face, b.faces)
        res.faces.push_back(m * face);

    foreach (Quadrangle face_q, b.faces_q) {
        res.faces_q.push_back(m * face_q);
    }
    foreach (Nprizm prizmeach, b.prizm) {
        res.prizm.push_back(m * prizmeach);
    }
    return res;
}
