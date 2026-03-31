import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

PageLayout {
    id: root

    required property string drillFileName
    required property string profileFileName
    property var _targetProperty

    signal drillFileSelected(fn: string)
    signal profileFileSelected(fn: string)

    icon: MaterialSymbols.upload
    title: qsTr("Upload files")
    description: qsTr("Select drill file (.xln, .drl or .txt) and board profile (.gbr)")

    RowLayout {
        Button {
            text: qsTr("Dill")
            onClicked: drillFileDialog.open()
        }
        TextField {
            Layout.fillWidth: true
            text: root.drillFileName
            onTextChanged: if (text != root.drillFileName) root.drillFileSelected(text)
        }
    }
    RowLayout {
        Button {
            text: qsTr("Profile")
            onClicked: profileFileDialog.open()
        }
        TextField {
            Layout.fillWidth: true
            text: root.profileFileName
            onTextChanged: if (text != root.profileFileName) root.profileFileSelected(text)
        }
    }

    FileDialog {
        id: drillFileDialog
        nameFilters: ["Excellon files (*.xln)", "Drill files (*.drl)", "All files (*.*)"]
        currentFolder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]
        onAccepted: root.drillFileSelected(currentFile)
    }
    FileDialog {
        id: profileFileDialog
        nameFilters: ["Profile files (*.gbr)", "All files (*.*)"]
        currentFolder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]
        onAccepted: root.profileFileSelected(currentFile)
    }
}
