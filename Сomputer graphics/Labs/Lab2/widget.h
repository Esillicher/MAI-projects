#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QPointF>
#include <QVector>
#include <QtMath>

#include "tetraeder.hpp"
#include "piramid.h"
#include"n_prizm.h"
#include"paraboloid.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void scaleChanged(int);

private slots:
    void on_figureComboBox_currentIndexChanged(int index);

    void on_ZspinBox_valueChanged(int arg);

    void on_AspinBox_valueChanged(int arg);

private:
    Ui::Widget *ui;

    Tetraeder tetraeder;

    Piramid piramid;
    N_prizm prizm_main;
    Paraboloid paraboloid;

    int prev_mx, prev_my;
    double phi_x, phi_y;

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

    void ParaboloidRepaint();
};

#endif // WIDGET_H
