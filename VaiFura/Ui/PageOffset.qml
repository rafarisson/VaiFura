import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel

    icon: MaterialSymbols.gamepad
    title: qsTr("Position Offset")
    description: qsTr("Control positional offset")

    ColumnLayout {
        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("X Offset")
            }
            UnitTextField {
                unit: "mm"
                text: root.documentModel.offset.x
                onValueChanged: (value) => root.documentModel.offset.x = value
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
                text: root.documentModel.offset.y
                onValueChanged: (value) => root.documentModel.offset.y = value
            }
        }
    }
}
