import QtQuick

UnitTextField {
    id: root

    property alias textValue: root.text

    property int maxBeforeDecimal: 11
    property int maxAfterDecimal: 4
    property string _lastValidTextValue: ""

    signal valueChanged(value: double)

    validator: RegularExpressionValidator {
        readonly property string regexString: "^-?[0-9]{0,%0}[.,]?[0-9]{0,%1}$"
            .arg(root.maxBeforeDecimal)
            .arg(root.maxAfterDecimal)

        regularExpression: new RegExp(regexString)
    }

    onTextEdited: {
        if (acceptableInput) {
            _lastValidTextValue = root.textValue
            let v = Number(text.replace(",", "."))
            if (!isNaN(v) && isFinite(v))
                root.valueChanged(v)
        }
        else {
            root.text = _lastValidTextValue
        }
    }
}
