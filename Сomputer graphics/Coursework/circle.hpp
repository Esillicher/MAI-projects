#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <QPainter>
#include <cmath>

class Circle
{
private:
    int algorithm, step;
    QPoint centerPointScr, centerPointGrd;
    int radiusScr, radiusGrd;

public:
    Circle() {}
    Circle(int alg, int step, QPoint center_p, int rad)
    {
        algorithm = alg;
        this->step = step;
        centerPointScr = center_p;
        radiusScr = rad;
    }
    ~Circle() {}

    void ScrToGrd()
    {
        centerPointGrd = QPoint(centerPointScr.x() / step, centerPointScr.y() / step);
        radiusGrd = radiusScr / step;
    }
    QPoint GrdToScr(QPoint point)
    {
        return QPoint(point.x() * step + step / 2,
                      point.y() * step + step / 2);
    }

    void None(QPainter& painter)
    {
        painter.setPen(QPen(Qt::gray, step));
        painter.drawEllipse(GrdToScr(centerPointGrd), radiusGrd * step, radiusGrd * step);
    }

    void drawPixel(QPainter& painter, int x, int y, float alpha)
    {
        QColor color = Qt::gray;
        color.setAlphaF(alpha);
        painter.fillRect(x * step, y * step, step, step, color);
    }

    void Bresenham(QPainter& painter)
    {
        int x0 = centerPointGrd.x(), y0 = centerPointGrd.y();
        int x = radiusGrd, y = 0;
        int radiusError = 1 - x;

        while (x >= y)
        {
            // I квадрант
            drawPixel(painter, x0 + x, y0 - y, 1); // X
            drawPixel(painter, x0 + y, y0 - x, 1); // Y

            // II квадрант
            drawPixel(painter, x0 - x, y0 - y, 1); // X
            drawPixel(painter, x0 - y, y0 - x, 1); // Y

            // III квадрант
            drawPixel(painter, x0 - x, y0 + y, 1); // X
            drawPixel(painter, x0 - y, y0 + x, 1); // Y

            // IV квадрант
            drawPixel(painter, x0 + x, y0 + y, 1); // X
            drawPixel(painter, x0 + y, y0 + x, 1); // Y

            y++;
            if (radiusError < 0)
            {
                radiusError += 2 * y + 1;
            }
            else
            {
                x--;
                radiusError += 2 * (y - x + 1);
            }
        }
    }

    void Wu(QPainter& painter)
    {
        int x0 = centerPointGrd.x(), y0 = centerPointGrd.y();

        for (int x = 0; x <= radiusGrd * cos(M_PI / 4); ++x)
        {
            //Вычисление точного значения координаты Y
            float y = sqrt(radiusGrd * radiusGrd - x * x);

            //                      X               Y                      I
            //I квадрант, X
            drawPixel(painter, x0 + (int)y,      y0 - x,           1 - (y - (int)y));
            drawPixel(painter, x0 + (int)y + 1,  y0 - x,           y - (int)y);
            //I квадрант, Y
            drawPixel(painter, x0 + x,           y0 - (int)y - 1,  y - (int)y);
            drawPixel(painter, x0 + x,           y0 - (int)y,      1 - (y - (int)y));

            //II квадрант, X
            drawPixel(painter, x0 - (int)y - 1,  y0 - x,           y - (int)y);
            drawPixel(painter, x0 - (int)y ,     y0 - x,           1 - (y - (int)y));
            //II квадрант, Y
            drawPixel(painter, x0 - x,           y0 - (int)y - 1,  y - (int)y);
            drawPixel(painter, x0 - x,           y0 - (int)y ,     1 - (y - (int)y));

            //III квадрант, X
            drawPixel(painter, x0 - (int)y - 1,  y0 + x,           y - (int)y);
            drawPixel(painter, x0 - (int)y,      y0 + x,           1 - (y - (int)y));
            //III квадрант, Y
            drawPixel(painter, x0 - x,           y0 + (int)y,      1 - (y - (int)y));
            drawPixel(painter, x0 - x,           y0 + (int)y + 1,  y - (int)y);

            //IV квадрант, X
            drawPixel(painter, x0 + (int)y,      y0 + x,           1 - (y - (int)y));
            drawPixel(painter, x0 + (int)y + 1 , y0 + x,           y - (int)y);
            //IV квадрант, Y
            drawPixel(painter, x0 + x,           y0 + (int)y,      1 - (y - (int)y));
            drawPixel(painter, x0 + x,           y0 + (int)y + 1,  y - (int)y);
        }
    }

    float distanceToCircle(float x, float y)
    {
        float distance = sqrt(pow(x - centerPointGrd.x(), 2) +
                        pow(y - centerPointGrd.y(), 2)) - radiusGrd;
        return (distance > 0) ? distance : distance * -1.0F;
    }

    void pixelSSAA(QPainter& painter, int x, int y, int N)
    {
        float alpha = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                float alphaSubpixel = 1 - distanceToCircle(x + 0.5F / N + i / N, y + 0.5F / N + j / N);
                if (alphaSubpixel > 0) alpha += alphaSubpixel;
            }
        }

        drawPixel(painter, x, y, alpha / pow(N, 2));
    }

    void SSAA(QPainter& painter, int N)
    {
        int x0 = centerPointGrd.x(), y0 = centerPointGrd.y();

        for (int x = 0; x <= radiusGrd * cos(M_PI / 4); ++x)
        {
            //Вычисление точного значения координаты Y
            float y = sqrt(radiusGrd * radiusGrd - x * x);

            //                      X               Y
            //I квадрант, X
            pixelSSAA(painter, x0 + (int)y,      y0 - x,           N);
            pixelSSAA(painter, x0 + (int)y + 1,  y0 - x,           N);
            //I квадрант, Y
            pixelSSAA(painter, x0 + x,           y0 - (int)y - 1,  N);
            pixelSSAA(painter, x0 + x,           y0 - (int)y,      N);

            //II квадрант, X
            pixelSSAA(painter, x0 - (int)y - 1,  y0 - x,           N);
            pixelSSAA(painter, x0 - (int)y ,     y0 - x,           N);
            //II квадрант, Y
            pixelSSAA(painter, x0 - x,           y0 - (int)y - 1,  N);
            pixelSSAA(painter, x0 - x,           y0 - (int)y ,     N);

            //III квадрант, X
            pixelSSAA(painter, x0 - (int)y - 1,  y0 + x,           N);
            pixelSSAA(painter, x0 - (int)y,      y0 + x,           N);
            //III квадрант, Y
            pixelSSAA(painter, x0 - x,           y0 + (int)y,      N);
            pixelSSAA(painter, x0 - x,           y0 + (int)y + 1,  N);

            //IV квадрант, X
            pixelSSAA(painter, x0 + (int)y,      y0 + x,           N);
            pixelSSAA(painter, x0 + (int)y + 1 , y0 + x,           N);
            //IV квадрант, Y
            pixelSSAA(painter, x0 + x,           y0 + (int)y,      N);
            pixelSSAA(painter, x0 + x,           y0 + (int)y + 1,  N);
        }
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
            painter.drawEllipse(GrdToScr(centerPointGrd), 2, 2);
            painter.drawEllipse(GrdToScr(centerPointGrd), radiusGrd * step, radiusGrd * step);
        }
    }
};

#endif // CIRCLE_HPP
