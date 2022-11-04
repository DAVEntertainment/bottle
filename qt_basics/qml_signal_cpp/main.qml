import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import demo.page1 1.0
import demo.page2 1.0

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    header: Label {
        id: app_header
        text: view.currentItem.title + " / 2"
        horizontalAlignment: Text.AlignHCenter
    }

    SwipeView { /* swipe with finger or mouse to see next page */
        id: view
        anchors.fill: parent

        function onPage1SwitchStateChanged(state) { // define function to process
            console.log("view.onPage1SwitchStateChanged:", state, "@", app_header.text)
        }

        Page1 {
            id: page1_in_view
            onPage1CloseButtonDown: () => { // process signal outside
                console.log("page1_in_view.onPage1CloseButtonDown @", app_header.text)
                page2_in_view.needChangeFoot(false);
            }
        }

        Page2 {
            id: page2_in_view
            onFootChanged: (left) => { // process signal outside
                console.log("page2_in_view.onFootChanged:", left, "@", app_header.text)
            }
        }

        Item {
            id: item_in_view
            Component.onCompleted: () => { // Component.onCompleted only available for Item/Component class
                console.log("item_in_view.Component.onCompleted")
                page1_in_view.switchStateChanged.connect(view.onPage1SwitchStateChanged)
            }
        }
    }
}
