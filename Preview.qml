import QtQuick

import libmodel
import libview

Item {
    id: root

    required property DrillDocumentModel doc

    DrillDocumentPreview {
        anchors.fill: parent
        model: root.doc
    }
}
