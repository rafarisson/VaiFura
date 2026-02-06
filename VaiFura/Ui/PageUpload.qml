import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

PageLayout {
    id: root

    required property var model

    icon: MaterialSymbols.upload
    title: qsTr("Excellon file")
    description: qsTr("Select drill file (.xln, .drl or .txt)")

    RowLayout {
        Button {
            text: qsTr("Select file")
        }
        TextField {
            Layout.fillWidth: true
            text: root.model.documentPath
            onTextEdited: root.model.documentPath = text
        }
    }
}
