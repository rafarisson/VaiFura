#include "BoardProfileBuilder.h"

BoardProfileBuilder::BoardProfileBuilder(BoardProfile *profile)
    : profile_{profile}
{
    clear();
}

void BoardProfileBuilder::clear()
{
    profile_->paths_.clear();
}

void BoardProfileBuilder::addPath(const BoardPath &path)
{
    profile_->paths_.append(path);
}

