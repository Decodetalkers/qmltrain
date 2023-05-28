import Command.Base 1.0
import Command.Sync 1.0
import Marine
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: page

    SwipeView {
        id: swipeView

        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Pane {
            ListView {
                anchors.fill: parent
                model: StyleSettings.subscribes

                delegate: ItemDelegate {
                    width: swipeView.width

                    contentItem: RowLayout {
                        spacing: 20

                        Label {
                            text: modelData.urlName
                            horizontalAlignment: Qt.AlignLeft
                            Layout.fillWidth: true
                        }

                        Label {
                            text: "Last Update : " + modelData.updateTime
                            horizontalAlignment: Qt.AlignRight
                            Layout.fillWidth: false
                        }

                        Label {
                            text: "Subscribe Counts :" + modelData.subscribeCounts
                            horizontalAlignment: Qt.AlignRight
                            Layout.fillWidth: false
                        }

                        Button {
                            text: "o"
                            onClicked: {
                                modelData.updateSucribes();
                            }
                            enabled: !modelData.subscribing
                        }

                    }

                }

            }

        }

        Repeater {
            model: StyleSettings.subscribes

            Pane {
                width: swipeView.width
                height: swipeView.height

                BusyIndicator {
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: modelData.subscribing
                }

                ListView {
                    anchors.fill: parent
                    model: modelData

                    delegate: SubScribeDelegate {
                        width: swipeView.width
                        theswitch.checked: modelData.url === StyleSettings.workingSubScribeUrl && index === StyleSettings.workingSubScribeIndex
                        onSwitchCheck: function(checked) {
                            StyleSettings.setWorkingSubScribe(modelData.url, index);
                        }
                    }

                }

                RoundButton {
                    text: qsTr("o")
                    highlighted: true
                    anchors.rightMargin: 70
                    anchors.topMargin: 20
                    anchors.right: parent.right
                    anchors.top: parent.top
                    onClicked: {
                        modelData.updateSucribes();
                    }
                    enabled: !modelData.subscribing
                }

            }

        }

    }

    RoundButton {
        text: qsTr("+")
        highlighted: true
        anchors.margins: 50
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            resDialog.open();
        }
    }

    Dialog {
        id: rmdialog

        property string currentUrl
        property string currentUrlName

        function removeUrl(url, urlName) {
            rmdialog.currentUrl = url;
            rmdialog.currentUrlName = urlName;
            rmdialog.open();
        }

        x: Math.round((page.width - width) / 2)
        y: Math.round(page.height / 6)
        width: Math.round(Math.min(page.width, page.height) / 3 * 2)
        modal: true
        focus: true
        title: "Remove " + rmdialog.currentUrlName + "?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            StyleSettings.removeSubScribeWithKey(rmdialog.currentUrl);
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
            StyleSettings.addSubscribe(urlTextField.text, urlNameField.text);
            //CommandLineGet.getHttpsOutput(urlText.text)
            //StyleSettings.setStyle(styleBox.currentText)
            grid.urlNameField.clear();
            grid.urlTextField.clear();
            resDialog.close();
        }

        contentItem: GridLayout {
            id: grid

            property alias urlNameField: urlNameField
            property alias urlTextField: urlTextField
            property string urlName
            property string url

            rows: 2
            columns: 2

            Label {
                text: qsTr("UrlName")
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
            }

            TextField {
                id: urlNameField

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                placeholderText: grid.urlName
            }

            Label {
                text: qsTr("Url")
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
            }

            TextField {
                id: urlTextField

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                placeholderText: grid.url
            }

        }

    }

    header: TabBar {
        id: tabBar

        currentIndex: swipeView.currentIndex

        TabButton {
            text: "OverView"
        }

        Repeater {
            model: StyleSettings.subscribes

            TabButton {

                contentItem: RowLayout {
                    Label {
                        color: StyleSettings.workingSubScribeUrl === modelData.url ? "orange" : "black"
                        text: modelData.urlName
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "x"
                        onClicked: {
                            rmdialog.removeUrl(modelData.url, modelData.urlName);
                        }
                    }

                }

            }

        }

    }

}
