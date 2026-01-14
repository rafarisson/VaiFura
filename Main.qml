import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import libmodel
import libview
import VaiFura

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {

        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            TextField {
                Layout.fillWidth: true
                onTextChanged: VaiFura.documentPath = text
                Component.onCompleted: text = "C:\\Users\\xpert\\Desktop\\drill_1_16.xln"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            DrillDocumentPreview {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.preferredHeight: 300
                model: VaiFura.model
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Label {
                    text: qsTr("Tools:")
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    clip: true
                    model: VaiFura.toolsModel

                    delegate: Text {
                        // Assigned by the model
                        required property int id
                        required property double diameter

                        text: id + ": (" + diameter + ")"
                    }
                }

                Label {
                    text: qsTr("Drills:")
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    clip: true
                    model: VaiFura.holesModel

                    delegate: Text {
                        // Assigned by the model
                        required property int index
                        required property int toolId
                        required property double posX
                        required property double posY

                        text: index + ": (" + posX + "," + posY +") T" + toolId
                    }
                }
            }

            TreeView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.preferredHeight: 300

                clip: true
                model: VaiFura.drillsModel
                selectionMode: TreeView.SingleSelection

                delegate: Row {
                    id: itemDelegate

                    readonly property real indentation: 20

                    // Assigned by the model
                    required property int itemType
                    required property real diameter
                    required property real posX
                    required property real posY
                    required property int childCount

                    // Assigned to by TreeView:
                    required property TreeView treeView
                    required property bool isTreeNode
                    required property bool expanded
                    required property int hasChildren
                    required property int depth
                    required property int row
                    required property int column
                    required property bool current

                    // implicitWidth: treeView.width
                    // implicitHeight: checkBox.implicitHeight

                    // Item {
                    //     width: l.width
                    //     height: 1
                    // }

                    // Label {
                    //     id: l
                    //     visible: itemDelegate.hasChildren
                    //     text: itemDelegate.expanded ? "+++" : "---"
                    //     TapHandler {
                    //         onSingleTapped: itemDelegate.treeView.toggleExpanded(itemDelegate.row)
                    //     }
                    // }

                    // CheckBox {
                    //     tristate: true
                    //     text: itemDelegate.itemType == DrillTreeModel.ToolType
                    //           ? `Tool ${itemDelegate.diameter}mm [${itemDelegate.childCount}]`
                    //           : `Drill (${itemDelegate.posX},${itemDelegate.posY})`
                    // }

                    // property Animation indicatorAnimation: NumberAnimation {
                    //     target: indicator
                    //     property: "rotation"
                    //     from: itemDelegate.expanded ? 0 : 90
                    //     to: itemDelegate.expanded ? 90 : 0
                    //     duration: 100
                    //     easing.type: Easing.OutQuart
                    // }
                    // TableView.onPooled: indicatorAnimation.complete()
                    // TableView.onReused: if (current) indicatorAnimation.start()
                    // onExpandedChanged: indicator.rotation = expanded ? 90 : 0

                    Label {
                        id: indicator

                        visible: itemDelegate.isTreeNode && itemDelegate.hasChildren
                        text: ">"

                        TapHandler {
                            onSingleTapped: {
                                // let index = itemDelegate.treeView.index(itemDelegate.row, itemDelegate.column)
                                // treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                                itemDelegate.treeView.toggleExpanded(itemDelegate.row)
                            }
                        }
                    }

                    Item {
                        visible: itemDelegate.depth
                        // width: indicator.implicitWidth * 1.2
                        width: itemDelegate.indentation * itemDelegate.depth + itemDelegate.spacing
                        height: 1
                    }

                    CheckBox {
                        id: checkBox
                        anchors.leftMargin: itemDelegate.depth  * 20
                        text: itemDelegate.itemType == DrillTreeModel.ToolType
                              ? `Tool ${itemDelegate.diameter}mm [${itemDelegate.childCount}]`
                              : `Drill (${itemDelegate.posX},${itemDelegate.posY})`
                    }
                }
            }
        }
    }
}
