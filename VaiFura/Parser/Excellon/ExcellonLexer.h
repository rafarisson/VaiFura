#ifndef EXCELLONLEXER_H
#define EXCELLONLEXER_H

#include <QString>
#include "ExcellonToken.h"

class ExcellonLexer
{
public:
    ExcellonToken lex(const QString &line) const;

private:
    ExcellonToken lexToolDef(const QString &line) const;
    ExcellonToken lexToolSelect(const QString &line) const;
    ExcellonToken lexCoord(const QString &line) const;
};

#endif // EXCELLONLEXER_H
