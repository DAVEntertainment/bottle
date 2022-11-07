import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import demo.sig 1.0


ApplicationWindow {
    width: 600
    height: 500
    visible: true

    SignalSource {
        id: sig_src
    }

    ColumnLayout {
        Label {
            id: label
            text: "Start: "
            function onWalk() { // signal handler
                if (text.length > 10) {
                    text = ""
                }
                text += "+"
            }
        }
    }

    Item {
        id: item_in_app
        Component.onCompleted: { // Component.onCompleted only available for Item class (and child classes)
            console.log("item_in_app.Component.onCompleted")
            sig_src.walkOneStep.connect(label.onWalk) // connect C++ signal to label
        }
    }
}
