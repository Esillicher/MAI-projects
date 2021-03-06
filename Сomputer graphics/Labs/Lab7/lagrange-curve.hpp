#ifndef LAGRANGECURVE_HPP
#define LAGRANGECURVE_HPP

#include <QPointF>
#include <vector>

using namespace std;


class LagrangeSpline
{
private:
    int steps = 100;
    vector<QPointF> AnchorPoints;

public:
    LagrangeSpline() {}

    double l(uint i, double x)
    {
        double res = 1;
        for (uint j = 0; j < AnchorPoints.size(); ++j)
        {
            if (i == j) continue;
            res *= (x - AnchorPoints[j].x()) / (AnchorPoints[i].x() - AnchorPoints[j].x());
        }
        return res;
    }

    double L(double x)
    {
        double res = 0;

        for (uint i = 0; i < AnchorPoints.size(); ++i)
            res += AnchorPoints[i].y() * l(i, x);

        return res;
    }

    vector<QPointF> Calculate(vector<QPointF> AnchorPoints)
    {
        this->AnchorPoints = AnchorPoints;

        vector<QPointF> res;
        double t = (AnchorPoints.back().x() - AnchorPoints.front().x()) / steps;

        for (double s = AnchorPoints.front().x(); s <= AnchorPoints.back().x(); s += t)
            res.push_back(QPointF(s, L(s)));

        return res;
    }
};

#endif // LAGRANGECURVE_HPP
