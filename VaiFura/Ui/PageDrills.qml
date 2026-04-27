import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

PageLayout {
    id: root

    required property DrillDocumentModel documentModel
    required property DrillTreeModel drillModel

    icon: MaterialSymbols.tools_power_drill
    title: qsTr("Tools and Holes")
    description: qsTr("Total holes selected: %1").arg(root.documentModel.selectedHoleCount)

    Label {
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        text: qsTr("No holes available")
        visible: !root.documentModel.holeCount
        opacity: 0.6
    }

    TreeView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: Math.min(contentHeight, 300)

        visible: root.documentModel.holeCount
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        reuseItems: false
        alternatingRows: false
        model: root.drillModel

        delegate: DrillTreeViewDelegate {
            text: type == DrillTreeModel.ToolType
                  ? `Tool ${diameter}mm [${childCount}]`
                  : `Drill ${positionText}`
        }

        ScrollBar.vertical: ScrollBar {
            visible: true
        }
    }
}
