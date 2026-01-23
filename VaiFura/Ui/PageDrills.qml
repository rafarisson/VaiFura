import QtQuick
import QtQuick.Controls

import VaiFura.Model

Page {
    id: root

    required property DrillTreeModel drillModel

    TreeView {
        id: drillTree

        anchors.fill: parent

        boundsBehavior: Flickable.StopAtBounds
        clip: true
        reuseItems: false
        alternatingRows: false
        model: root.drillModel

        delegate: DrillTreeViewDelegate {
            text: type == DrillTreeModel.ToolType
                  ? `Tool ${diameter}mm [${childCount}]`
                  : `Drill (${position.x},${posY + position.y})`
        }

        ScrollBar.vertical: ScrollBar {
            visible: true
        }
    }
}
