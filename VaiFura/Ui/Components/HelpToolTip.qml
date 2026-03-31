import QtQuick
import QtQuick.Controls

Label {
    id: control

    property string help: ""
    readonly property bool __enabled: help !== ""

    text: MaterialSymbols.help
    font.family: MaterialSymbols.fontFamily
    font.pointSize: 12
    color: "gray"
    visible: __enabled

    HoverHandler {
        id: hover
        enabled: control.__enabled
    }

    ToolTip.text: help
    ToolTip.visible: hover.hovered
}
