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

                }
                RoundButton {
                    text: qsTr("o")
                    highlighted: true
                    anchors.margins: 10
                    anchors.left: parent.left
                    anchors.top: parent.top
                    onClicked: {
                        modelData.updateSucribes()
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
                        text: modelData.url
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "x"
                        onClicked : {
                            StyleSettings.removeSubScribeWithKey(modelData.url)
                        }
                    }
                }
            }
        }
    }

    RoundButton {
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            resDialog.open()
        }
    }

    Dialog {
        id: resDialog
        x: Math.round((page.width - width) / 2)
        y: Math.round(page.height / 6)
        width: Math.round(Math.min(page.width, page.height) / 3 * 2)
        modal: true
        focus: true
        title: "Settings"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            StyleSettings.addSubscribe(urlText.text)
            //CommandLineGet.getHttpsOutput(urlText.text)
            //StyleSettings.setStyle(styleBox.currentText)
            resDialog.close()
        }
        contentItem: TextInput {
            id: urlText
        }
    }
}
