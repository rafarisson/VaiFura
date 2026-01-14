#ifndef DRILLDOCUMENT_H
#define DRILLDOCUMENT_H

#include <QVector>

struct Tool
{
    int id = -1;
    double mm = 0;
};

struct Hole {
    double x = 0;
    double y = 0;
    int toolId = -1;
};

class DrillDocument
{
public:
    explicit DrillDocument() {}
    DrillDocument(const QVector<Tool> &t, const QVector<Hole> &h);

    const QVector<Tool>& tools() const { return tools_; }
    const QVector<Hole>& holes() const { return holes_; }

    void reset();

private:
    friend class DrillDocumentBuilder;

    QVector<Tool> tools_;
    QVector<Hole> holes_;
};

#endif // DRILLDOCUMENT_H
