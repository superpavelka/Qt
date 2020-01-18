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
           console.log(itog)
           Qt.createQmlObject(itog, table, "lineTask" + amountTasks++)
           getNext()
       }
       onEmitNextLine: getNext() // Добавление нового компонента
       onEmitInitBase:
       {
           taskWindow.close()
           basereader.updateList()
       }
       onAddUserToList:
       {
           if (userlist != null)
           {
               userlist.addUser(fio)
               basereader.getNextUser()
           }
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
       Button{
           id:userButton
           height: 30
           x:150
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
   }
}
