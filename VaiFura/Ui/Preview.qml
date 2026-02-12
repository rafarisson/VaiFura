import QtQuick
import QtQuick.Controls

import VaiFura.Model
import VaiFura.Preview

Item {
    id: root

    required property DrillDocumentModel documentModel
    required property DrillTransformModel transformModel

    function fit() {
        Qt.callLater(documentPreview.fitToContent)
    }

    clip: true

    DrillDocumentPreview {
        id: documentPreview
        anchors.fill: parent

        model: root.documentModel
        transformModel: root.transformModel
    }

    RoundButton {
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 12
        }

        text: MaterialSymbols.zoom_in_map
        font.family: MaterialSymbols.fontFamily
        font.pointSize: 16
        onClicked: root.fit()
    }

    Component.onCompleted: Qt.callLater(fit)
}
