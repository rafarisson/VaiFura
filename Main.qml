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
            SplitView.preferredWidth: 300

            PageUpload {
                path: VaiFura.documentPath
                onPathChanged: VaiFura.documentPath = path
            }

            PageDrills {
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
            SplitView.preferredWidth: 300

            PageOffset {
                documentModel: VaiFura.model
            }

            PageSettings {
                documentModel: VaiFura.model
                exportSettingsModel: VaiFura.exportSettingsModel
            }

            PageExport {
                documentModel: VaiFura.model
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
}
