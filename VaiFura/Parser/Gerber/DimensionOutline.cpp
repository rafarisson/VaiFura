#include <QtMath>
#include <QString>
#include <QRegularExpression>
#include "DimensionOutline.h"
#include "BoardProfileBuilder.h"

bool DimensionOutline::parse(QTextStream &in, BoardProfileBuilder &builder)
{
    BoardPath current;

    builder.clear();
    reset();

    while (!in.atEnd()) {
        const QString line = in.readLine();

        // Ignora a ferramente e usa somente os pontos
        // f1 = "%ADD10C,0.152400*%" = 0.152400
        // f2 = "%ADD11C,0.254000*%" = 0.254000

        if (line.startsWith("%FS")) {
            setFormatSpecification(line);
        }
        else if (line.startsWith("X")) {
            parseCoord(line, current, builder);
        }
    }

    if (!current.points.isEmpty())
        builder.addPath(current);

    return true;
}

void DimensionOutline::reset()
{
    unit_ = Units::MM;
    scale_ = 0.0001;
}

double DimensionOutline::formatCoord(double v) const
{
    double coord =  v * scale_;
    if (unit_ == Units::INCH)
        coord *= 25.4;
    return coord;
}

void DimensionOutline::parseCoord(const QString &line, BoardPath &current, BoardProfileBuilder &builder) const
{
    // X496062Y-404368D02*
    // X320000Y-1000000D01*
    // X0Y-1000000D02*

    static const QRegularExpression re(R"(X(-?\d+)Y(-?\d+)D(\d+))");
    const auto m = re.match(line);
    if (!m.hasMatch())
        return;

    BoardPoint p{
        formatCoord(m.captured(1).toDouble()),
        formatCoord(m.captured(2).toDouble())
    };

    if (m.captured(3).toInt() == 2) {
        if (!current.points.isEmpty()) {
            builder.addPath(current);
            current.points.clear();
        }
    }

    current.points.append(p);
}

void DimensionOutline::setFormatSpecification(const QString &line)
{
    // "%FSLAX34Y34*%"

    static const QRegularExpression re(R"(X(\d)(\d)Y(\d)(\d))");

    reset();

    const auto m = re.match(line);
    if (!m.hasMatch())
        return;

    // intDigits = m.captured(1).toInt();
    int decDigits = m.captured(2).toInt();

    scale_ = 1.0 / std::pow(10.0, decDigits);
}
