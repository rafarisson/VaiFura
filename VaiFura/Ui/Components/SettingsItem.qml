import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: control

    default property alias editor: contentWrapper.data

    property string label: ""
    property string description: ""

    width: itemLayout.implicitWidth
    implicitHeight: itemLayout.implicitHeight

    Layout.fillWidth: true

    RowLayout {
        id: itemLayout
        anchors.fill: parent
        Layout.fillWidth: true

        Label {
            Layout.fillWidth: !helpToolTip.enabled
            text: control.label
        }
        HelpToolTip {
            id: helpToolTip
            Layout.fillWidth: enabled
            help: control.description
        }
        Item {
            id: contentWrapper
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
        }
    }
}
