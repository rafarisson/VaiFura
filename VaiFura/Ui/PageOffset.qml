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
        SettingsItem {
            label: qsTr("X Offset")
            NumberTextField {
                unit: "mm"
                text: root.transformModel.offset.x
                onValueChanged: (v) => root.transformModel.offset.x = v
            }
        }
        SettingsItem {
            label: qsTr("Y Offset")
            NumberTextField {
                unit: "mm"
                text: root.transformModel.offset.y
                onValueChanged: (v) => root.transformModel.offset.y = v
            }
        }
        SettingsItem {
            label: qsTr("Rotate")
            NumberTextField {
                unit: "°"
                text: root.transformModel.rotation
                onValueChanged: (v) => root.transformModel.rotation = v
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            IconButton {
                iconText: MaterialSymbols.rotate_right
                onClicked: root.transformModel.rotation -= root.rotateInc
            }

            IconButton {
                iconText: MaterialSymbols.rotate_left
                onClicked: root.transformModel.rotation += root.rotateInc
            }

            IconButton {
                iconText: MaterialSymbols.flip
                checkable: true
                checked: root.transformModel.mirrorX
                onCheckedChanged: root.transformModel.mirrorX = checked
            }

            IconButton {
                iconText: MaterialSymbols.flip
                iconRotation: 90
                checkable: true
                checked: root.transformModel.mirrorY
                onCheckedChanged: root.transformModel.mirrorY = checked
            }
        }
    }
}
