import QtQuick
import QtQuick.Controls
// import QtQuick.Controls.impl
import QtQuick.Layouts

Button {
    id: control

    property alias iconText: control.text
    property alias iconSize: control.font.pointSize
    property real iconRotation: 0

    contentItem.rotation: iconRotation

    text: MaterialSymbols.question_mark
    font.family: MaterialSymbols.fontFamily
    font.pointSize: 16

    width: 50
    Layout.preferredWidth: control.width
}

// Button {
//     id: control

//     property alias iconText: iconLabel.text
//     property alias iconSize: iconLabel.font.pointSize
//     property alias iconRotation: iconLabel.rotation

//     contentItem: IconLabel {
//         id: iconLabel

//         spacing: control.spacing
//         mirrored: control.mirrored
//         display: control.display

//         text: MaterialSymbols.question_mark
//         font.family: MaterialSymbols.fontFamily
//         font.pointSize: 16
//     }

//     width: 50
//     Layout.preferredWidth: control.width
// }
