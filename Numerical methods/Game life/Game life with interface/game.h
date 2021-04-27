#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    // когда одна из ячеек выставлена, подаём этот сигнал, чтобы заблокировать изменение размера
    void environmentChanged(bool ok);
    // когда игра заканчивается или поле очищается, подаём сигнал разблокировки поля
    void gameEnds(bool ok);

public slots:
    void startStopGame(const int &number = -1); // функция запуска-остановки
    void clear(); // функция очистки

    int cellNumber(); // количество ячеек в одном ряду
    void setCellNumber(const int &s); //  установить кол-во ячеек

    QColor getMasterColor(); // получить цвет ячеек
    void setMasterColor(const QColor &color); // установить цвет ячеек

    QString dump(); // получить дамп текущего состояния вселенной
    void setDump(const QString &data); // установить текущее состояние вселенной из дампа

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    QColor m_masterColor;
    QTimer* timer;
    int generations;
    bool* universe; // поле
    bool* next; // поле
    int universeSize;
    bool isStarted;
    bool isAlive(int k, int j); // жива ли клетка в соотствествии с правилами игры
    void resetUniverse();// очистка значений полей
};

#endif // GAMEWIDGET_H
