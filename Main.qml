import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura
import VaiFura.Ui

ApplicationWindow {
    width: 1200
    height: 800
    visible: true

    header: ToolBar {
        RowLayout {
            Label {
                text: qsTr("Excellon file:")
            }

            TextField {
                Layout.fillWidth: true
                Layout.preferredWidth: 300

                Component.onCompleted: text = "C:\\Users\\xpert\\Desktop\\drill_1_16.xln"
                onTextChanged: VaiFura.documentPath = text
            }

            // Label { text: "Offset X:" }
            // SpinBox { }
            // Label { text: "Offset Y:" }
            // SpinBox { }
            // Button { text: "Exportar" }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6

        ColumnLayout {
            Layout.fillHeight: true
            Layout.preferredWidth: 50

            TabBar {
                id: tab

                Layout.fillWidth: true

                TabButton {
                    text: qsTr("Drills")
                }

                TabButton {
                    text: qsTr("Settings")
                }
            }

            StackLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

                currentIndex: tab.currentIndex

                PageDrills {
                    drillModel: VaiFura.drillsModel
                }

                PageSettings {
                    documentModel: VaiFura.model
                }
            }
        }

        Preview {
            id: preview
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 300
            Layout.preferredWidth: 100
            doc: VaiFura.model
        }
    }
}


// ApplicationWindow {
//     width: 640
//     height: 480
//     visible: true
//     title: qsTr("Hello World")

//     header: ToolBar {
//         ToolButton {
//             text: qsTr("A")
//             onClicked: toolsDrawer.open()
//         }
//     }

//     Drawer {
//         id: toolsDrawer
//         // y: header.height
//         // width: window.width * 0.6
//         // height: window.height - header.height
//         // edge: Qt.RightEdge
//         // width: 320

//         ColumnLayout {
//             anchors.fill: parent
//             // deslocamento cima/baixo + velocidade
//             Repeater {
//                 model: 10
//                 RowLayout {
//                     Layout.fillWidth: true

//                     Label {
//                         text: qsTr("Velocidade")
//                     }
//                     TextField {
//                         Layout.fillWidth: true
//                     }
//                 }
//             }
//         }
//     }

//     PreviewPage {
//         anchors.fill: parent
//     }

//     // ColumnLayout {
//     //     anchors.fill: parent

//     //     TabBar {
//     //         Layout.fillWidth: true

//     //         TabButton {
//     //             text: qsTr("Home");
//     //             // onClicked: stackView.push()
//     //         }
//     //         TabButton {
//     //             text: qsTr("Configurações");
//     //             // onClicked: stackView.pop()
//     //         }
//     //     }

//     //     // StackView {
//     //     //     id: stackView

//     //     //     Layout.fillWidth: true
//     //     //     Layout.fillHeight: true

//     //     //     PreviewPage { }
//     //     //     SettingsPage { }
//     //     // }
//     // }
// }
