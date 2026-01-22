#ifndef EXCELLONLEXER_H
#define EXCELLONLEXER_H

#include <QString>
#include "ExcellonToken.h"

class ExcellonLexer
{
public:
    ExcellonToken lex(const QString &line) const;
};

#endif // EXCELLONLEXER_H
