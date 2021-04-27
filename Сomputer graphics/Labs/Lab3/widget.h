#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    float alpha;
    float beta;

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

    ~Widget();

private slots:
    void on_Figure_currentIndexChanged(int index);
    void on_LightModel_currentTextChanged(const QString &arg);
    void on_StepsSpinBox_valueChanged(int arg);
    void on_StepsSlider_valueChanged(int value);

    void on_LSourceSpinX_valueChanged(int arg);
    void on_LSourceSpinY_valueChanged(int arg);
    void on_LSourceSpinZ_valueChanged(int arg);

    void on_RedSlider1_valueChanged(int value);
    void on_RedSlider2_valueChanged(int value);
    void on_RedSlider3_valueChanged(int value);
    void on_GreenSlider1_valueChanged(int value);
    void on_GreenSlider2_valueChanged(int value);
    void on_GreenSlider3_valueChanged(int value);
    void on_BlueSlider1_valueChanged(int value);
    void on_BlueSlider2_valueChanged(int value);
    void on_BlueSlider3_valueChanged(int value);
    void on_CoeffSlider_valueChanged(int value);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
