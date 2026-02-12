import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillTransformModel transformModel

    icon: MaterialSymbols.gamepad
    title: qsTr("Positioning")
    description: qsTr("Adjust position, rotation and mirror")

    ColumnLayout {
        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("X Offset")
            }
            NumberTextField {
                unit: "mm"
                text: root.transformModel.offset.x
                onValueChanged: (v) => root.transformModel.offset.x = v
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Y Offset")
            }
            NumberTextField {
                unit: "mm"
                text: root.transformModel.offset.y
                onValueChanged: (v) => root.transformModel.offset.y = v
            }
        }
    }
}
