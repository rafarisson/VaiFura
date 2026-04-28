import QtQuick
import QtQuick.Controls

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property DrillTreeModel drillModel

    property int optimizationMode: 0
    property bool showPath: true
    property bool showOrder: true

    icon: MaterialSymbols.route
    title: qsTr("Optimization")
    description: qsTr("Optimize drilling path and preview behavior")

    SettingsItem {
        label: qsTr("Mode")
        ComboBox {
            implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted

            model: [
                "Nearest Neighbor (fast)",
                "Original order (no optimization)"
            ]
        }
    }

    SettingsItem {
        label: qsTr("Show path")
        description: qsTr("Display the tool movement path between holes");
        CheckBox {
            spacing: 0
            rightPadding: 0
        }
    }

    SettingsItem {
        label: qsTr("Show order")
        description: qsTr("Display drilling sequence numbers on each hole");
        CheckBox {
            spacing: 0
            rightPadding: 0
        }
    }
}
