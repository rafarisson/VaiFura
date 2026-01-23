import QtQuick
import QtQuick.Controls

Page {
    id: root

    enum ContentLayout {
        LayoutNormal,
        LayoutFill,
        LayoutCenter
    }

    default property alias content: container.data
    property int contentLayout: ScrollablePage.LayoutNormal

    Flickable {
        id: flickable

        anchors.fill: parent

        boundsBehavior: Flickable.StopAtBounds
        clip: true

        contentWidth: root.contentLayout !== ScrollablePage.LayoutFill
                      ? Math.max(parent.width, container.width)
                      : container.width
        contentHeight: container.height

        ScrollIndicator.vertical: ScrollIndicator { }
        ScrollIndicator.horizontal: ScrollIndicator { }

        Item {
            id: container

            anchors.top: parent.top
            anchors.left: root.contentLayout === ScrollablePage.LayoutCenter ? undefined : parent.left
            anchors.horizontalCenter: root.contentLayout === ScrollablePage.LayoutCenter ? parent.horizontalCenter : undefined

            implicitWidth: root.contentLayout !== ScrollablePage.LayoutFill
                           ? childrenRect.width
                           : Math.max(root.width, childrenRect.width)
            implicitHeight: childrenRect.height

            clip: true
        }
    }

    // // PAGE
    // Rectangle {
    //     anchors.fill: parent
    //     color: "transparent"
    //     border.color: "red"
    //     border.width: 4
    //     z: 500
    // }

    // // FLICKABLE CONTENT
    // Rectangle {
    //     anchors.horizontalCenter: root.contentLayout === ScrollablePage.LayoutCenter
    //                               ? flickable.horizontalCenter
    //                               : undefined
    //     width: flickable.contentWidth
    //     height: flickable.contentHeight
    //     color: "transparent"
    //     border.color: "blue"
    //     border.width: 2
    //     z: 900
    // }

    // // CONTENT
    // Rectangle {
    //     x: container.x
    //     y: container.y
    //     width: container.width
    //     height: container.height
    //     color: "transparent"
    //     border.color: "olive"
    //     border.width: 2
    //     z: 800
    // }
}
