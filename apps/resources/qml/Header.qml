import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: header
    height: 100
    width: parent.width
    anchors.top: parent.top
    color: "#333333"

    property url leftsource
    property url rightsource
    property bool leftvisible: true
    property bool rightvisible: true
    signal leftButtonClicked
    signal rightButtonClicked

    Button {
        id: leftButton
        visible: header.leftvisible
        width: 90
        height: 90
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5


        style: ButtonStyle {

            label: Image {
                source: header.leftsource
                fillMode: Image.PreserveAspectFit  // ensure it fits
            }
        }

        onClicked: {
            leftButtonClicked();
        }
    }

    Button {
        id: rightButton
        visible: header.rightvisible
        width: 90
        height: 90
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5

        style: ButtonStyle {

            label: Image {
                source: header.rightsource
                fillMode: Image.PreserveAspectFit  // ensure it fits
            }
        }

        onClicked: {
            rightButtonClicked();
        }
    }
}
