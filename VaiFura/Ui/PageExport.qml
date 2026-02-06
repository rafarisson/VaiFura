import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property ExportSettingsListModel exportSettingsModel

    icon: MaterialSymbols.download
    title: qsTr("G-Code file")
    description: qsTr("Export g-code file (.gcode)")

    ColumnLayout {
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 300
            Layout.preferredHeight: 200

            boundsBehavior: Flickable.StopAtBounds
            clip: true
            model: root.exportSettingsModel
            visible: root.exportSettingsModel.size

            delegate: DelegateChooser {
                role: "type"
                DelegateChoice {
                    roleValue: ExportSettingsListModel.Number
                    SettingsNumberDelegate {}
                }
                DelegateChoice {
                    roleValue: ExportSettingsListModel.Text
                    SettingsNumberDelegate {}
                }
                DelegateChoice {
                    roleValue: ExportSettingsListModel.Boolean
                    SettingsBooleanDelegate {}
                }
            }

            ScrollBar.vertical: ScrollBar {
                visible: true
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Export")
            enabled: root.documentModel.selectedHoleCount
        }
    }
}
