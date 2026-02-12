import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillTransformModel transformModel
    readonly property real rotateInc: 45

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

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Rotate")
            }

            NumberTextField {
                unit: "°"
                text: root.transformModel.rotation
                onValueChanged: (v) => root.transformModel.rotation = v
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            IconButton {
                property real current: root.transformModel.rotation

                iconText: MaterialSymbols.rotate_right
                onClicked: root.transformModel.rotation = current + root.rotateInc
            }

            IconButton {
                property real current: root.transformModel.rotation

                iconText: MaterialSymbols.rotate_left
                onClicked: root.transformModel.rotation = current - root.rotateInc
            }

            IconButton {
                property bool current: root.transformModel.mirrorX

                iconText: MaterialSymbols.flip
                onClicked: root.transformModel.mirrorX = !current
            }

            IconButton {
                property bool current: root.transformModel.mirrorY

                iconText: MaterialSymbols.flip
                iconRotation: 90
                onClicked: root.transformModel.mirrorY = !current
            }
        }
    }
}
