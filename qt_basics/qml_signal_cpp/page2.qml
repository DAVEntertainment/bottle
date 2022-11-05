import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import demo.waker 1.0

Page {
    id: page2
    title: "Page 2"

    signal footChanged(bool left)
    signal needChangeFoot(bool left)
    onNeedChangeFoot: (left) => {
        console.log("page2.onNeedChangeFoot: Change foot to", left ? "left": "right")
        wk.leftFoot = left
    }

    ColumnLayout {

        Label {
            text: "Page 2 Anchor"
        }
        
        Waker {
            id: wk
            linkedText: output
            leftFoot: true
        }

        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                wk.WalkOneStep()
            }
        }

        TextArea {
            id: output
            text: "Start Walk:"
            enabled: false
        }

        Button {
            text: "Toggle Foot"
            onClicked: {
                console.log("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
                console.log("Click 'Toggle Foot' On Page 2")
                wk.leftFoot = !wk.leftFoot
            }
        }
    }

    Item {
        id: item_in_page2
        Component.onCompleted: { // Component.onCompleted only available for Item/Component class
            console.log("item_in_page2.Component.onCompleted")
            wk.leftFootChanged.connect(footChanged)
        }
    }
}
