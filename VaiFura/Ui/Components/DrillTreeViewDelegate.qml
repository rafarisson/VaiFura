import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.TreeViewDelegate {
    id: control

    implicitWidth: leftMargin + __contentIndent + implicitContentWidth + rightPadding + rightMargin
    implicitHeight: Math.max(indicator ? indicator.height : 0, implicitContentHeight) * 1.25

    indentation: indicator ? indicator.width : 12
    leftMargin: 4
    rightMargin: 4
    spacing: 4

    topPadding: contentItem ? (height - contentItem.implicitHeight) / 2 : 0
    leftPadding: !mirrored ? leftMargin + __contentIndent : width - leftMargin - __contentIndent - implicitContentWidth


    highlighted: control.selected || control.current
               || ((control.treeView.selectionBehavior === TableView.SelectRows
               || control.treeView.selectionBehavior === TableView.SelectionDisabled)
               && control.row === control.treeView.currentRow)

    // Assigned to by TreeView
    required property int row
    required property var model

    // Assigned by the DrillTreeModel
    required property int checkState



    readonly property real __contentIndent: !isTreeNode ? 0 : (depth * indentation) + (indicator ? indicator.width + spacing : 0)

    indicator: Item {
        // Create an area that is big enough for the user to
        // click on, since the image is a bit small.
        readonly property real __indicatorIndent: control.leftMargin + (control.depth * control.indentation)
        x: !control.mirrored ? __indicatorIndent : control.width - __indicatorIndent - width
        y: (control.height - height) / 2
        implicitWidth: 20
        implicitHeight: 40 // same as Button.qml
        ColorImage {
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            rotation:  control.expanded ? 90 : (control.mirrored ? 180 : 0)
            source: "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/arrow-indicator.png"
            color: control.palette.windowText
            defaultColor: "#353637"
        }
    }

    background: Rectangle {
        implicitHeight: 40 // same as Button.qml
        border.color: control.current ? control.palette.highlight : control.palette.windowText
        border.width: Qt.styleHints.accessibility.contrastPreference !== Qt.HighContrast ? 0 :
                      control.current ? 2 : 1
        color: control.highlighted
               ? control.palette.highlight
               : (control.treeView.alternatingRows && control.row % 2 !== 0
               ? control.palette.alternateBase : control.palette.base)
    }

    contentItem: CheckBox {
        text: control.text
        tristate: control.hasChildren
        checkState: control.checkState
        nextCheckState: function() {
            return checkState === Qt.Checked ? Qt.Unchecked : Qt.Checked
        }
        onCheckStateChanged: if (control.model.checkState != checkState) control.model.checkState = checkState
    }
}
