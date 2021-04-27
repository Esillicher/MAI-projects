#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include "curvepainter.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    CurvePainter Painter;
    int CurveID;

    int PrevX, PrevY;
    double Phi, Psi;

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *e);

    void paintEvent(QPaintEvent *);
    void SetLabelsAndBoxesHidden(bool arg);
    void GetCurveParams(int CurveID);

private slots:
    void on_CurveComboBox_currentTextChanged(const QString &arg);
    void on_StepIntSpinBox_valueChanged(int arg);
    void on_AdoubleSpinBox_valueChanged(double arg);
    void on_BdoubleSpinBox_valueChanged(double arg);
    void on_CdoubleSpinBox_valueChanged(double arg);
    void on_ResetButton_clicked();
};

#endif // WIDGET_H
