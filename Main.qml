import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura
import VaiFura.Ui

ApplicationWindow {
    width: 1200
    height: 800
    visible: true

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        ColumnLayout {
            PageLayout {
                icon: MaterialSymbols.upload
                title: qsTr("Excellon file")
                description: qsTr("Select drill file (.xln, .drl or .txt)")

                RowLayout {
                    Button {
                        text: qsTr("Select file")
                    }
                    TextField {
                        Layout.fillWidth: true
                        text: VaiFura.documentPath
                        onTextEdited: VaiFura.documentPath = text
                    }
                }
            }

            PageDrills {
                documentModel: VaiFura.model
                drillModel: VaiFura.drillsModel
            }
        }

        Preview {
            SplitView.fillWidth: true
            SplitView.fillHeight: true
            documentModel: VaiFura.model
        }

        ColumnLayout {
            PageSettings {
                documentModel: VaiFura.model
            }

            PageLayout {
                icon: MaterialSymbols.download
                title: qsTr("G-Code file")
                description: qsTr("Export g-code file (.gcode)")

                Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Export")
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
}
