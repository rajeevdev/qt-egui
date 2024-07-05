import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "."

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 850
    flags: Qt.FramelessWindowHint

    Item {
        focus: true
        Keys.onEscapePressed: {
            Qt.quit()
        }
    }

    StackView {
        id: stack
        initialItem: mainPage
        anchors.fill: parent

        delegate: StackViewDelegate {
            function transitionFinished(properties)
            {
                properties.exitItem.opacity = 1
            }

            pushTransition: StackViewTransition {
                PropertyAnimation {
                    target: enterItem
                    property: "opacity"
                    from: 0
                    to: 1
                }
                PropertyAnimation {
                    target: exitItem
                    property: "opacity"
                    from: 1
                    to: 0
                }
            }
        }
    }

    Component
    {
        id: mainPage
        Item {
            Header {
                leftsource: "qrc:/images/settings-150.png"
                rightsource: "qrc:/images/close-150.png"
                onLeftButtonClicked: {
                    stack.push(settingsPage);
                }
                onRightButtonClicked: {
                    Qt.quit();
                }
            }


            Clock {

            }

            Footer {

            }
        }
    }

    Component
    {
        id: settingsPage
        Item {
            Header {
                leftvisible: false
                rightsource: "qrc:/images/close-150.png"
                onRightButtonClicked: {
                    stack.pop();
                }
            }

            WirelessSettings {

            }

            Footer {

            }

        }


    }



//    Image {
//        source: "assets/settings-150.png"
//        width: 50
//        height: 50
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//               console.info("image clicked!")
//            }
//        }
//    }
}
