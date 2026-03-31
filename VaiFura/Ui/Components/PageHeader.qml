import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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

    ColumnLayout {
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
            Layout.fillWidth: true

            id: titleLabel
            font.bold: true
        }

        Label {
            Layout.fillWidth: true

            id: descriptionLabel
            textFormat: Text.PlainText
            wrapMode: Text.WordWrap
            visible: text !== ""
        }
    }
}
