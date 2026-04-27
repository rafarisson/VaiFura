import QtQuick
import QtQuick.Layouts

import VaiFura.Model

Repeater {
    id: root

    required property SettingsListModel settingsModel

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
