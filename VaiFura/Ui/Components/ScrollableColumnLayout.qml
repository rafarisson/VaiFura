import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Flickable {
    id: root

    default property alias editor: layout.data

    contentHeight: layout.implicitHeight
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    ColumnLayout {
        id: layout

        width: root.width
    }

    ScrollBar.vertical: ScrollBar { }
}