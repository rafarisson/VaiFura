#ifndef BOARDPROFILE_H
#define BOARDPROFILE_H

#include <QVector>
#include <QPointF>
#include <QRectF>

struct BoardPoint
{
    double x, y;
};

struct BoardPath
{
    QVector<BoardPoint> points;
};

class BoardProfile
{
public:
    const QVector<BoardPath>& paths() const { return paths_; }

private:
    friend class BoardProfileBuilder;

    QVector<BoardPath> paths_;
};

#endif // BOARDPROFILE_H
