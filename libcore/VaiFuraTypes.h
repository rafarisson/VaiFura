#ifndef VAIFURATYPES_H
#define VAIFURATYPES_H

#include <QVector>

struct Tool
{
    int id = -1;
    double mm = 0;
};

struct Drill {
    double x = 0;
    double y = 0;
    int toolId = -1;
};

#endif // VAIFURATYPES_H
