import Command.Base 1.0
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: delegate

    checkable: true
    states: [
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                // TODO: When Qt Design Studio supports generalized grouped properties, change to:
                //       hiddenPlace.visible: true
                target: hiddenPlace
                visible: true
            }

        }
    ]

    contentItem: ColumnLayout {
        RowLayout {
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

        RowLayout {
            id: hiddenPlace

            visible: false

            Label {
                text: qsTr("Url: ")
            }

            Label {
                Layout.fillWidth: true
                text: modelData.url
            }

            Button {
                text: "Share"
                onClicked: {
                    StyleSettings.savetoClipBoard(modelData.url);
                }
            }

        }

    }

}
