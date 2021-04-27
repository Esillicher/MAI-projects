#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QVector4D>
#include <QMatrix4x4>
#include <QVector3D>
#include <QMatrix3x3>
#include <QPointF>
#include <algorithm>
#include <cmath>
using std::max;

int steps = 30;
float resX = 1;
float resY = 1;
int check = 1;
int X = 100;
int Y = 200;
int Z = 300;
int Ired1 = 20;
int Ired2 = 90;
int Ired3 = 90;
int Igreen1 = 20;
int Igreen2 = 60;
int Igreen3 = 90;
int Iblue1 = 20;
int Iblue2 = 30;
int Iblue3 = 80;
int eli = 30; //коэффициент блеска, свойство материала
float m = 0.223; //шероховатость материала
QString sv = "Blinn-Fong";

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->StepsSlider->setValue(steps);
    ui->StepsSpinBox->setValue(steps);
    ui->LSourceSpinX->setValue(X);
    ui->LSourceSpinY->setValue(Y);
    ui->LSourceSpinZ->setValue(Z);
    ui->RedSlider1->setValue(Ired1);
    ui->RedSlider2->setValue(Ired2);
    ui->RedSlider3->setValue(Ired3);
    ui->GreenSlider1->setValue(Igreen1);
    ui->GreenSlider2->setValue(Igreen2);
    ui->GreenSlider3->setValue(Igreen3);
    ui->BlueSlider1->setValue(Iblue1);
    ui->BlueSlider2->setValue(Iblue2);
    ui->BlueSlider3->setValue(Iblue3);
    ui->CoeffSlider->setValue(eli);
}

Widget::~Widget()
{
    delete ui;
}

QVector3D crossProduct(QVector4D A, QVector4D B) //вектороное произведение
{
    return QVector3D::crossProduct(QVector3D(A), QVector3D(B));
}
float ColorOverflowControl(float c)
{
    c = c < 0 ? 0 : c;
    c = c > 255 ? 255 : c;
    return c;
}

float colorred (QVector3D N, QVector3D L,QVector3D V){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Ired1
            + Ired2*(max(0.0F,QVector3D::dotProduct(L,N)))
            + Ired3*pow(max(0.0F,QVector3D::dotProduct(N,(L+V).normalized())),eli);
    return diff;
}
float colorgreen(QVector3D N, QVector3D L,QVector3D V){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Igreen1+Igreen2*(max(0.0F,QVector3D::dotProduct(L,N)))
            +Igreen3*pow(max(0.0F,QVector3D::dotProduct(N,(L+V).normalized())),eli);
    return diff;
}
float colorblue(QVector3D N, QVector3D L,QVector3D V){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Iblue1+Iblue2*(max(0.0F,QVector3D::dotProduct(L,N)))
            +Iblue3*pow(max(0.0F,QVector3D::dotProduct(N,(L+V).normalized())),eli);
    return diff;
}

float CookTorrance(QVector3D N, QVector3D L, QVector3D V, float m)
{
    float HN = QVector3D::dotProduct((L+V).normalized(),N);
    float VN = QVector3D::dotProduct(V,N);
    float LN = QVector3D::dotProduct(L,N);
    float VH = QVector3D::dotProduct(V,(L+V).normalized());
    float G = fmin(1,fmin((2*HN*VN)/VH,(2*HN*LN)/VH));
    float F = 1/(1+VN);
    float Dd = exp((pow((HN),2)-1)/(pow(m,2)*(pow((HN),2)))) / (M_PI*pow(m,2)*(pow((HN),4)));

    return (F*G*Dd)/(VN*LN);
}

float K_colorred(QVector3D N, QVector3D L,QVector3D V, float m){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Ired1
            + Ired2*(max(0.0F,QVector3D::dotProduct(L,N)))
            + Ired3*max(0.0F,CookTorrance(N,L,V,m));
    return diff;
}
float K_colorgreen(QVector3D N, QVector3D L,QVector3D V, float m){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Igreen1+Igreen2*(max(0.0F,QVector3D::dotProduct(L,N)))
            +Igreen3*max(0.0F,CookTorrance(N,L,V,m));
    return diff;
}
float K_colorblue(QVector3D N, QVector3D L,QVector3D V, float m){
    L.normalize();
    N.normalize();
    V.normalize();
    float diff = Iblue1+Iblue2*(max(0.0F,QVector3D::dotProduct(L,N)))
            +Iblue3*max(0.0F,CookTorrance(N,L,V,m));
    return diff;
}

