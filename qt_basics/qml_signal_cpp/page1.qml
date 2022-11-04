import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import demo.switch 1.0 // registered by qmlRegisterType

Page {
    id: page1
    title: "Page 1"

    // example of signal inside QML
    signal page1CloseButtonDown()
    onPage1CloseButtonDown: () => { // process signal inside
        console.log("page1.onPage1CloseButtonDown: Close Switch")
        info.text = "Off"
        sw.state = false
    }

    signal switchStateChanged(bool state)

    ColumnLayout {

        Label {
            text: "Page 1 Anchor"
        }

        Switch { // registered by qmlRegisterType
            id: sw
            linkedText: info
            state: false
            onStateChanged: (state) => {
                console.log("sw.onStateChanged: ", sw.state)
            }
        }

        TextArea {
            id: info
            text: "Nothing Happens"
            enabled: false
        }

        Button {
            text: "Open"
            onClicked: {
                console.log("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
                console.log("Click 'Open' On Page 1")
                sw.Open() // directly call Q_INVOKABLE method
            }
        }

        Button {
            text: "Close"
            onClicked: {
                console.log("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
                console.log("Click 'Close' On Page 1")
                page1.page1CloseButtonDown() // trigger page signal inside button
            }
        }
    }

    Item {
        id: item_in_page1
        Component.onCompleted: { // Component.onCompleted only available for Item class (and child classes)
            console.log("item_in_page1.Component.onCompleted")
            sw.stateChanged.connect(page1.switchStateChanged) // connect signals here
        }
    }
}
