import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Command.Base 1.0


ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Action {
        id: navigateAboutAction
        icon.name: "vlc"
        onTriggered: {
            optionsMenu.open()
        }
    }
    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent
            Label {
                id: titleLabel
                text: "Nobody here"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                action: navigateAboutAction
                Menu {
                    id: optionsMenu
                    Action {
                        text: "Settings"
                        onTriggered : {
                            CommandLineGet.getOutput()
                        }
                    }
                }
            }
        }
    }
    Connections {
        function onOutPuts(messages) {
            edit.text = messages
        }
        target: CommandLineGet
    }
    RowLayout {
        ListView {
            implicitWidth: 200; implicitHeight: root.height
            model: ContactModel {}
            delegate: Text {
                text: name + ": " + number
            }
        }
        TextEdit {
            id: edit
            Layout.preferredWidth: root.width - 200
            Layout.preferredHeight: root.height
            wrapMode: TextEdit.Wrap
        }
    }
}
