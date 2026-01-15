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

                Component.onCompleted: text = "C:\\Users\\xpert\\Desktop\\drill_1_16.xln"
                onTextChanged: VaiFura.documentPath = text
            }
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            DrillDocumentPreview {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 300
                Layout.preferredWidth: 100

                model: VaiFura.model
            }

            ColumnLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    text: qsTr("Tools (%1):").arg(toolsListView.count)
                }

                ListView {
                    id: toolsListView

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    model: VaiFura.toolsModel

                    delegate: Text {
                        required property int id
                        required property real diameter

                        text: id + ": (" + diameter + ")"
                    }

                    ScrollBar.vertical: ScrollBar {
                        visible: true
                    }
                }

                Label {
                    text: qsTr("Holes (%1):").arg(holesListView.count)
                }

                ListView {
                    id: holesListView

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    model: VaiFura.holesModel

                    delegate: Text {
                        required property int index
                        required property int toolId
                        required property real posX
                        required property real posY

                        text: index + ": (" + posX + "," + posY + ") T" + toolId
                    }

                    ScrollBar.vertical: ScrollBar {
                        visible: true
                    }
                }
            }


            TreeView {
                id: drillsTreeView

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 300
                Layout.preferredWidth: 100

                boundsBehavior: Flickable.StopAtBounds
                clip: true
                reuseItems: false
                alternatingRows: false
                model: VaiFura.drillsModel

                delegate: DrillTreeViewDelegate {
                    // Assigned by the model
                    required property int type
                    required property real diameter
                    required property real posX
                    required property real posY
                    required property int childCount
                    required property bool isChecked

                    checked: isChecked
                    text: type == DrillTreeModel.ToolType
                          ? `Tool ${diameter}mm [${childCount}]`
                          : `Drill (${posX},${posY})`

                    onCheckedChanged: if (isChecked != checked) model.isChecked = checked
                }

                ScrollBar.vertical: ScrollBar {
                    visible: true
                }
            }
        }
    }

    Connections {
        function onDocumentPathChanged() {
            Qt.callLater(drillsTreeView.expandRecursively);
        }

        target: VaiFura
    }
}
