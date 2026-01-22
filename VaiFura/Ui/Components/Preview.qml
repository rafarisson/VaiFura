import QtQuick

import VaiFura.Model
import VaiFura.Preview

Item {
    id: root

    required property DrillDocumentModel doc

    function fit() {
        // Qt.callLater(documentPreview.fitToContent)
    }

    // onWidthChanged: Qt.callLater(fit)
    // onHeightChanged: Qt.callLater(fit)

    DrillDocumentPreview {
        id: documentPreview
        anchors.fill: parent
        model: root.doc
    }
}
