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
                fileName: VaiFura.documentFileName
                onFileSelected: (fn) => VaiFura.documentFileName = fn
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
            transformModel: VaiFura.transformModel
        }

        ColumnLayout {
            SplitView.fillHeight: true
            SplitView.preferredWidth: 300

            PageOffset {
                transformModel: VaiFura.transformModel
            }

            PageExport {
                documentModel: VaiFura.model
                settingsModel: VaiFura.settingsModel
                onSaveRequest: (path) => VaiFura.save(path)
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
}
