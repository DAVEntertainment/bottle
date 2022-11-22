import QtQuick 2.11
import QtQuick.Controls 2.15
import com.pack 1.0

ApplicationWindow {
    width: 600
    height: 500
    visible: true

    Demo {
        id: demo
    }

    Button {
        width: 200
        height: 50
        onClicked: {
            demo.changed()
        }
    }
}
