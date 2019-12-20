import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Rectangle
{
    x: 0
    y: 0
    height: 20
    id:mainrect

    Rectangle {
        id: t_id_rect
        x: 0
        y: 0
        width: 65
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit
            x: 0
            y: 0
            width: 65
            height: 20
            text: ""
            font.pixelSize: 12
        }
    }


    Rectangle {
        id: t_task_rect
        x: 65
        y: 0
        width: 119
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit1
            x: 0
            y: 0
            width: 119
            height: 20
            text: qsTr("")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_desc_rect
        x: 184
        y: 0
        width: 176
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit2
            x: 0
            y: 0
            width: 176
            height: 18
            text: qsTr("")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_dateb_rect
        x: 360
        y: 0
        width: 109
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit3
            x: 0
            y: 0
            width: 109
            height: 20
            text: qsTr("")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_datee_rect
        x: 468
        y: 0
        width: 93
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit4
            x: 0
            y: 0
            width: 93
            height: 20
            text: qsTr("")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_prog_rect
        x: 561
        y: 0
        width: 79
        height: 20
        color: "#ffffff"
        border.color: "#040404"

        TextEdit {
            id: textEdit5
            x: 0
            y: 0
            width: 79
            height: 20
            text: qsTr("")
            font.pixelSize: 12
        }
    }    
}



