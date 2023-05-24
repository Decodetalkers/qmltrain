import QtQuick
import QtQuick.Controls

Page {
    id: page

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Repeater {
            model: 3

            Pane {
                width: swipeView.width
                height: swipeView.height

                Column {
                    spacing: 40
                    width: parent.width

                    Label {
                        width: parent.width
                        wrapMode: Label.Wrap
                        horizontalAlignment: Qt.AlignHCenter
                        text: "TabBar is a bar with icons or text which allows the user "
                              + "to switch between different subtasks, views, or modes."
                    }

                    Image {
                        source: "qrc:/images/arrows.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: "First"
        }
        TabButton {
            text: "Second"
        }
        TabButton {
            text: "Third"
        }
    }
}
