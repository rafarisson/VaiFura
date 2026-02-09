import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property SettingsListModel settingsModel

    // property alias currentPath: folderDialog.currentFolder

    signal saveRequest(path: string)

    icon: MaterialSymbols.download
    title: qsTr("G-Code file")
    description: qsTr("Configure G-code parameters")

    Repeater {
        Layout.fillWidth: true

        clip: true
        model: root.settingsModel
        visible: root.settingsModel.size

        delegate: DelegateChooser {
            role: "type"
            DelegateChoice {
                roleValue: SettingsListModel.Number
                SettingsNumberDelegate {
                    Layout.fillWidth: true
                }
            }
            DelegateChoice {
                roleValue: SettingsListModel.Boolean
                SettingsBooleanDelegate {
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
    //     model: root.settingsModel
    //     visible: root.settingsModel.size

    //     delegate: DelegateChooser {
    //         role: "type"
    //         DelegateChoice {
    //             roleValue: SettingsListModel.Number
    //             SettingsNumberDelegate {}
    //         }
    //         DelegateChoice {
    //             roleValue: SettingsListModel.Boolean
    //             SettingsBooleanDelegate {}
    //         }
    //     }
    // }

    Button {
        Layout.fillWidth: true
        text: qsTr("Export")
        enabled: root.documentModel.selectedHoleCount
        onClicked: folderDialog.open()
    }

    FolderDialog {
        id: folderDialog
        onAccepted: root.saveRequest(selectedFolder)
    }
}
