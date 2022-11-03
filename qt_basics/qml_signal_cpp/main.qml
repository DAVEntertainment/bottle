import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import demo.calc 1.0 // defined by qmlRegisterType

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    Switch {
        id: calc
        linkedText: info
    }

    ColumnLayout {

        TextArea {
            id: info
            text: "Nothing Happens"
            enabled: false
        }

        GridLayout  {
            columns: 2
            Button {
                text: "Open"
                onClicked: { calc.Open() }
            }
            Button {
                text: "Close"
                onClicked: { calc.Close() }
            }
        }
    }
}
