import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

SettingsBaseDelegate {
    id: control

    CheckBox {
        spacing: 0
        rightPadding: 0
        checked: control.value
        onCheckedChanged: control.model.value = checked
    }
}
