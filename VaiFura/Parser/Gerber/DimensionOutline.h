#ifndef DIMENSIONOUTLINE_H
#define DIMENSIONOUTLINE_H

#include "Units.h"
#include "BoardProfileParser.h"

class BoardPath;

class DimensionOutline : public BoardProfileParser
{
public:
    bool parse(QTextStream &in, BoardProfileBuilder &builder) override;

private:
    void reset();
    double formatCoord(double v) const;
    void parseCoord(const QString &line, BoardPath &current, BoardProfileBuilder &builder) const;
    void setFormatSpecification(const QString &line);

private:
    Units unit_;
    double scale_;
};

#endif // DIMENSIONOUTLINE_H
