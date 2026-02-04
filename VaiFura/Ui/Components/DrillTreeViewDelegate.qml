import QtQuick
import QtQuick.Controls

TreeViewDelegate {
    id: root

    // Assigned by the TreeDocumentModel
    required property var documentModel
    required property int type
    required property real diameter
    required property real posX
    required property real posY
    required property int childCount
    required property int checkState

    property point position: Qt.point(posX + documentModel.offset.x,
                                      posY + documentModel.offset.y)

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
