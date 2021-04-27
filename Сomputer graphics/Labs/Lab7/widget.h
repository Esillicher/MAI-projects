#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPointF>

#include <vector>
#include "bezier-spline.hpp"
#include "lagrange-curve.hpp"
#include "b-spline.hpp"

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mousePressEvent(QMouseEvent *e);

private slots:
    void on_SelectAlgorithm_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    vector<QPointF> AnchorPoints;
    vector<QPointF> CurvePoints;
    BezierSpline bezier;
    LagrangeSpline lagrange;
    BSpline bspline;

    void DrawAnchorPoints(QPainter& painter);
    void DrawCurve(QPainter& painter);
    void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
