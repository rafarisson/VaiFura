#ifndef DRILLDOCUMENTBUILDER_H
#define DRILLDOCUMENTBUILDER_H

#include "DrillDocument.h"

class DrillDocumentBuilder
{
public:
    DrillDocumentBuilder &addTool(const Tool &tool) {
        doc_.tools_.append(tool);
        return *this;
    }

    DrillDocumentBuilder &addHole(const Hole &drill) {
        doc_.holes_.append(drill);
        return *this;
    }

    DrillDocument build() {
        return std::move(doc_);
    }

private:
    DrillDocument doc_;
};

#endif // DRILLDOCUMENTBUILDER_H
