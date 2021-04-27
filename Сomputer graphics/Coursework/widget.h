#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPointF>
#include <vector>
#include <cmath>

#include "segment.hpp"
#include "circle.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_StepSpinBox_valueChanged(int arg);
    void on_BaseLinesCheckBox_toggled();

private:
    Ui::Widget *ui;

    std::vector <Segment> Segments;
    std::vector <Circle> Circles;
    int step;
    QPoint startPoint, endPoint;
};

#endif // WIDGET_H
