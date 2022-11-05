import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import com.pack 1.0

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    Calculator {
        id: calc
        textArea: info
        onTextAreaChanged: {
            console.log("calc text area changed to ", textArea)
        }
    }

    ColumnLayout {

        TextArea {
            id: info
            text: ""
            enabled: false
        }

        GridLayout  {
            columns: 3
            Button {
                text: "1"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "2"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "3"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "4"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "5"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "6"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "7"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "8"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "9"
                onClicked: { calc.Input(text) }
            }
            Label {
                
            }
            Button {
                text: "0"
                onClicked: { calc.Input(text) }
            }
            Button {
                text: "C"
                onClicked: { calc.Input(text) }
            }
        } // GridLayout
    }
}
