import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: control

    default property alias editor: contentWrapper.data

    required property var model
    required property string label
    required property string description
    required property string unit
    required property var value

    width: ListView.view.width
    implicitHeight: itemLayout.implicitHeight

    RowLayout {
        id: itemLayout
        anchors.fill: parent

        HelpToolTip {
            help: control.description
        }
        Label {
            Layout.fillWidth: true
            text: control.label
        }
        Item {
            id: contentWrapper
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
        }
    }
}
