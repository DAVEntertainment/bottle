import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    Button {
        width: 200
        height: 50
        onClicked: {
            fd.folder = "file:///d:"
            fd.open()
        }
    }

    FileDialog {
        id: fd
        title: "Select A Path"
        selectFolder: true
        sidebarVisible: true
        onAccepted: {
            console.log("Choosing", fd.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
    }
}
