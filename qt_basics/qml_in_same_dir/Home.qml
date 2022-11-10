import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import Demo.Coms 1.0


ApplicationWindow {
    width: 600
    height: 500
    visible: true

    ColumnLayout {
        Label {
            text: "Home"
        }

        Button {
            text: "Open Dialog"
            onClicked: {
                diag.open()
            }
        }

        EditDialog {
            id: diag
        }
    }
}
