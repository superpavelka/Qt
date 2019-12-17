import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Window {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Tasks")

    property NewData newData: value

    ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.fill: parent       // Заполняем всю область родительского
                                   // объекта
    }
    Rectangle {
        id: id_rect
        x: 0
        y: 0
        width: 65
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: id_label
            x: 18
            y: 8
            text: qsTr("ID")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: task_rect
        x: 65
        y: 0
        width: 119
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: task_label
            x: 41
            y: 8
            text: qsTr("Задача")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: desc_rect
        x: 184
        y: 0
        width: 176
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: desc_label
            x: 61
            y: 8
            width: 54
            height: 14
            text: qsTr("Описание")
            font.pixelSize: 12
        }
    }


    Rectangle {
        id: datebeg_rect
        x: 360
        y: 0
        width: 109
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: datebeg_label
            x: 14
            y: 0
            width: 71
            height: 30
            text: qsTr("Дата начала\n разработки")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: dateend_rect
        x: 468
        y: 0
        width: 93
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: dateend_label
            x: 13
            y: 2
            text: qsTr("Срок\nвыполнения")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: progress_rect
        x: 561
        y: 0
        width: 79
        height: 30
        color: "#ffffff"
        border.color: "#040404"

        Text {
            id: progress_label
            x: 14
            y: 8
            text: qsTr("Прогресс")
            font.pixelSize: 12
        }
    }
    Rectangle {
        id: t_id_rect
        x: 0
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }


    Rectangle {
        id: t_task_rect
        x: 65
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_desc_rect
        x: 184
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_dateb_rect
        x: 360
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_datee_rect
        x: 468
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: t_prog_rect
        x: 561
        y: 30
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
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }
}
