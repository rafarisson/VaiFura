import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

PageLayout {
    id: root

    required property string fileName

    signal fileSelected(fn: string)

    icon: MaterialSymbols.upload
    title: qsTr("Excellon file")
    description: qsTr("Select drill file (.xln, .drl or .txt)")

    RowLayout {
        Button {
            text: qsTr("Select file")
            onClicked: fileDialog.open()
        }
        TextField {
            Layout.fillWidth: true
            text: root.fileName
            onTextChanged: if (text != root.fileName) root.fileSelected(text)
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["Excellon files (*.xln)", "Drill files (*.drl)", "All files (*.*)"]
        currentFolder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]
        onAccepted: root.fileSelected(currentFile)
    }
}
