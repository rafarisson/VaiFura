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
            SplitView.fillHeight: true

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
                Layout.fillWidth: true
                Layout.fillHeight: true
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
            SplitView.fillHeight: true

            PageOffset {
                Layout.fillWidth: true
                documentModel: VaiFura.model
            }

            PageExport {
                Layout.fillWidth: true
                documentModel: VaiFura.model
                exportSettingsModel: VaiFura.exportSettingsModel
            }
        }
    }
}
