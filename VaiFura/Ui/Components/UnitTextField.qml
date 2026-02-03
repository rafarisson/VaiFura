import QtQuick
import QtQuick.Controls

TextField {
    id: root

    property alias unit: unitLabel.text

    property int maxBeforeDecimal: 11
    property int maxAfterDecimal: 4

    signal valueChanged(value: double)

    Label {
        id: unitLabel

        anchors {
            right: parent.right
            rightMargin: parent.leftPadding
            verticalCenter: parent.verticalCenter
        }

        visible: text !== ""
        textFormat: Text.PlainText
    }

    validator: RegularExpressionValidator {
        readonly property string regexString: "^-?[0-9]{0,%0}[.,]?[0-9]{0,%1}$"
            .arg(root.maxBeforeDecimal)
            .arg(root.maxAfterDecimal)

        regularExpression: new RegExp(regexString)
    }

    onTextEdited: {
        if (!text)
            return;
        let v = Number(text)
        if (isNaN(v))
            return;
        root.valueChanged(v)
    }
}
