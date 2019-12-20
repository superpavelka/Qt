import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import com.vv.reader 1.0


Window {
    id:root
    visible: true
    width: 750
    height: 480
    title: qsTr("Tasks")

    property string ns: 'NewData{width:640; height:20;}'
    property string ts: 'NewData{width:640; height:20;'
    property int num: 0

    ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.fill: parent
        Component.onCompleted:
        {
            loader.loadBase()
        }
        ColumnLayout {
            id:list
            y:35
        }
    }

    Reader{
        id : loader
        onInitEnd:
        {
            if (succeed)
            {
              Qt.createQmlObject(ns, list, "objdata")
              loader.getNextRecord()
            } else Qt.quit()
        }
        onLoad:
        {
            var total = ts + 't_id:"' + id + '";task:"' + task +
                             '";desc:"' + desc + '";date_beg:"' + date_beg +
                             '";date_end:"' + date_end + '";prog:"' + prog +'";}'
            Qt.createQmlObject(total, list, "obj" + (++num))
            loader.getNextRecord()

        }
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
    Button{
        id:addData
        text: qsTr("Добавить")
        Component.onCompleted: {
            x = 640;
            y = 0;
            width=100
            height=30
        }
        onClicked:
        {
           var data_id = list.data[num].data[0].data[0].text
           var data_task = list.data[num].data[1].data[0].text
           var data_desc = list.data[num].data[2].data[0].text
           var data_datebeg = list.data[num].data[3].data[0].text
           var data_dateend = list.data[num].data[4].data[0].text
           var data_prog = list.data[num].data[5].data[0].text
           loader.writeNewInformation(data_id,data_task,data_desc,data_datebeg,data_dateend,data_prog)
           Qt.createQmlObject(nc, list, "objdata")
           num++
        }

    }

}
