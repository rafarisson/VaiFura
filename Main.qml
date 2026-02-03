import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura
import VaiFura.Ui

ApplicationWindow {
    width: 1200
    height: 800
    visible: true

    header: ToolBar {
        RowLayout {
            anchors {
                fill: parent
                leftMargin: 12
                rightMargin: 12
            }

            Label {
                text: MaterialSymbols.file_open
                font.family: MaterialSymbols.fontFamily
                font.pointSize: 16
            }
            Label {
                text: qsTr("Excellon file")
            }

            TextField {
                Layout.preferredWidth: 300

                text: VaiFura.documentPath
                onTextEdited: VaiFura.documentPath = text
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6

        ColumnLayout {
            Layout.fillHeight: true
            Layout.preferredWidth: 50

            TabBar {
                id: tab

                Layout.fillWidth: true

                TabButton {
                    text: qsTr("Drills")
                }

                TabButton {
                    text: qsTr("Settings")
                }
            }

            StackLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                currentIndex: tab.currentIndex

                PageDrills {
                    drillModel: VaiFura.drillsModel
                }

                PageSettings {
                    documentModel: VaiFura.model
                }
            }
        }

        Preview {
            id: preview
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            Layout.preferredWidth: 100
            documentModel: VaiFura.model
        }
    }

    footer: ToolBar {
        RowLayout {
            anchors {
                fill: parent
                leftMargin: 12
                rightMargin: 12
            }

            Label {
                text: MaterialSymbols.tools_power_drill
                font.family: MaterialSymbols.fontFamily
                font.pointSize: 16
            }
            Label {
                text: qsTr("Total de furos: %1").arg(VaiFura.model.selectedHoleCount)
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }
}
