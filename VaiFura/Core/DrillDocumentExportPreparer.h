#ifndef DRILLDOCUMENTEXPORTPREPARER_H
#define DRILLDOCUMENTEXPORTPREPARER_H

#include <QPointF>
#include "DrillDocument.h"

class DrillTransform;

class DrillDocumentExportPreparer
{
public:
    const DrillDocument *document() const { return &doc_; }
    void prepare(const DrillDocument &src, const DrillTransform &transform);

private:
    DrillDocument doc_;
};

#endif // DRILLDOCUMENTEXPORTPREPARER_H