QVector4D getObjectPoint(float a, float b) {
    if(check == 1)
    {
        float D=0.5;
        float A=0.3;
        return QVector4D((D+A*cos(b))*cos(a),
                         (D+A*cos(b))*sin(a),
                         A*sin(b),
                         1);
    }
    else
        return QVector4D(cos(a)*cos(b),
                         sin(b),
                         sin(a)*cos(b),
                         1);

}

void Widget::paintEvent(QPaintEvent *)
{
    float resz = (resX+resY)/2;
    QPainter p(this);

    if(check == 1)
    {
        QVector<QVector4D> object;
        float da = M_PI  /steps;

        for (float a = -M_PI; a < M_PI ; a += da)
        {
            for (float b = -M_PI; b < M_PI; b += da)
            {
                float aa = a + da;
                float bb = b + da;
                object.push_back(getObjectPoint(a, b));
                object.push_back(getObjectPoint(aa, b));
                object.push_back(getObjectPoint(aa, bb));
                object.push_back(getObjectPoint(a, bb));
            }
        }
        QMatrix4x4 e(1,0,0,0,
                     0,1,0,0,
                     0,0,1,0,
                     0,0,0,1);
        float C, S;
        C = cos(alpha);
        S = sin(alpha);
        QMatrix4x4 rotate1(1,0,0,0,
                           0,C,-S,0,
                           0,S,C,0,
                           0,0,0,1);
        C = cos(beta);
        S = sin(beta);
        QMatrix4x4 rotate2(C,0,S,0,
                           0,1,0,0,
                           -S,0,C,0,
                           0,0,0,1);
        QMatrix4x4 translate(200,0,0,200,
                             0,200,0,200,
                             0,0,200,200,
                             0,0,0,1);
        QMatrix4x4 M = translate * rotate1 * rotate2;
        for (int i = 0; i < object.size(); i += 4)
        {
            QVector4D A,B,C,D;
            A = M * object[i + 0];
            B = M * object[i + 1];
            C = M * object[i + 2];
            D = M * object[i + 3];
            QVector3D Zrenie = QVector3D(0,74,760);

            QVector3D N = crossProduct(A-B, A-C);
            QVector3D L = QVector3D(X, Y, Z);

            if (N.z() > 0)
            {
                QPointF ff[4];
                ff[0] = QPointF(A.x()*resz, A.y()*resz);
                ff[1] = QPointF(B.x()*resz, B.y()*resz);
                ff[2] = QPointF(C.x()*resz, C.y()*resz);
                ff[3] = QPointF(D.x()*resz, D.y()*resz);
                float diff = 0;
                float diff1 = 0;float diff2 = 0;float diff3 =0;
                if(sv == "Blinn-Fong")
                {
                    diff1 = ColorOverflowControl(colorred(N,L,Zrenie));
                    diff2 = ColorOverflowControl(colorgreen(N,L,Zrenie));
                    diff3 = ColorOverflowControl(colorblue(N,L,Zrenie));
                }
                else
                {
                    diff1 = ColorOverflowControl(K_colorred(N,L,Zrenie,m));
                    diff2 = ColorOverflowControl(K_colorgreen(N,L,Zrenie,m));
                    diff3 = ColorOverflowControl(K_colorblue(N,L,Zrenie,m));
                }
                ColorOverflowControl(diff);

                p.setPen(Qt::NoPen);
                p.setBrush(QColor(diff1,diff2,diff3));
                p.drawConvexPolygon(ff, 4);
            }
        }
    }

    else
    {
        if(check == 2)
        {
            QVector<QVector4D> object;
            float da = M_PI  / steps;
            for (float a =-M_PI ; a < M_PI ; a += da)
            {
                for (float b = -M_PI/2; b < M_PI/2; b += da)
                {
                    float aa = a + da;
                    float bb = b + da;

                    object.push_back(getObjectPoint(a, b));
                    object.push_back(getObjectPoint(a, bb));
                    object.push_back(getObjectPoint(aa, b));
                    object.push_back(getObjectPoint(a, bb));
                    object.push_back(getObjectPoint(aa, bb));
                    object.push_back(getObjectPoint(aa, b));
                }
            }
            QMatrix4x4 e(1,0,0,0,
                         0,1,0,0,
                         0,0,1,0,
                         0,0,0,1);
            float C, S;
            C = cos(alpha);
            S = sin(alpha);
            QMatrix4x4 rotate1(1,0,0,0,
                               0,C,-S,0,
                               0,S,C,0,
                               0,0,0,1);
            C = cos(beta);
            S = sin(beta);
            QMatrix4x4 rotate2(C,0,S,0,
                               0,1,0,0,
                               -S,0,C,0,
                               0,0,0,1);
            QMatrix4x4 translate(200,0,0,200,
                                 0,200,0,200,
                                 0,0,200,200,
                                 0,0,0,1);
            QMatrix4x4 M = translate * rotate1 * rotate2;
            for (int i = 0; i < object.size(); i += 3)
            {
                QVector4D A,B,C,D;
                A = M * object[i + 0];
                B = M * object[i + 1];
                C = M * object[i + 2];
                //D = M * object[i + 3];

                QVector3D Zrenie = QVector3D(0,74,760);
                QVector3D N = crossProduct(A-B, A-C);
                QVector3D L = QVector3D(X, Y, Z);
                if (N.z() > 0)
                {
                    QPointF ff[3];
                    ff[0] = QPointF(A.x()*resz, A.y()*resz);
                    ff[1] = QPointF(B.x()*resz, B.y()*resz);
                    ff[2] = QPointF(C.x()*resz, C.y()*resz);
                    //                   ff[3] = QPointF(D.x()*resz, D.y()*resz);
                    float diff = 0;
                    float diff1 = 0;float diff2 = 0;float diff3 =0;
                    if(sv == "Blinn-Fong")
                    {
                        diff1 = ColorOverflowControl(colorred(N,L,Zrenie));
                        diff2 = ColorOverflowControl(colorgreen(N,L,Zrenie));
                        diff3 = ColorOverflowControl(colorblue(N,L,Zrenie));
                    }
                    else
                    {
                        diff1 = ColorOverflowControl(K_colorred(N,L,Zrenie,m));
                        diff2 = ColorOverflowControl(K_colorgreen(N,L,Zrenie,m));
                        diff3 = ColorOverflowControl(K_colorblue(N,L,Zrenie,m));
                    }
                    ColorOverflowControl(diff);

                    p.setPen(Qt::NoPen);
                    p.setBrush(QColor(diff1,diff2,diff3));
                    p.drawConvexPolygon(ff, 3);
                }
            }
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    alpha = e->y() *0.005;
    beta = e->x() *0.005;
    update();
}
void Widget::resizeEvent(QResizeEvent *event)
{
    resX = (float)event->size().width()/700;
    resY = (float)event->size().height()/500;
    update();
}

void Widget::on_Figure_currentIndexChanged(int index)
{
    check = index + 1;
    update();
}
void Widget::on_LightModel_currentTextChanged(const QString &arg)
{
    sv = arg;
    if (ui->LightModel->currentText() == "Blinn-Fong") ui->CoeffSlider->setValue(eli);
    else ui->CoeffSlider->setValue((int)(m*100));
    update();
}
void Widget::on_StepsSlider_valueChanged(int value)
{
    steps = value;
    update();
}
void Widget::on_StepsSpinBox_valueChanged(int arg)
{
    steps = arg;
    update();
}


void Widget::on_LSourceSpinX_valueChanged(int arg)
{
    X = arg;
    update();
}
void Widget::on_LSourceSpinY_valueChanged(int arg)
{
    Y = arg;
    update();
}
void Widget::on_LSourceSpinZ_valueChanged(int arg)
{
    Z = arg;
    update();
}


void Widget::on_RedSlider1_valueChanged(int value)
{
    Ired1 = value;
    update();
}
void Widget::on_RedSlider2_valueChanged(int value)
{
    Ired2 = value;
    update();
}
void Widget::on_RedSlider3_valueChanged(int value)
{
    Ired3 = value;
    update();
}
void Widget::on_GreenSlider1_valueChanged(int value)
{
    Igreen1 = value;
    update();
}
void Widget::on_GreenSlider2_valueChanged(int value)
{
    Igreen2 = value;
    update();
}
void Widget::on_GreenSlider3_valueChanged(int value)
{
    Igreen3 = value;
    update();
}
void Widget::on_BlueSlider1_valueChanged(int value)
{
    Iblue1 = value;
    update();
}
void Widget::on_BlueSlider2_valueChanged(int value)
{
    Iblue2 = value;
    update();
}
void Widget::on_BlueSlider3_valueChanged(int value)
{
    Iblue3 = value;
    update();
}
void Widget::on_CoeffSlider_valueChanged(int value)
{
    if (ui->LightModel->currentIndex() == 0) eli = value;
    if (ui->LightModel->currentIndex() == 1) m = value / 100.0;
    update();
}
