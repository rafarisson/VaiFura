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
            // Assigned by the model
            required property var documentModel
            required property int type
            required property real diameter
            required property real posX
            required property real posY
            required property int childCount

            property point position: Qt.point(posX + documentModel.offset.x, posY + documentModel.offset.y)

            implicitWidth: treeView.width

            text: type == DrillTreeModel.ToolType
                  ? `Tool ${diameter}mm [${childCount}]`
                  : `Drill (${position.x},${posY + position.y})`
        }

        ScrollBar.vertical: ScrollBar {
            visible: true
        }
    }
}
