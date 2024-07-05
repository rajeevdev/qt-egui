import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: wirelessSettings
    width: 600
    height: 600
    anchors.centerIn: parent

    ListModel {
        id: wirelessModel
        ListElement {
            name: "RISHITATANISHI"
        }
        ListElement {
            name: "Rajeev"
        }
        ListElement {
            name: "Jio"
        }
    }

    ListView {
        anchors.fill: parent
        model: wirelessModel
        spacing: 10
        delegate: Rectangle {
            height: 70
            width: 650
            color: "grey"
            Text {
                text: name
                font.pixelSize: 50
            }
        }
    }
}
