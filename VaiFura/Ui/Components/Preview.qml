import QtQuick

import VaiFura.Model
import VaiFura.Preview

Item {
    id: root

    required property DrillDocumentModel documentModel

    function fit() {
        Qt.callLater(documentPreview.fitToContent)
    }

    DrillDocumentPreview {
        id: documentPreview
        anchors.fill: parent
        model: root.documentModel
    }

    Component.onCompleted: Qt.callLater(fit)
}
