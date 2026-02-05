import QtQuick
import QtQuick.Controls

Label {
    id: control

    property string help: ""
    readonly property bool enabled: help !== ""

    text: MaterialSymbols.help
    font.family: MaterialSymbols.fontFamily
    font.pointSize: 12
    color: "gray"
    visible: enabled

    HoverHandler {
        id: hover
        enabled: control.enabled
    }

    ToolTip.text: help
    ToolTip.visible: hover.hovered
}
