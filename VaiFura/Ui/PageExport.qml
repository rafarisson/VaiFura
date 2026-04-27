import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property SettingsListModel settingsModel

    property alias currentPath: folderDialog.currentFolder

    signal saveRequest(path: string)

    icon: MaterialSymbols.download
    title: qsTr("G-Code file")
    description: qsTr("Configure G-code parameters")

    visible: settingsModel.size

    SettingsRepeater {
        settingsModel: root.settingsModel
    }

    Button {
        Layout.fillWidth: true
        text: qsTr("Export")
        enabled: root.documentModel.selectedHoleCount
        onClicked: folderDialog.open()
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
            currentFolder = selectedFolder
            root.saveRequest(selectedFolder)
        }
    }
}
