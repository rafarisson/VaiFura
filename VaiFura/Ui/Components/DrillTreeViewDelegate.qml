import QtQuick
import QtQuick.Controls

TreeViewDelegate {
    id: root

    // Assigned by the TreeDocumentModel
    required property var documentModel
    required property var transformModel
    required property int type
    required property real diameter
    required property real posX
    required property real posY
    required property int childCount
    required property int checkState

    property int precision: 4
    readonly property point position: Qt.point(posX, posY)
    readonly property string positionText: formatPosition(position.x, position.y)

    function formatPosition(x: real, y: real) : string {
        return `(${x.toFixed(precision)}, ${y.toFixed(precision)})`
    }

    implicitHeight: 50
    implicitWidth: treeView.width

    contentItem: CheckBox {
        text: root.text
        tristate: root.hasChildren
        checkState: root.checkState
        nextCheckState: function() {
            return checkState === Qt.Checked ? Qt.Unchecked : Qt.Checked
        }
        onCheckStateChanged: {
            if (root.checkState != checkState)
                root.model.checkState = checkState
        }
    }
}
