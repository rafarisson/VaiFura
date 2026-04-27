import QtQuick

import VaiFura.Model

PageLayout {
    id: root

    required property SettingsListModel settingsModel

    icon: MaterialSymbols.precision_manufacturing
    title: qsTr("Machine Setup")
    description: qsTr("Configure machine origin and work offsets")

    visible: settingsModel.size

    SettingsRepeater {
        settingsModel: root.settingsModel
    }
}
