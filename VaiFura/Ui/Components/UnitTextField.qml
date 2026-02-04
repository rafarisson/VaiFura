import QtQuick
import QtQuick.Controls

TextField {
    id: root

    property alias unit: unitLabel.text

    property int maxBeforeDecimal: 11
    property int maxAfterDecimal: 4
    property string _lastValidText: ""

    signal valueChanged(value: double)

    implicitWidth: 150

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
        if (acceptableInput) {
            _lastValidText = text
            let v = Number(text.replace(",", "."))
            if (!isNaN(v) && isFinite(v))
                root.valueChanged(v)
        } else {
            text = _lastValidText
        }
    }
}
