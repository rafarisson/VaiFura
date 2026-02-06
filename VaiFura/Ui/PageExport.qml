import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel

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
        }
    }

    Button {
        Layout.fillWidth: true
        text: qsTr("Export")
        enabled: root.documentModel.selectedHoleCount
    }
}
