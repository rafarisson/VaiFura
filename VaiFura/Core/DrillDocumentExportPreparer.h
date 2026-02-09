#ifndef DRILLDOCUMENTEXPORTPREPARER_H
#define DRILLDOCUMENTEXPORTPREPARER_H

#include <QPointF>
#include "DrillDocument.h"

class DrillDocumentExportPreparer
{
public:
    const DrillDocument *document() const { return &doc_; }
    void prepare(const DrillDocument &src, const QPointF &offset);

private:
    DrillDocument doc_;
};

#endif // DRILLDOCUMENTEXPORTPREPARER_H
