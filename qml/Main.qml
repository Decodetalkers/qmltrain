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
    Action {
        id: navigateBackAction
        icon.source: stackView.depth > 1 ? "qrc:/images/back.png" : "qrc:/images/drawer.png"
        onTriggered: {
            if (stackView.depth > 1) {
                stackView.pop()
                drawerListView.currentIndex = -1
            } else {
                drawer.open()
            }
        }
    }
    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent
            ToolButton {
                action: navigateBackAction
            }
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

    //Connections {
    //    function onOutPuts(messages) {
    //        edit.text = messages
    //    }
    //    target: CommandLineGet
    //}

    Drawer {
        id: drawer
        width: Math.min(root.width, root.height) / 3 * 2
        height: root.height
        ListView {
            id: drawerListView

            focus: true
            currentIndex: -1
            anchors.fill: parent
            delegate: ItemDelegate {
                width: drawerListView.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    drawerListView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }
            model: ListModel {
                ListElement { title: "MainPage"; source: "pages/LinksPage.qml" }
                ListElement { title: "Settings"; source: "pages/TabBar.qml" }
            }
            ScrollIndicator.vertical: ScrollIndicator { }

        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Pane {
            id: pane

            Image {
                id: logo
                width: pane.availableWidth / 2
                height: pane.availableHeight / 2
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -50
                fillMode: Image.PreserveAspectFit
                source: "qrc:/images/qt-logo.png"
            }

            Label {
                text: "Qt Quick Controls provides a set of controls that can be used to build complete interfaces in Qt Quick."
                anchors.margins: 20
                anchors.top: logo.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: arrow.top
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                wrapMode: Label.Wrap
            }

            Image {
                id: arrow
                source: "qrc:/images/arrow.png"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
            }
        }
    }

    //RowLayout {
    //    ListView {
    //        implicitWidth: 200; implicitHeight: root.height
    //        model: ContactModel {}
    //        delegate: Text {
    //            text: name + ": " + number
    //        }
    //    }
    //    TextEdit {
    //        id: edit
    //        Layout.preferredWidth: root.width - 200
    //        Layout.preferredHeight: root.height
    //        wrapMode: TextEdit.Wrap
    //    }
    //}

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
            //CommandLineGet.getHttpsOutput(urlText.text)
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
