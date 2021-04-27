#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <QPainter>
#include <algorithm>
#include <cmath>
using namespace std;

class Segment
{
private:
    int algorithm, step;
    QPoint sPointScr, ePointScr;
    QPoint sPointGrd, ePointGrd;

public:
    Segment() {}
    Segment(int alg, int step, QPoint start_p, QPoint end_p)
    {
        algorithm = alg;
        this->step = step;
        sPointScr = start_p;
        ePointScr = end_p;
    }
    ~Segment() {}

    void ScrToGrd()
    {
        sPointGrd = QPoint(sPointScr.x() / step, sPointScr.y() / step);
        ePointGrd = QPoint(ePointScr.x() / step, ePointScr.y() / step);
    }
    QPoint GrdToScr(QPoint point)
    {
        return QPoint(point.x() * step + step / 2,
                      point.y() * step + step / 2);
    }

    void None(QPainter& painter)
    {
        QPen pen;
        pen.setWidth(step);
        pen.setColor(Qt::gray);
        painter.setPen(pen);
        painter.drawLine(GrdToScr(sPointGrd), GrdToScr(ePointGrd));
    }

    void drawPixel(QPainter& painter, int x, int y, float alpha, bool wasSwapped)
    {
        if (wasSwapped) swap(x, y);
        QColor color = Qt::gray;
        color.setAlphaF(alpha);
        painter.fillRect(x * step, y * step, step, step, color);
    }

    bool needSwapping(int& x0, int& y0, int& x1, int& y1)
    {
        bool wasSwapped = false;
        if (abs(y1 - y0) > abs(x1 - x0))
        {
            swap(x0, y0);
            swap(x1, y1);
            wasSwapped = true;
        }
        if (x0 > x1)
        {
            swap(x0, x1);
            swap(y0, y1);
        }
        return wasSwapped;
    }

    void Bresenham(QPainter& painter)
    {
        int x0 = sPointGrd.x(), y0 = sPointGrd.y();
        int x1 = ePointGrd.x(), y1 = ePointGrd.y();

        bool wasSwapped = needSwapping(x0, y0, x1, y1);

        int dx = x1 - x0;
        int dy = abs(y1 - y0);
        int error = 0;
        int ystep = (y0 < y1) ? 1 : -1;
        int y = y0;
        for (int x = x0; x <= x1; ++x)
        {
            drawPixel(painter, x, y, 1.0, wasSwapped);
            error += dy;
            if (2 * error >= dx)
            {
                y += ystep;
                error -= dx;
            }
        }
    }

    void Wu(QPainter& painter)
    {
        int x0 = sPointGrd.x(), y0 = sPointGrd.y();
        int x1 = ePointGrd.x(), y1 = ePointGrd.y();

        bool wasSwapped = needSwapping(x0, y0, x1, y1);

        drawPixel(painter, x0, y0, 1, wasSwapped);
        drawPixel(painter, x1, y1, 1, wasSwapped);

        float gradient = (y1 - y0) / (float)(x1 - x0);
        float y = y0 + gradient;
        for (int x = x0 + 1; x < x1; ++x)
        {
            drawPixel(painter, x, (int)y, 1 - (y - (int)y), wasSwapped);
            drawPixel(painter, x, (int)y + 1, y - (int)y, wasSwapped);
            y += gradient;
        }
    }

    float altitudeFromSubPixCenter(float Ax, float Ay,
                                   float Bx, float By,
                                   float Cx, float Cy,
                                   float AB, bool wasSwapped)
    {
        if (wasSwapped)
        {
            swap(Ax, Ay);
            swap(Bx, By);
            swap(Cx, Cy);
        }
        float doubleSquare = (Bx - Ax) * (Cy - Ay) - (Cx - Ax) * (By - Ay);
        if (doubleSquare < 0) doubleSquare *= -1.0F;
        return doubleSquare / AB;
    }

    void SSAA(QPainter& painter, int N)
    {
        int x0 = sPointGrd.x(), y0 = sPointGrd.y();
        int x1 = ePointGrd.x(), y1 = ePointGrd.y();

        bool wasSwapped = needSwapping(x0, y0, x1, y1);

        if (y0 != y1)
        {
            drawPixel(painter, x0, y0, 1, wasSwapped);
            drawPixel(painter, x1, y1, 1, wasSwapped);

            float gradient = (y1 - y0) / (float)(x1 - x0);
            float y = y0 + gradient;
            float AB = sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));

            for (int x = x0 + 1; x < x1; ++x)
            {
                float averageColorF = 0.0F;
                float averageColorS = 0.0F;

                for (int i = 0; i < N; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        float altitudeF = 1 - altitudeFromSubPixCenter(x0 + 0.5F, y0 + 0.5F,
                                                                       x1 + 0.5F, y1 + 0.5F,
                                                                       x + 0.5F / N + i / N,
                                                                       (int)y + 0.5F / N + j / N,
                                                                       AB, wasSwapped);
                        float altitudeS = 1 - altitudeFromSubPixCenter(x0 + 0.5F, y0 + 0.5F,
                                                                       x1 + 0.5F, y1 + 0.5F,
                                                                       x + 0.5F / N + i / N,
                                                                       (int)y + 0.5F / N + j / N + 1,
                                                                       AB, wasSwapped);
                        averageColorF += (altitudeF < 0) ? 0 : altitudeF;
                        averageColorS += (altitudeS < 0) ? 0 : altitudeS;
                    }
                }

                drawPixel(painter, x, (int)y, averageColorF / pow(N, 2), wasSwapped);
                drawPixel(painter, x, (int)y + 1, averageColorS / pow(N, 2), wasSwapped);
                y += gradient;
            }
        }
        else
            None(painter);
    }

    void Draw(QPainter& painter, int step, bool baseLineVisible)
    {
        this->step = step;
        ScrToGrd();

        switch (algorithm)
        {
            case 0: None(painter); break;
            case 1: Bresenham(painter); break;
            case 2: Wu(painter); break;
            case 3: SSAA(painter, 2); break;
            case 4: SSAA(painter, 4); break;
            case 5: SSAA(painter, 8); break;
            default: break;
        }

        if (baseLineVisible)
        {
            painter.setPen(Qt::black);
            painter.drawEllipse(GrdToScr(sPointGrd), 2, 2);
            painter.drawEllipse(GrdToScr(ePointGrd), 2, 2);
            painter.drawLine(GrdToScr(sPointGrd), GrdToScr(ePointGrd));
        }
    }
};

#endif // SEGMENT_HPP
