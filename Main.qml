// pragma ComponentBehavior: Bound

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
                reuseItems: false

                delegate: Row {
                    id: itemDelegate

                    readonly property real indentation: 20

                    // Assigned by the model
                    required property int type
                    required property real diameter
                    required property real posX
                    required property real posY
                    required property int childCount
                    required property bool isChecked

                    // Assigned to by TreeView:
                    required property TreeView treeView
                    required property bool isTreeNode
                    required property bool expanded
                    required property int hasChildren
                    required property int depth
                    required property int row
                    required property int column
                    required property bool current

                    Label {
                        id: indicator

                        visible: itemDelegate.isTreeNode && itemDelegate.hasChildren
                        text: ">"

                        TapHandler {
                            onSingleTapped: {
                                // let index = itemDelegate.treeView.index(itemDelegate.row, itemDelegate.column)
                                // itemDelegate.treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
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
                        text: itemDelegate.type == DrillTreeModel.ToolType
                              ? `Tool ${itemDelegate.diameter}mm [${itemDelegate.childCount}]`
                              : `Drill (${itemDelegate.posX},${itemDelegate.posY})`
                        checked: itemDelegate.isChecked
                        onToggled: {
                            let old = itemDelegate.isChecked
                            itemDelegate.isChecked = checkBox.checked
                            console.log("toggle", old, itemDelegate.isChecked, checkBox.checked)
                        }
                    }
                }

                Component.onCompleted: Qt.callLater(expandRecursively)
            }
        }
    }
}
