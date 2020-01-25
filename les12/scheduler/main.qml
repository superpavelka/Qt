import QtQuick 2.12
import QtQuick.Window 2.12
import com.gb.BaseTask 1.0
import QtQuick.Controls 2.5

Window {
    property int amountTasks: 0
    property string newtableline: 'TaskElement{width:800; height:30;'
    property UserList userlist: null
    property TaskWindow taskWindow:null
    property NewTask newTask:null
    property var tasks : new Array (0)
    function loadnext()
    {
        basereader.getNext();
    }
    BaseReader
    {
        id: basereader
        onStatusLoadBase:
        {
            if (correct == false)
            {
                Qt.quit()
                console.log(error)
            }
            else
            {
                serverclientrect.destroy() // Удаляем панель выбора
            }

            if (amount > 0)
            {
                loadnext()
            }
        }
        onLogMistake:
        {
            console.log(msg)
        }
        onPrintData:
        {
            var itog = newtableline + 'taskTxt:"' + task + '";begTxt:"'
                    + begDate + '";endTxt:"' + endDate +'";prgTxt:"'
                    + Number(progress) + '%"; y:' + amountTasks * 25 + ';idt:' + id +
                    ';dbreader:basereader' + '}';
            console.log(itog);
            var newTask = Qt.createQmlObject(itog, table, "lineTask" + amountTasks++);
            newTask.y = basereader.getY();
            basereader.incY(newTask.height);
            tasks.push(newTask);
            getNext();
        }
        onEmitNextLine: getNext() // Добавление нового компонента
        onEmitDelAndUpdate:
        {
            taskWindow.close();
            for (var i=0; i<tasks.length; i++)
                tasks[i].destroy();
            tasks = []
            basereader.updateList();
        }
        onAddUserToList:
        {
            if (userlist != null)
            {
                userlist.addUser(fio)
                basereader.getNextUser()
            }
        }
        onCloseUsrWindow:
        {
            userlist.close()
            var delIndex = -1
            for (var i=0; i<model.count; i++)
                if (model.get(i).text === fio)
                    delIndex = i
            if (delIndex >= 0)
                model.remove(delIndex)
        }

        /*onDelUserFromList:
       {
           if (userlist != null)
           {
            userlist.delUser(fio)
           }
       }*/
        onAddUserToCombo:
        {
            model.append({ text: fio })
            basereader.getNextUserCombo()
        }

        onSignalAddNewUserCombo:
        {
            model.append({ text: fio })
        }

        onTaskFullInformation:
        {
            var comp = Qt.createComponent("qrc:///TaskWindow.qml")
            taskWindow = comp.createObject(TaskWindow)
            taskWindow.bdreader = basereader
            taskWindow.idt = id
            taskWindow.taskname = task
            taskWindow.describe = descr
            taskWindow.startDate = begDate
            taskWindow.endDate = endDate
            taskWindow.progress = progress
            taskWindow.show()
        }
        onSetAdminModeEditTask: {
            if (taskWindow != null)
            {
                taskWindow.setAdminMode()
            }
        }
        onAdminUserTask:
        {
            if (taskWindow != null)
            {
                taskWindow.adminmode.adminModeInfoUserTask(active, fio, login, usertask, report)
            }
        }
        onSetWorkMode: {
            if (taskWindow != null)
            {
                taskWindow.setWorkMode(fio, bigTask, report)
            }
        }
    }
    visible: true
    width: 640
    height: 480
    title: qsTr("Sheduler")
    Component.onCompleted:
    {
        basereader.initBase();   // Загрузка базы заданий
        table.width = width
        table.height = height - 50;

        rect.width = width
        rect.height = 50;
        rect.y = height - 50
    }

    ScrollView
    {
        id:table
        width: 600
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

    }
    Rectangle
    {
        id: rect
        height: 30
        Button
        {
            id:addButton
            text: "Добавить"
            onClicked:
            {
                console.log("THIS")
                var component = Qt.createComponent("qrc:///NewTask.qml")
                console.log(component)
                var obj = component.createObject(NewTask)
                console.log(obj)
                obj.baseRender = basereader
                obj.show()
            }
        }
        Button
        {
            id:userButton
            height: 40
            x:106
            y: 0
            width: 100
            text: "Пользователи"
            onClicked:
            {
                var comp = Qt.createComponent("qrc:///UserList.qml")
                userlist = comp.createObject(UserList)
                userlist.baseRender = basereader
                userlist.show();
                basereader.getFirstUser()
            }
        }
        ComboBox
        {
            id: comboBox
            x: 212
            y: 0
            width: 140
            displayText: "Фильтрация"
            model: ListModel {
                id: model
            }
            Component.onCompleted:
            {
                currentIndex = 0
                model.append({ text: "admin" })
                basereader.getNextUserCombo()
            }
            onActivated:
            {
                var user = model.get(index).text
                for (var i=0; i<tasks.length; i++)
                    tasks[i].destroy();
                tasks = []
                basereader.filterList(user)
            }
        }
        Rectangle
               {
                   id:serverclientrect
                   x:300
                   y:userButton.y
                   width: 400
                   height: 100
                   color: 'red'
                   Button {
                       id:localeBD
                       height: 30
                       text: "Локальная"
                       onClicked:
                       {
                           basereader.initBase() // Работает как в примере из 11 урока
                       }
                   }
                   Rectangle
                   {
                       anchors.fill: ipServer
                   }
                   TextEdit
                   {
                       id:ipServer
                       x: localeBD.x + localeBD.width + 100
                       width: 100
                       text: "192.168.1.14"
                   }
                   Button
                   {
                       id:clientMode
                       x:ipServer.x
                       height: 30
                       y:ipServer.y + ipServer.height + 10
                       text: "Подключиться"
                       onClicked: {
                           basereader.initBaseClient(ipServer.text)
                       }
                   }
               }
    }
}
