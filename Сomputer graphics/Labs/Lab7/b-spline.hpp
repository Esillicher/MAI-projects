#ifndef BSPLINE_HPP
#define BSPLINE_HPP

#include <QPointF>
#include <vector>

using namespace std;


class BSpline
{
private:
    int anchors_cnt = 7;
    int order = 4;
    int steps = 100;

    vector<int> knots;

    double N(const vector<int> &T, int i, int order, float t)
    {
        // the inequality should be as follows: T[i] <= t <= T[i+1],
        // but I figured I don't really want to fiddle with "correct" floating point numbers comparsion
        // and will play lazy and just add the very last anchor point to the list of a spline's values

        // of course, it absolutely WILL backfire when last (order) knots are not equal, but.. oh well.

        if(order == 1)
            return T.at(i) <= t && t < T.at(i+1);

        double nA = t - T.at(i);
        double dA = T.at(i + order - 1) - T.at(i);

        double nB = T.at(i + order) - t;
        double dB = T.at(i + order) - T.at(i+1);

        double A = (dA == 0)? 0 : nA / dA;
        double B = (dB == 0)? 0: nB / dB;
        return A * N(T, i, order - 1, t) + B * N(T, i + 1, order - 1, t);
    }

public:
    BSpline()
    {
        CalculateKnots();
    }

    void CalculateKnots()
    {
        // for a spline to go through the first and last control points,
        // its first and last (order) knots are required to be the same
        // (see the note about knots multiplicity @ wiki)

        // a possible set of knots is:
        // [0] x k * [1 .. N - k - 2] + [N - k - 1] * k
        // where N is the number of control points and k is the spline's degree

        for(int i = 0; i < order; ++i)
            knots.push_back(0);
        for(int i = 1; i < anchors_cnt - (order - 1); ++i)
            knots.push_back(i);
        for(int i = 0; i < order; ++i)
            knots.push_back(anchors_cnt - (order - 1));
    }

    vector<QPointF> Calculate(vector<QPointF> AnchorPoints)
    {
        vector<QPointF> res;

        for(int s = 0; s < steps; ++s)
        {
            double t = s / float(steps) * order;
            QPointF pt(0.0, 0.0);

            for(int i = 0; i < anchors_cnt; ++i)
                pt += N(knots, i, order, t) * AnchorPoints[i];
            res.push_back(pt);
        }

        // see note regarding inequality in N() function at the top
        res.push_back(AnchorPoints.back());

        return res;
    }
};

#endif // BSPLINE_HPP
