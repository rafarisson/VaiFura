import QtQuick

SettingsBaseDelegate {
    id: control

    NumberTextField {
        unit: control.unit
        text: control.value
        onValueChanged: (v) => control.model.value = v
    }
}
