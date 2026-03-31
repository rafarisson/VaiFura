#ifndef BOARDPROFILEPARSER_H
#define BOARDPROFILEPARSER_H

#include <QTextStream>

class BoardProfileBuilder;

class BoardProfileParser
{
public:
    virtual ~BoardProfileParser() = default;
    virtual bool parse(QTextStream &in, BoardProfileBuilder &builder) = 0;
};

#endif // BOARDPROFILEPARSER_H
