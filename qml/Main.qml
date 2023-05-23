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

    required property var buildInStyles

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
                            resDialog.open()
                            //CommandLineGet.getHttpsOutput()
                        }
                    }
                    Action {
                        text: "Style"
                        onTriggered : {
                            settingsDialog.open()
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


    Dialog {
        id: settingsDialog
        x: Math.round((root.width - width) / 2)
        y: Math.round(root.height / 6)
        width: Math.round(Math.min(root.width, root.height) / 3 * 2)
        modal: true
        focus: true
        title: "Settings"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            StyleSettings.setStyle(styleBox.currentText)
            settingsDialog.close()
        }
        onRejected: {
            settingsDialog.close()
        }
        contentItem: ColumnLayout {
            id: settingColumn
            spacing: 20

            RowLayout {
                spacing: 10

                Label {
                    text: "Style: "
                }
                ComboBox {
                    id: styleBox
                    property int styleIndex : -1
                    model: root.buildInStyles
                    Component.onCompleted: {
                        styleIndex = find(StyleSettings.style, Qt.MatchFixedString)
                        if (styleIndex !== -1) {
                            currentIndex = styleIndex
                        }
                    }
                    Layout.fillWidth: true
                }
            }
            Text {
                text: StyleSettings.style
            }
        }
    }
    Dialog {
        id: resDialog
        x: Math.round((root.width - width) / 2)
        y: Math.round(root.height / 6)
        width: Math.round(Math.min(root.width, root.height) / 3 * 2)
        modal: true
        focus: true
        title: "Settings"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            CommandLineGet.getHttpsOutput(urlText.text)
            //StyleSettings.setStyle(styleBox.currentText)
            resDialog.close()
        }
        onRejected: {
            settingsDialog.close()
        }
        contentItem: TextInput {
            id: urlText
        }
    }

}
