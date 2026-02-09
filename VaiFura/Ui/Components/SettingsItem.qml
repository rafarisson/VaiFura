import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: control

    default property alias editor: contentWrapper.data
    property alias columnEditor: columnEditorWrapper.data

    property string label: ""
    property string description: ""

    width: itemColumn.implicitWidth
    implicitHeight: itemColumn.implicitHeight

    ColumnLayout {
        id: itemColumn
        anchors.fill: parent

        spacing: 0

        RowLayout {
            Layout.fillWidth: true

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

        Item {
            id: columnEditorWrapper
            Layout.fillWidth: true
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
        }
    }
}
