import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Command.Base 1.0

Page {
    id: page

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Repeater {
            model: StyleSettings.subscribes

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

                    Button {
                        text: "Add subScribe"
                        onClicked: {
                            StyleSettings.addSubscribe("test")
                        }
                    }
                    Button {
                        text: "remove subScribe"
                        onClicked: {
                            StyleSettings.removeSubScribe()
                        }
                    }
                }
            }
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        Repeater {
            model: StyleSettings.subscribes
            TabButton {
                contentItem: RowLayout {
                    Label {
                        text: modelData
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "x"
                        onClicked : {
                            StyleSettings.removeSubScribeWithKey(modelData)
                        }
                    }
                }
            }
        }
    }
}
