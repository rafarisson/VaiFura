import QtQuick
import QtQuick.Controls

import VaiFura
import VaiFura.Ui

ApplicationWindow {
    width: 1200
    height: 800
    visible: true

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        ScrollableColumnLayout {
            SplitView.fillHeight: true
            SplitView.preferredWidth: 300

            PageUpload {
                drillFileName: VaiFura.drillDocumentFileName
                profileFileName: VaiFura.profileDocumentFileName
                onDrillFileSelected: (fn) => VaiFura.drillDocumentFileName = fn
                onProfileFileSelected: (fn) => VaiFura.profileDocumentFileName = fn
            }

            PageDrills {
                documentModel: VaiFura.model
                drillModel: VaiFura.drillsModel
            }

            PageOffset {
                transformModel: VaiFura.transformModel
            }
        }

        Preview {
            SplitView.fillWidth: true
            SplitView.fillHeight: true

            documentModel: VaiFura.model
            transformModel: VaiFura.transformModel
            optimizationModel: VaiFura.optimizationModel
        }

        ScrollableColumnLayout {
            SplitView.fillHeight: true
            SplitView.preferredWidth: 300

            PageMachine {
                settingsModel: VaiFura.machineSettingsModel
            }

            PageOptimization {
                documentModel: VaiFura.model
                drillModel: VaiFura.drillsModel
            }

            PageExport {
                documentModel: VaiFura.model
                settingsModel: VaiFura.settingsModel
                onSaveRequest: (path) => VaiFura.save(path)
            }
        }
    }
}
