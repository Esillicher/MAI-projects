#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

int sign(int x)
{
    return x > 0? 1 : x == 0? 0 : -1;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    phi_x = phi_y = 0;

    //tetraeder.calculate();
    piramid.calculate();

    connect(ui->scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::scaleChanged(int)
{
    repaint();
}

void Widget::paintEvent(QPaintEvent *)
{
    QMatrix4x4 m;
    m.translate(200, 200);
    m.rotate(phi_y, 1, 0, 0);
    m.rotate(phi_x, 0, 1, 0);
    m.scale(ui->scaleSlider->value() / 10.0);

    QPainter p(this);

    Body t = m * tetraeder;
    t.draw(&p);

    Body q = m * piramid;
    q.draw(&p);
    Body pr = m* prizm_main;
    pr.draw(&p);
    Body par = m*paraboloid;
    par.draw(&p);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    int mx = e->x(), my = e->y();
    phi_x += sign(mx - prev_mx), phi_y += sign(my - prev_my);

    prev_mx = mx, prev_my = my;
    repaint();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    prev_mx = e->x(), prev_my = e->y();
}

void Widget::on_figureComboBox_currentIndexChanged(int index)
{
    piramid.faces.clear();
    paraboloid.faces_q.clear();
    paraboloid.faces.clear();
    prizm_main.faces.clear();
    if (index == 0) piramid.calculate();
    if (index == 1) paraboloid.calculate();
    if (index == 2) prizm_main.calculate();
    repaint();
}

void Widget::ParaboloidRepaint()
{
    paraboloid.faces_q.clear();
    paraboloid.faces.clear();
    paraboloid.calculate();
    repaint();
}

void Widget::on_ZspinBox_valueChanged(int arg)
{
    paraboloid.z = arg;
    ParaboloidRepaint();
}

void Widget::on_AspinBox_valueChanged(int arg)
{
    paraboloid.a = arg;
    ParaboloidRepaint();
}
