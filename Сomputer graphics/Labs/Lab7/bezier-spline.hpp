#ifndef BEZIERSPLINE_HPP
#define BEZIERSPLINE_HPP

#include <QPointF>
#include <vector>
#include <cmath>

using namespace std;


class BezierSpline
{
private:
    int steps = 100;

public:
    BezierSpline() {}

    double factorial(double n)
    {
      return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }

    double B(double i, double n, double t)
    {
        return factorial(n) / (factorial(i) * factorial(n - i)) * pow(t, i) * pow(1 - t, n - i);
    }

    vector<QPointF> Calculate(vector<QPointF> AnchorPoints)
    {
        vector<QPointF> res;

        for (int s = 0; s < steps; ++s)
        {
            double t = s / (float)steps;
            QPointF pt(0.0, 0.0);

            for(uint i = 0; i < AnchorPoints.size(); ++i)
                pt += B(i, AnchorPoints.size() - 1, t) * AnchorPoints[i];
            res.push_back(pt);
        }

        return res;
    }
};

#endif // BEZIERSPLINE_HPP
