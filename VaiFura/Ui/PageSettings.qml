import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel

    icon: MaterialSymbols.settings
    title: qsTr("Export Settings")

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

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Safe Z Height")
            }
            UnitTextField {
                unit: "mm"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Drilling Depth")
            }
            UnitTextField {
                unit: "mm"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Drilling Feed Rate")
            }
            UnitTextField {
                unit: "mm/min"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Retract Height")
            }
            UnitTextField {
                unit: "mm"
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Retract Feed Rate")
            }
            UnitTextField {
                unit: "mm/min"
            }
        }
    }
}
