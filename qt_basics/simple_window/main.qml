import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    width: 400
    height: 500
    visible: true

    RoundButton {
        text: "+"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
