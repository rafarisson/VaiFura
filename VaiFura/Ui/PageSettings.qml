import QtQuick
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property ExportSettingsListModel exportSettingsModel

    visible: exportSettingsModel.size

    icon: MaterialSymbols.settings
    title: qsTr("G-code Settings")
    description: qsTr("Configure G-code parameters")

    Repeater {
        Layout.fillWidth: true

        clip: true
        model: root.exportSettingsModel
        visible: root.exportSettingsModel.size

        delegate: DelegateChooser {
            role: "type"
            DelegateChoice {
                roleValue: ExportSettingsListModel.Number
                SettingsNumberDelegate {
                    Layout.fillWidth: true
                }
            }
        }
    }

    // ListView {
    //     Layout.fillWidth: true
    //     Layout.fillHeight: true
    //     Layout.preferredWidth: 300
    //     Layout.preferredHeight: 200

    //     boundsBehavior: Flickable.StopAtBounds
    //     clip: true
    //     model: root.exportSettingsModel
    //     visible: root.exportSettingsModel.size

    //     delegate: DelegateChooser {
    //         role: "type"
    //         DelegateChoice {
    //             roleValue: ExportSettingsListModel.Number
    //             SettingsNumberDelegate {}
    //         }
    //         DelegateChoice {
    //             roleValue: ExportSettingsListModel.Text
    //             SettingsTextDelegate {}
    //         }
    //     }

    //     ScrollBar.vertical: ScrollBar {
    //         visible: true
    //     }
    // }
}
