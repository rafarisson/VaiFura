import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura
import VaiFura.Ui

ApplicationWindow {
    id: www
    width: 1200
    height: 800
    visible: true

    header: ToolBar {
        RowLayout {
            anchors {
                fill: parent
            }

            Label {
                text: MaterialIcons.fileDocument
                font.family: MaterialIcons.fontFamily
                font.pointSize: 16
            }
            Label {
                text: qsTr("Excellon file")
            }

            TextField {
                Layout.fillWidth: true
                Layout.preferredWidth: 300

                Component.onCompleted: text = "C:\\Users\\xpert\\Desktop\\drill_1_16.xln"
                onTextChanged: VaiFura.documentPath = text
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
                verticalCenter: parent.verticalCenter
            }

            Label {
                text: MaterialIcons.dotsHexagon
                font.family: MaterialIcons.fontFamily
                font.pointSize: 16
            }
            Label {
                text: qsTr("Total de furos: %1").arg(VaiFura.model.selectedHoleCount)
            }

            ToolButton {
                text: qsTr("Fit")
                onClicked: preview.fit()
            }
        }
    }
}
