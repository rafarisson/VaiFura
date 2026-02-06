import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property bool generateFilePerTool
    property alias outputPath: folderDialog.selectedFolder

    signal generate()

    icon: MaterialSymbols.download
    title: qsTr("G-Code file")
    description: qsTr("Export g-code file (.gcode)")

    SettingsItem {
        Layout.fillWidth: true
        label: qsTr("Generate File Per Tool")
        description: qsTr("When enabled, a separate output file is generated for each tool instead of combining all tools into a single file.")
        Switch {
            spacing: 0
            rightPadding: 0
            checked: root.generateFilePerTool
            onCheckedChanged: root.generateFilePerTool = checked
        }
    }

    Button {
        Layout.fillWidth: true
        text: qsTr("Export")
        enabled: root.documentModel.selectedHoleCount
        onClicked: folderDialog.open()
    }

    FolderDialog {
        id: folderDialog
        onAccepted: root.generate()
    }
}
