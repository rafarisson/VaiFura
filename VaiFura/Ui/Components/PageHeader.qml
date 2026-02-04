import QtQuick
import QtQuick.Controls

Item {
    id: control

    property alias icon: iconLabel.text
    property alias iconSize: iconLabel.font.pointSize
    property alias title: titleLabel.text
    property alias description: descriptionLabel.text

    readonly property int margin: 12

    implicitHeight: Math.max(iconLabel.implicitHeight, contentColumn.implicitHeight) + margin * 2
    implicitWidth: iconLabel.implicitWidth + contentColumn.implicitWidth + margin * 3

    Label {
        id: iconLabel

        anchors {
            left: parent.left
            leftMargin: control.margin
            verticalCenter: parent.verticalCenter
        }

        font.family: MaterialSymbols.fontFamily
        font.pointSize: 24
        color: "gray"
    }

    Column {
        id: contentColumn
        spacing: 4

        anchors {
            left: iconLabel.right
            leftMargin: control.margin
            right: parent.right
            rightMargin: control.margin
            verticalCenter: parent.verticalCenter
        }

        Label {
            id: titleLabel
            font.bold: true
        }

        Label {
            id: descriptionLabel
            textFormat: Text.PlainText
            wrapMode: Text.WordWrap
            visible: text !== ""
        }
    }
}
