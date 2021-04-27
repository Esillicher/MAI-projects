#include "widget.h"
#include "ui_widget.h"

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    step = 10;
    ui->StepSpinBox->setValue(step);
    startPoint = QPoint(-1, -1);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        startPoint = e->pos();
    }
    if (e->button() == Qt::RightButton)
    {
        if (ui->SegmentButton->isChecked() && Segments.size() > 0) Segments.pop_back();
        if (ui->CircleButton->isChecked() && Circles.size() > 0) Circles.pop_back();
        repaint();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *e)
{
    endPoint = e->pos();
    repaint();
}
void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && startPoint != e->pos())
    {
        int algorithm = ui->AlgoComboBox->currentIndex();

        if (ui->SegmentButton->isChecked())
            Segments.push_back(Segment(algorithm, step, startPoint, endPoint));

        if (ui->CircleButton->isChecked())
        {
            int radius = abs(endPoint.x() - startPoint.x()) / step * step;
            Circles.push_back(Circle(algorithm, step, startPoint, radius));
        }
    }
    startPoint = QPoint(-1, -1);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::lightGray);
    int algorithm = ui->AlgoComboBox->currentIndex();
    bool showBaseLines = ui->BaseLinesCheckBox->isChecked();

    // Сетка
    if (step > 1)
    {
        for(int i = 0; i <= height(); i += step) painter.drawLine(100, i+100, width(), i);
        for(int i = 0; i <= width(); i += step) painter.drawLine(i+100, 100, i, height());
    }

    // Нарисованные линии
    for (uint i = 0; i < Segments.size(); ++i) Segments[i].Draw(painter, step, showBaseLines);
    for (uint i = 0; i < Circles.size(); ++i) Circles[i].Draw(painter, step, showBaseLines);

    // Рисуемая линия
    if (startPoint.x() >= 0)
    {
        if (ui->SegmentButton->isChecked())
            Segment(algorithm, step, startPoint, endPoint).Draw(painter, step, showBaseLines);
        if (ui->CircleButton->isChecked())
        {
            int radius = abs(endPoint.x() - startPoint.x()) / step * step;
            Circle(algorithm, step, startPoint, radius).Draw(painter, step, showBaseLines);
        }
    }
}

void Widget::on_StepSpinBox_valueChanged(int arg)
{
    step = arg;

    static bool BaseLinesToggled = false;
    if (step == 1)
    {
        BaseLinesToggled = ui->BaseLinesCheckBox->isChecked();
        ui->BaseLinesCheckBox->setChecked(false);
    }
    else if (BaseLinesToggled)
    {
        ui->BaseLinesCheckBox->setChecked(true);
        BaseLinesToggled = false;
    }

    repaint();
}
void Widget::on_BaseLinesCheckBox_toggled()
{
    repaint();
}
