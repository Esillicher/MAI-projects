#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "game.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1),
    universeSize(50)
{
    isStarted = false;
    timer->setInterval(300);
    m_masterColor = "#050";
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
}

GameWidget::~GameWidget()
{
    delete [] universe;
    delete [] next;
}

void GameWidget::startStopGame(const int &number)
{
    if (isStarted)
    {
        timer->stop();
        isStarted = false;
    }
    else
    {
        generations = number;
        timer->start();
        isStarted = true;
    }
}

void GameWidget::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = false;
        }
    }
    gameEnds(true);
    update();
}

int GameWidget::cellNumber()
{
    return universeSize;
}

void GameWidget::setCellNumber(const int &s)
{
    universeSize = s;
    resetUniverse();
    update();
}

void GameWidget::resetUniverse()
{
    delete [] universe;
    delete [] next;
    universe = new bool[(universeSize + 2) * (universeSize + 2)];
    next = new bool[(universeSize + 2) * (universeSize + 2)];
    memset(universe, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
    memset(next, false, sizeof(bool)*(universeSize + 2) * (universeSize + 2));
}

QString GameWidget::dump()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDump(const QString &data)
{
    int current = 0;
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k*universeSize + j] = data[current] == '*';
            current++;
        }
        current++;
    }
    update();
}

bool GameWidget::isAlive(int k, int j)
{
    int power = 0;
    power += universe[(k+1)*universeSize +  j];
    power += universe[(k-1)*universeSize + j];
    power += universe[k*universeSize + (j+1)];
    power += universe[k*universeSize + (j-1)];
    power += universe[(k+1)*universeSize + ( j-1)];
    power += universe[(k-1)*universeSize + (j+1)];
    power += universe[(k-1)*universeSize + (j-1)];
    power += universe[(k+1)*universeSize +  (j+1)];
    if (((universe[k*universeSize + j] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void GameWidget::newGeneration()
{
    if(generations < 0)
        generations++;
    int notChanged=0;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            next[k*universeSize + j] = isAlive(k, j);
            if(next[k*universeSize + j] == universe[k*universeSize + j])
                notChanged++;
        }
    }
    if(notChanged == universeSize*universeSize) {
        QMessageBox::information(this,
                                 tr("Игра закончена."),
                                 tr("Все следующие поколения будут одинаковыми."),
                                 QMessageBox::Ok);
        startStopGame();
        gameEnds(true);
        return;
    }
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            universe[k*universeSize + j] = next[k*universeSize + j];
        }
    }
    update();
    generations--;
    if(generations == 0) {
        startStopGame();
        gameEnds(true);
        QMessageBox::information(this,
                                 tr("Игра закончена."),
                                 tr("Итерации завершились."),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel);
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    universe[k*universeSize + j] = !universe[k*universeSize + j];
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    int currentLocation = k*universeSize + j;
    if(!universe[currentLocation]){                // если текущая ячейка пуста, заливаем её
        universe [currentLocation]= !universe[currentLocation];
        update();
    }
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // границы поля
    QColor gridColor = QColor("#000"); // цвет сетки
    gridColor.setAlpha(30); // устанавливаем прозрачность цвета сетки
    p.setPen(gridColor);
    double cellWidth = (double)width()/universeSize; // ширина окна / количество ячеек в ряду
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize; // высота окна / количество ячеек в ряду
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(universe[k*universeSize + j] == true) { // если ячейка заливается ("живая")
                qreal left = (qreal)(cellWidth*j-cellWidth); // отступ слева
                qreal top  = (qreal)(cellHeight*k-cellHeight); // отступ сверху
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(m_masterColor)); // заливка ячейки
            }
        }
    }
}

QColor GameWidget::getMasterColor()
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}
