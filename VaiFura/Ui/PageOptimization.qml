import QtQuick
import QtQuick.Controls

import VaiFura.Model

PageLayout {
    id: root

    required property OptimizationModel optimizationModel

    property alias showPath: showPathChecbox.checked
    property alias showOrder: showOrderChecbox.checked

    icon: MaterialSymbols.route
    title: qsTr("Optimization")
    description: qsTr("Optimize drilling path and preview behavior")

    SettingsItem {
        label: qsTr("Mode")
        ComboBox {
            implicitContentWidthPolicy: ComboBox.WidestTextWhenCompleted

            model: root.optimizationModel.availablePlans
            onCurrentIndexChanged: root.optimizationModel.currentPlanIndex = currentIndex
        }
    }

    SettingsItem {
        label: qsTr("Show path")
        description: qsTr("Display the tool movement path between holes");
        CheckBox {
            id: showPathChecbox

            spacing: 0
            rightPadding: 0
            checked: true
        }
    }

    SettingsItem {
        label: qsTr("Show order")
        description: qsTr("Display drilling sequence numbers on each hole");
        CheckBox {
            id: showOrderChecbox

            spacing: 0
            rightPadding: 0
            checked: true
        }
    }
}
