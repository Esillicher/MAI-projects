#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Phi = Psi = 0;
    Painter.AddCurve(100, 3);
    Painter.AddCurve(100, 2);
    Painter.Curve[0].SetDefaultParams(0);
    Painter.Curve[1].SetDefaultParams(1);
    Painter.Curve[0].SetTranslation(this->width() / 2.0, this->height() / 2.0, 0);
    Painter.Curve[1].SetTranslation(this->width() / 2.0, this->height() / 2.0, 0);

    CurveID = 2;
    SetLabelsAndBoxesHidden(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    PrevX = e->x(); PrevY = e->y();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    Phi += (e->y() - PrevY) * -0.0005;
    Psi += (e->x() - PrevX) * 0.0005;
    Painter.Curve[CurveID].SetRotationX(Phi);
    Painter.Curve[CurveID].SetRotationY(Psi);
    Painter.CalculateCurve((CurveID));
    repaint();
}

void Widget::resizeEvent(QResizeEvent *e)
{
    double ScaleX = (double)e->size().width() / 600;
    double ScaleY = (double)e->size().height() / 530;
    Painter.Curve[0].SetScaling(ScaleX, ScaleY);
    Painter.Curve[1].SetScaling(ScaleX, ScaleY);
    Painter.Curve[0].SetTranslation(this->width() / 2.0, this->height() / 2.0, 0);
    Painter.Curve[1].SetTranslation(this->width() / 2.0, this->height() / 2.0, 0);
    Painter.CalculateCurve(0);
    Painter.CalculateCurve(1);
    repaint();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (CurveID < 2) Painter.PaintCurve(CurveID, painter);
}

void Widget::SetLabelsAndBoxesHidden(bool arg)
{
    ui->StepLabel->setHidden(arg);
    ui->StepIntSpinBox->setHidden(arg);
    ui->ALabel->setHidden(arg);
    ui->AdoubleSpinBox->setHidden(arg);
    ui->BLabel->setHidden(arg);
    ui->BdoubleSpinBox->setHidden(arg);
    ui->CLabel->setHidden(arg);
    ui->CdoubleSpinBox->setHidden(arg);
    ui->ResetButton->setHidden(arg);
}
void Widget::GetCurveParams(int CurveID)
{
    if (CurveID < 2)
    {
        ui->StepIntSpinBox->setValue(Painter.Curve[CurveID].points.size());
        ui->AdoubleSpinBox->setValue(Painter.Curve[CurveID].params[0]);
        ui->BdoubleSpinBox->setValue(Painter.Curve[CurveID].params[1]);
        if (CurveID == 0) ui->CdoubleSpinBox->setValue(Painter.Curve[CurveID].params[2]);
    }
}
void Widget::on_CurveComboBox_currentTextChanged(const QString &arg)
{
    if(arg == "None")
    {
        CurveID = 2;
        SetLabelsAndBoxesHidden(true);
    }
    else
    {
        CurveID = 0;
        SetLabelsAndBoxesHidden(false);

        if(arg == "Curve 2")
        {
            CurveID = 1;
            ui->CLabel->hide();
            ui->CdoubleSpinBox->hide();
        }

        Painter.CalculateCurve(CurveID);
    }
    GetCurveParams(CurveID);
    repaint();
}

void Widget::on_StepIntSpinBox_valueChanged(int arg)
{
    Painter.Curve[CurveID].points.resize(arg);
    Painter.CalculateCurve(CurveID);
    repaint();
}
void Widget::on_AdoubleSpinBox_valueChanged(double arg)
{
    Painter.Curve[CurveID].params[0] = arg;
    Painter.CalculateCurve(CurveID);
    repaint();
}
void Widget::on_BdoubleSpinBox_valueChanged(double arg)
{
    Painter.Curve[CurveID].params[1] = arg;
    Painter.CalculateCurve(CurveID);
    repaint();
}
void Widget::on_CdoubleSpinBox_valueChanged(double arg)
{
    Painter.Curve[CurveID].params[2] = arg;
    Painter.CalculateCurve(CurveID);
    repaint();
}

void Widget::on_ResetButton_clicked()
{
    Painter.Curve[CurveID].SetDefaultParams(CurveID);
    Phi = Psi = 0;
    Painter.Curve[CurveID].SetRotationX(Phi);
    Painter.Curve[CurveID].SetRotationY(Psi);
    Painter.CalculateCurve(CurveID);
    repaint();

    ui->AdoubleSpinBox->setValue(Painter.Curve[CurveID].params[0]);
    ui->BdoubleSpinBox->setValue(Painter.Curve[CurveID].params[1]);
    if (CurveID == 0) ui->CdoubleSpinBox->setValue(Painter.Curve[CurveID].params[2]);
}
