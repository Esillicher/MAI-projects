#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e) // обработка нажатий мыши
{
    if (ui->SelectAlgorithm->currentIndex() != 0) // если в ComboBox выбрано не "None"
    {
        if (e->button() == Qt::LeftButton) // если была нажата левая клавиша мыши
            AnchorPoints.push_back(QPointF(e->x(), e->y())); // вставляем координаты мыши в вектор опорных точек

        if (e->button() == Qt::RightButton && AnchorPoints.size() > 0) // если правая клавиша мыши
            AnchorPoints.pop_back(); // удаляем последнюю точку

        repaint();
    }
}

void Widget::DrawAnchorPoints(QPainter& painter) // отрисовка опорных точек
{
    if (ui->SelectAlgorithm->currentIndex() != 0) // если в ComboBox выбрано не "None"
    {
        painter.setPen(QColor(Qt::gray));

        for(uint i = 0; i < AnchorPoints.size(); ++i) // проходим по всем точкам
        {

            if (i > 0) painter.drawLine(AnchorPoints[i-1], AnchorPoints[i]); // для точек со второй по последнюю
            // соединяем линией текущую точку с предыдущей

            painter.drawEllipse(AnchorPoints[i], 2, 2); // выводим точку в виде эллипса с радиусом 2
        }
    }
}

void Widget::DrawCurve(QPainter& painter) // отрисовка кривой
{
    if (ui->SelectAlgorithm->currentIndex() != 0 &&
            CurvePoints.size() > 1) // если в ComboBox выбрано не "None" и точек больше одной
    {
        painter.setPen(QColor(Qt::red));

        for(uint i = 0; i < CurvePoints.size() - 1; ++i)
            // соединяем текущую (вплоть до предпоследней) со следующей
            painter.drawLine(CurvePoints[i], CurvePoints[i+1]);
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    DrawAnchorPoints(painter); // вызов отрисовки опорных точек (проверка внутри)

    if (AnchorPoints.size() > 1) // если опорных точек больше одной
    {
        switch (ui->SelectAlgorithm->currentIndex()) // смотрим, какой выбран алгоритм
        {
        case 0: break;
        // вызываем функцию от объекта соотв. класса для получения точек кривой
        case 1: CurvePoints = bezier.Calculate(AnchorPoints); break;
        case 2: CurvePoints = lagrange.Calculate(AnchorPoints); break;
        case 3: CurvePoints = bspline.Calculate(AnchorPoints); break;
        }

        DrawCurve(painter); // вызываем отрисовку кривой
    }
}

void Widget::on_SelectAlgorithm_currentIndexChanged(int index) // обработка смены пункта в ComboBox
{
    if (index == 0) AnchorPoints.clear(); // если переключились на None, очищаем опорные точки
    repaint();
}
