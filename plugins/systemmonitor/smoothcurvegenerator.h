/*
 * 参考代码原属主：公孙二狗
 * 链接地址：http://www.qtdebug.com/qtbook-paint-smooth-curve/
 * https://www.codeproject.com/Articles/31859/Draw-a-Smooth-Curve-through-a-Set-of-D-Points-wit%EF%BC%8C%E6%A0%B8%E5%BF%83%E6%98%AF%E4%BD%BF%E7%94%A8%E6%9B%B2%E7%BA%BF%E4%B8%8A%E7%9A%84%E7%82%B9%E8%AE%A1%E7%AE%97%E5%87%BA%E8%B4%9D%E5%A1%9E%E5%B0%94%E6%9B%B2%E7%BA%BF%E7%9A%84%E4%B8%A4%E4%B8%AA%E6%8E%A7%E5%88%B6%E7%82%B9%EF%BC%8C%E7%84%B6%E5%90%8E%E4%BD%BF%E7%94%A8%E8%B4%9D%E5%A1%9E%E5%B0%94%E6%9B%B2%E7%BA%BF%E7%94%9F%E6%88%90%E5%B9%B3%E6%BB%91%E6%9B%B2%E7%BA%BF%EF%BC%8C%E5%BE%88%E6%83%AD%E6%84%A7%E7%9A%84%E6%98%AF%E7%94%9F%E6%88%90%E6%8E%A7%E5%88%B6%E7%82%B9%E7%9A%84%E7%AE%97%E6%B3%95%E7%BB%86%E8%8A%82%E6%88%91%E6%B2%A1%E7%9C%8B%E6%87%82%EF%BC%8C%E5%8F%AA%E4%B8%8D%E8%BF%87%E6%98%AF%E4%BD%9C%E4%BA%86%E4%B8%80%E6%AC%A1%E6%90%AC%E8%BF%90%E5%B7%A5%EF%BC%8C%E6%8A%8A%E7%A8%8B%E5%BA%8F%E7%A7%BB%E6%A4%8D%E5%88%B0%E4%BA%86
 */

#ifndef SMOOTHCURVEGENERATOR_H
#define SMOOTHCURVEGENERATOR_H

#include <QList>
#include <QPainterPath>
#include <QPointF>

class SmoothCurveGenerator {
public:
    /**
     * 传入曲线上的点的 list，创建平滑曲线
     *
     * @param points - 曲线上的点
     * @return - 返回使用给定的点创建的 QPainterPath 表示的平滑曲线
     * 生成的平滑曲线，会发现平滑曲线段之间会有很多小段的抖动
     */
    static QPainterPath generateSmoothCurve1(const QList<QPointF> &points);

    /**
     * 传入曲线上的点的 list，创建平滑曲线
     * @param points - 曲线上的点
     * @return - 返回使用给定的点创建的 QPainterPath 表示的平滑曲线
     * 可以解决平滑曲线段之间的抖动问题，但是曲线段在比较陡时，曲线上的值可能会超出曲线原来值的范围
     */
    static QPainterPath generateSmoothCurve(const QList<QPointF> &points);

private:
    /**
     * Solves a tridiagonal system for one of coordinates (x or y)
     * of first Bezier control points.
     * @param result - Solution vector.
     * @param rhs - Right hand side vector.
     * @param n - Size of rhs.
     */
    static void calculateFirstControlPoints(double * &result, const double *rhs, int n);
    /**
     * Calculate control points of the smooth curve using the given knots.
     * @param knots - Points of the given curve.
     * @param firstControlPoints - Store the generated first control points.
     * @param secondControlPoints - Store the generated second control points.
     */
    static void calculateControlPoints(const QList<QPointF> &knots,
                                       QList<QPointF> *firstControlPoints,
                                       QList<QPointF> *secondControlPoints);
};
#endif // SMOOTHCURVEGENERATOR_H
