import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Command.Base 1.0
import Command.Sync 1.0
import Marine
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

                ListView {
                    anchors.fill: parent
                    delegate: SubScribeDelegate {
                        width: swipeView.width
                    }
                    model: modelData
                }
                RoundButton {
                    text: qsTr("o")
                    highlighted: true
                    anchors.margins: 10
                    anchors.right: parent.right
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
