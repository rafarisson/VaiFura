import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property ExportSettingsListModel exportSettingsModel

    icon: MaterialSymbols.download
    title: qsTr("G-Code file")
    description: qsTr("Export g-code file (.gcode)")

    ColumnLayout {
        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 300
            Layout.preferredHeight: 200

            boundsBehavior: Flickable.StopAtBounds
            clip: true
            model: root.exportSettingsModel
            visible: root.exportSettingsModel.size

            delegate: Item {
                id: itemDelegate

                required property var model
                required property string label
                required property string description
                required property string unit
                required property var value

                width: ListView.view.width
                implicitHeight: itemLayout.implicitHeight

                RowLayout {
                    id: itemLayout
                    anchors.fill: parent
                    Label {
                        Layout.fillWidth: true
                        text: itemDelegate.label
                    }
                    HelpToolTip {
                        help: itemDelegate.description
                    }
                    UnitTextField {
                        unit: itemDelegate.unit
                        text: itemDelegate.value
                        onValueChanged: (v) => itemDelegate.model.value = v
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                visible: true
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Export")
        }
    }
}
