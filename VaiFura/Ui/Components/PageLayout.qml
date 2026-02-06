import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    default property alias content: contentWrapper.data
    property alias icon: pageHeader.icon
    property alias description: pageHeader.description

    readonly property int contentMargin: 6

    implicitWidth: Math.max(pageHeader.implicitWidth, contentWrapper.implicitWidth) + (contentMargin * 2)
    implicitHeight: pageHeader.implicitHeight + contentWrapper.implicitHeight + (contentMargin * 1)
    clip: true

    header: PageHeader {
        id: pageHeader
        title: root.title
    }

    // Component.onCompleted: {
    //     console.log(title)
    //     console.log(pageHeader.implicitWidth, pageHeader.implicitHeight, pageHeader.width, pageHeader.height)
    //     console.log(implicitWidth, implicitHeight, width, height)
    //     console.log(contentWrapper.implicitWidth, contentWrapper.implicitHeight, contentWrapper.width, contentWrapper.height)
    // }

    ColumnLayout {
        id: contentWrapper
        anchors.fill: parent
        anchors.leftMargin: root.contentMargin
        anchors.rightMargin: root.contentMargin
        anchors.bottomMargin: root.contentMargin
        clip: true
    }
}
