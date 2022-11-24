import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0
import dav.demo 1.0

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    id: root
    property int status: Status.Close

    ColumnLayout {
        Layout.fillWidth: true

        Text {
            id: t1
            text: "t1: "
        }
        Button {
            onClicked: {
                if (root.status == Status.Close) {
                    root.status = Status.Open
                    t1.text = "t1: " + root.status.toString()
                } else {
                    root.status = Status.Close
                    t1.text = "t1: " + root.status.toString()
                }
            }
        }
    }
}
