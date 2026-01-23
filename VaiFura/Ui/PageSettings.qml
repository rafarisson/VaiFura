import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VaiFura.Model

Page {
    id: root

    required property DrillDocumentModel documentModel

    ColumnLayout {
        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Offset x")
            }
            TextField {
                text: root.documentModel.offset.x
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Offset y")
            }
            TextField {
                text: root.documentModel.offset.y
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Avanço z")
            }
            TextField {
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Velocidade z")
            }
            TextField {
            }
        }
    }
}

// // Page {
// ScrollablePage {
//     id: root

//     contentLayout: ScrollablePage.LayoutFill

//     ColumnLayout {
//         implicitWidth: parent.width

//         RowLayout {
//             Layout.fillWidth: true

//             Label {
//                 Layout.fillWidth: true
//                 text: qsTr("Offset x:")
//             }
//             TextField {
//             }
//         }

//         RowLayout {
//             Layout.fillWidth: true

//             Label {
//                 Layout.fillWidth: true
//                 text: qsTr("Offset y:")
//             }
//             TextField {
//             }
//         }
//     }

//     // Column {
//     //     // width: 500

//     //     // clip: true
//     //     Repeater {
//     //         model: 5
//     //         Button {
//     //             required property int index
//     //             text: `Item ${index}`
//     //         }
//     //     }

//     //     Button { text: "ovo"}
//     //     Button { text: "galinha" }
//     //     Button { text: "dinossauro" }
//     //     Button { text: "dinossauro de braço curto abobado" }
//     // }
// }
