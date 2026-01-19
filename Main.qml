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
            Label {
                text: qsTr("Offset X:")
            }
            TextField {
                text: VaiFura.model.offset.x
                validator: DoubleValidator {
                    bottom: 0
                    notation: DoubleValidator.StandardNotation
                }
                onTextChanged: if (acceptableInput)
                                   VaiFura.model.offset = Qt.point(parseFloat(text), VaiFura.model.offset.y)
            }

            Label {
                text: qsTr("Offset Y:")
            }
            TextField {
                text: VaiFura.model.offset.y
                validator: DoubleValidator {
                    bottom: 0
                    notation: DoubleValidator.StandardNotation
                }
                onTextChanged: {
                    let v = parseFloat(text)
                    if (!isNaN(v))
                        VaiFura.model.offset = Qt.point(VaiFura.model.offset.x, v)
                }
            }
        }

        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                text: qsTr("a")
                Layout.fillHeight: true
            }

            Preview {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 300
                Layout.preferredWidth: 100
                doc: VaiFura.model
            }

            Button {
                text: VaiFura.model.selectedHoleCount
                Layout.fillHeight: true
            }


            TreeView {
                id: drillsTreeView

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 50

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

                    property point offset: VaiFura.model.offset

                    text: type == DrillTreeModel.ToolType
                          ? `Tool ${diameter}mm [${childCount}]`
                          : `Drill (${posX + offset.x},${posY + offset.y})`
                }

                ScrollBar.vertical: ScrollBar {
                    visible: true
                }
            }
        }

        Button {
            text: qsTr("test")
        }
    }

    Connections {
        function onDocumentPathChanged() {
            // Qt.callLater(drillsTreeView.expandRecursively);
        }

        target: VaiFura
    }
}
