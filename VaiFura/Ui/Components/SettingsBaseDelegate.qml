import QtQuick

Item {
    id: control

    default property alias editor: item.editor

    required property var model
    required property string label
    required property string description
    required property string unit
    required property var value

    width: ListView.view ? ListView.view.width : parent.width
    implicitHeight: item.implicitHeight

    SettingsItem {
        id: item
        width: control.width
        label: control.label
        description: control.description
    }
}
