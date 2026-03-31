#ifndef BOARDPROFILEBUILDER_H
#define BOARDPROFILEBUILDER_H

#include "BoardProfile.h"

class BoardProfileBuilder
{
public:
    explicit BoardProfileBuilder(BoardProfile *profile);

    void clear();
    void addPath(const BoardPath &path);

private:
    BoardProfile *profile_;
};

#endif // BOARDPROFILEBUILDER_H
