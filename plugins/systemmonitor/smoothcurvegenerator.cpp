/*
 * 参考代码原属主：公孙二狗
 * 链接地址：http://www.qtdebug.com/qtbook-paint-smooth-curve/
 * https://www.codeproject.com/Articles/31859/Draw-a-Smooth-Curve-through-a-Set-of-D-Points-wit%EF%BC%8C%E6%A0%B8%E5%BF%83%E6%98%AF%E4%BD%BF%E7%94%A8%E6%9B%B2%E7%BA%BF%E4%B8%8A%E7%9A%84%E7%82%B9%E8%AE%A1%E7%AE%97%E5%87%BA%E8%B4%9D%E5%A1%9E%E5%B0%94%E6%9B%B2%E7%BA%BF%E7%9A%84%E4%B8%A4%E4%B8%AA%E6%8E%A7%E5%88%B6%E7%82%B9%EF%BC%8C%E7%84%B6%E5%90%8E%E4%BD%BF%E7%94%A8%E8%B4%9D%E5%A1%9E%E5%B0%94%E6%9B%B2%E7%BA%BF%E7%94%9F%E6%88%90%E5%B9%B3%E6%BB%91%E6%9B%B2%E7%BA%BF%EF%BC%8C%E5%BE%88%E6%83%AD%E6%84%A7%E7%9A%84%E6%98%AF%E7%94%9F%E6%88%90%E6%8E%A7%E5%88%B6%E7%82%B9%E7%9A%84%E7%AE%97%E6%B3%95%E7%BB%86%E8%8A%82%E6%88%91%E6%B2%A1%E7%9C%8B%E6%87%82%EF%BC%8C%E5%8F%AA%E4%B8%8D%E8%BF%87%E6%98%AF%E4%BD%9C%E4%BA%86%E4%B8%80%E6%AC%A1%E6%90%AC%E8%BF%90%E5%B7%A5%EF%BC%8C%E6%8A%8A%E7%A8%8B%E5%BA%8F%E7%A7%BB%E6%A4%8D%E5%88%B0%E4%BA%86
 */

#include "smoothcurvegenerator.h"

QPainterPath SmoothCurveGenerator::generateSmoothCurve1(const QList<QPointF> &points) {
    if (points.size() == 0) {
        return QPainterPath();
    }
    QPainterPath path(points[0]);
    for (int i = 0; i < points.size() - 1; ++i) {
        // 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
        // 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
        // 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
        QPointF sp = points[i];
        QPointF ep = points[i+1];
        QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
        QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());
        path.cubicTo(c1, c2, ep);
    }
    return path;
}

//使用QPainterPath画贝塞尔曲线
QPainterPath SmoothCurveGenerator::generateSmoothCurve(const QList<QPointF> &points) 
{
    QPainterPath path;
    int len = points.size();
    if (len < 2) {
        return path;
    }
    
    QList<QPointF> firstControlPoints;
    QList<QPointF> secondControlPoints;
    
    calculateControlPoints(points, &firstControlPoints, &secondControlPoints);
    path.moveTo(points[0].x(), points[0].y());//默认是从原点（0，0）开始绘图，使用moveTo（）改变绘图的开始位置
    
    // Using bezier curve to generate a smooth curve.
    for (int i = 0; i < len - 1; ++i) {
        path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i+1]);//三阶贝赛尔曲线函数cubicto()绘图,传入点1 firstControlPoints[i]，点2 secondControlPoints[i]，endPoint（points[i+1]）
    }
    return path;
}

void SmoothCurveGenerator::calculateFirstControlPoints(double *&result, const double *rhs, int n) 
{
    double *tmp = new double[n];
    double b = 2.0;
    result[0] = rhs[0] / b;
    
    // Decomposition and forward substitution.
    for (int i = 1; i < n; i++) {
        tmp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }
    
    for (int i = 1; i < n; i++) {
        result[n - i - 1] -= tmp[n - i] * result[n - i]; // Backsubstitution.
    }
    
    delete[] tmp;
}

void SmoothCurveGenerator::calculateControlPoints(const QList<QPointF> &knots, QList<QPointF> *firstControlPoints, QList<QPointF> *secondControlPoints) 
{
    int n = knots.size() - 1;

    for (int i = 0; i < n; ++i) {
        firstControlPoints->append(QPointF());
        secondControlPoints->append(QPointF());
    }
    
    if (n == 1) {
        // Special case: Bezier curve should be a straight line.
        // P1 = (2P0 + P3) / 3
        (*firstControlPoints)[0].rx() = (2 * knots[0].x() + knots[1].x()) / 3;
        (*firstControlPoints)[0].ry() = (2 * knots[0].y() + knots[1].y()) / 3;

        // P2 = 2P1 – P0
        (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - knots[0].x();
        (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - knots[0].y();
        return;
    }
    
    // Calculate first Bezier control points
    double *xs = new double[n];
    double *ys = new double[n];
    double *rhsx = new double[n]; // Right hand side vector
    double *rhsy = new double[n]; // Right hand side vector
    
    // Set right hand side values
    for (int i = 1; i < n - 1; ++i) {
        rhsx[i] = 4 * knots[i].x() + 2 * knots[i + 1].x();
        rhsy[i] = 4 * knots[i].y() + 2 * knots[i + 1].y();
    }
    rhsx[0] = knots[0].x() + 2 * knots[1].x();
    rhsx[n - 1] = (8 * knots[n - 1].x() + knots[n].x()) / 2.0;
    rhsy[0] = knots[0].y() + 2 * knots[1].y();
    rhsy[n - 1] = (8 * knots[n - 1].y() + knots[n].y()) / 2.0;
    
    // Calculate first control points coordinates
    calculateFirstControlPoints(xs, rhsx, n);
    calculateFirstControlPoints(ys, rhsy, n);
    
    // Fill output control points.
    for (int i = 0; i < n; ++i) {
        (*firstControlPoints)[i].rx() = xs[i];
        (*firstControlPoints)[i].ry() = ys[i];

        if (i < n - 1) {
            (*secondControlPoints)[i].rx() = 2 * knots[i + 1].x() - xs[i + 1];
            (*secondControlPoints)[i].ry() = 2 * knots[i + 1].y() - ys[i + 1];
        } else {
            (*secondControlPoints)[i].rx() = (knots[n].x() + xs[n - 1]) / 2;
            (*secondControlPoints)[i].ry() = (knots[n].y() + ys[n - 1]) / 2;
        }
    }
    
    delete[] xs;
    delete[] ys;
    delete[] rhsx;
    delete[] rhsy;
}
