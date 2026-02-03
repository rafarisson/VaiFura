import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

Page {
    id: root

    required property DrillDocumentModel documentModel

    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("X Offset")
            }
            UnitTextField {
                unit: "mm"
                value: root.documentModel.offset.x
                onValueChanged: root.documentModel.offset.x = value
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Y Offset")
            }
            UnitTextField {
                unit: "mm"
                value: root.documentModel.offset.y
                onValueChanged: root.documentModel.offset.y = value
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Z Depth")
            }
            UnitTextField {
                unit: "mm"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Z Feed Rate")
            }
            UnitTextField {
                unit: "mm/min"
            }
        }
    }
}
