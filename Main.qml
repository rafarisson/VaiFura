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
                onTextChanged: VaiFura.drillDoc.path = text
                Component.onCompleted: text = "C:\\Users\\xpert\\Desktop\\drill_1_16.xln"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            DrillDocumentPreviewQuickItem {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.preferredHeight: 300
                document: VaiFura.drillDoc
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
                    model: VaiFura.toolListModel

                    delegate: Text {
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
                    model: VaiFura.drillListModel

                    delegate: Text {
                        required property int index
                        required property int toolId
                        required property double posX
                        required property double posY
                        text: index + ": (" + posX + "," + posY +") T" + toolId
                    }
                }

                // TreeView {
                //     Layout.fillWidth: true
                //     Layout.fillHeight: true
                //     model: toolsTreeModel
                //     delegate: CheckBox {
                //         required property string label
                //         text: label
                //     }


                //     // delegate: Item {
                //     //     id: aaa

                //     //     required property bool checked
                //     //     required property string label

                //     //     width: TreeView.view.width
                //     //     height: 28

                //     //     Row {
                //     //         spacing: 6

                //     //         CheckBox {
                //     //             checked: aaa.checked
                //     //             onToggled: aaa.checked = checked
                //     //         }

                //     //         Text {
                //     //             text: aaa.label
                //     //         }
                //     //     }
                //     // }
                // }

            }
        }
    }
}
