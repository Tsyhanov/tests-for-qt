import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import searcher.config 1.0

Window {
    id: mainWindow
    visible: true
    width: 270
    minimumWidth: 270
    maximumWidth: 270
    height: 340
    minimumHeight: 340
    maximumHeight: 340
    color: "#c1bebe"
    title: "Modbus device searcher"
    property var arrspeed: ["9600", "19200", "38400"]
    property var arrport: ["COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8"]
    property real progress: searchconf.m_currSearchAddr
    Searcher{
        id: searchconf
        m_currPort: comboPort.currentText;
        m_startAddr: comboStart.currentText;
        m_endAddr: comboEnd.currentText;
    }


    GroupBox {
        id: groupBox
        x: 6
        y: 8
        width: 259
        height: 218
        title: qsTr("Search settings")

        ComboBox {
            id: comboPort
            x: -12
            y: 0
            width: 120
            model: mainWindow.arrport
        }

        ComboBox {
            id: comboPortSpeed
            x: 127
            y: 0
            width: 120
            model: mainWindow.arrspeed
        }

        ComboBox {
            id: comboStart
            x: -12
            y: 59
            width: 120
            model: [1, 2, 3]
        }

        ComboBox {
            id: comboEnd
            x: 127
            y: 59
            width: 120
            model: [100, 200, 255]
        }

        Button {
            id: buttonStart
            x: -12
            y: 117
            width: 259
            height: 40
            text: qsTr("Start search")
            onClicked: {
                searchconf.startSearch();
                progressBar.from = comboStart.displayText;
                progressBar.to = comboEnd.displayText;
            }
        }

        ProgressBar {
            id: progressBar
            x: -12
            y: 169
            width: 259
            height: 6
            hoverEnabled: false
            value: progress
            from: 0
            to: 1
        }

        Label {
            id: label
            x: -12
            y: -13
            text: qsTr("COM-порт")
        }

        Label {
            id: label1
            x: 127
            y: -13
            text: qsTr("Speed")
        }

        Label {
            id: label2
            x: -12
            y: 45
            text: qsTr("From address")
        }

        Label {
            id: label3
            x: 127
            y: 45
            text: qsTr("To address")
        }
    }

    Button {
        id: buttonClose
        x: 6
        y: 292
        width: 259
        height: 40
        text: qsTr("Close")
        onClicked: {
            Qt.quit();
        }
    }

    TextArea {
        id: textArea
        x: 6
        y: 232
        width: 259
        height: 46
        text: qsTr("Log:")
    }
}
