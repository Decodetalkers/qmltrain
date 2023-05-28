import Command.Base 1.0
import Marine
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    //Connections {
    //    function onOutPuts(messages) {
    //        edit.text = messages
    //    }
    //    target: CommandLineGet
    //}

    id: root

    required property var buildInStyles

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Action {
        id: navigateAboutAction

        icon.name: "vlc"
        onTriggered: {
            optionsMenu.open();
        }
    }

    Action {
        id: navigateBackAction

        icon.source: stackView.depth > 1 ? "qrc:/images/back.png" : "qrc:/images/drawer.png"
        onTriggered: {
            if (stackView.depth > 1) {
                stackView.pop();
                drawerListView.currentIndex = -1;
            } else {
                drawer.open();
            }
        }
    }

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
                    drawerListView.currentIndex = index;
                    stackView.push(model.source);
                    drawer.close();
                }
            }

            model: ListModel {
                ListElement {
                    title: "MainPage"
                    source: "pages/LinksPage.qml"
                }

            }

            ScrollIndicator.vertical: ScrollIndicator {
            }

        }

    }

    StackView {
        id: stackView

        anchors.fill: parent

        initialItem: TabBar {
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
            StyleSettings.setStyle(styleBox.currentText);
            settingsDialog.close();
        }
        onRejected: {
            settingsDialog.close();
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

                    property int styleIndex: -1

                    model: root.buildInStyles
                    Component.onCompleted: {
                        styleIndex = find(StyleSettings.style, Qt.MatchFixedString);
                        if (styleIndex !== -1)
                            currentIndex = styleIndex;

                    }
                    Layout.fillWidth: true
                }

            }

            Text {
                text: StyleSettings.style
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
                        text: "Style"
                        onTriggered: {
                            settingsDialog.open();
                        }
                    }

                }

            }

        }

    }

}
