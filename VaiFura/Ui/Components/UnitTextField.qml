import QtQuick
import QtQuick.Controls

TextField {
    id: root

    property alias unit: unitLabel.text

    implicitWidth: 150

    Label {
        id: unitLabel

        anchors {
            right: parent.right
            rightMargin: parent.leftPadding
            verticalCenter: parent.verticalCenter
        }

        visible: text !== ""
        textFormat: Text.PlainText
    }
}
