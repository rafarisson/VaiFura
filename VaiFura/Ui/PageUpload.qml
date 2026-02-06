import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

PageLayout {
    id: root

    required property string path

    icon: MaterialSymbols.upload
    title: qsTr("Excellon file")
    description: qsTr("Select drill file (.xln, .drl or .txt)")

    RowLayout {
        Button {
            text: qsTr("Select file")
        }
        TextField {
            Layout.fillWidth: true
            text: root.path
            onTextEdited: root.path = text
        }
    }
}
