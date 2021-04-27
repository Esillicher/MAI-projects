#ifndef CURVEPAINTER_H
#define CURVEPAINTER_H

#include <QPainter>
#include "matrix4x4.hpp"
#include "curve3d.hpp"

class CurvePainter
{
public:
    vector<Curve3D> Curve;

    CurvePainter() {}

    void AddCurve(int NumPoints, int NumParams)
    {
        Curve.push_back(Curve3D(NumPoints, NumParams));
    }

    void CalculateCurve(int CurveID)
    {
        Curve[CurveID].FillVector(CurveID);
    }
    void PaintCurve(int CurveID, QPainter& Painter)
    {
        for (uint i = 0; i < Curve[CurveID].points.size() - 1; ++i)
            Painter.drawLine(Curve[CurveID].points[i].GetPointF(),
                             Curve[CurveID].points[i + 1].GetPointF());
    }

    double GetCurveParam(int CurveID, int ParamID)
    {
        return Curve[CurveID].params[ParamID];
    }
    void SetCurveParam(int CurveID, int ParamID, double arg)
    {
        Curve[CurveID].params[ParamID] = arg;
    }
};

#endif // CURVEPAINTER_H
