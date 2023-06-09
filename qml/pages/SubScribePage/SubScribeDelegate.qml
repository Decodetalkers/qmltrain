// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: delegate

    property alias theswitch: theswitch

    signal switchCheck(bool checkstatus)

    checkable: true
    states: [
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                // TODO: When Qt Design Studio supports generalized grouped properties, change to:
                //       grid.visible: true
                target: grid
                visible: true
            }

        }
    ]

    contentItem: ColumnLayout {
        spacing: 10

        RowLayout {
            Label {
                text: name
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Switch {
                id: theswitch

                onClicked: {
                    delegate.switchCheck(checked);
                }
            }

        }

        GridLayout {
            id: grid

            visible: false
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Label {
                text: qsTr("PassWord:")
                Layout.leftMargin: 60
            }

            Label {
                text: password
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("port:")
                Layout.leftMargin: 60
            }

            Label {
                text: port
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("method:")
                Layout.leftMargin: 60
            }

            Label {
                text: method
                font.bold: true
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

        }

    }

}
