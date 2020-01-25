import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0

Item {
   property int idt: 0
   property BaseReader dbreader: null
   property int usertaskamn: 0
   property string nb: 'ActiveUserItem{width:parent.width; height:150}'
   property ActiveUserItem elem: null
   function setInformation(task, describe, beg, end, progr)
   {
       taskEdit.text = task
       describeEdit.text = describe
       bedit.text = beg
       endedit.text = end
       progredit.text = progr
   }
   function adminModeInfoUserTask(activ, fio, login, task, report)
   {
       var y = 150 * usertaskamn
       elem = Qt.createQmlObject(nb, table, 'usertask' + usertaskamn++)
       elem.y = y
       elem.setValue(task, report, fio, login, activ, dbreader)
       dbreader.getNextUserTask()
   }    
   Rectangle
   {
       anchors.fill: parent
       id: admin
       Rectangle
       {
           id:adminRect
           width: parent.width
           height: parent.height
           x:0
           color: '#eeeee4'
           Rectangle
           {
               color: 'white'
               anchors.fill: taskEdit
           }
           TextEdit
           {
               id:taskEdit
               text: "Task"
               width: parent.width - 30
               x:15
               y:0
               focus: true
               selectByMouse: true
           }
       }
       Rectangle
       {
           color: 'white'
           anchors.fill: dflick
       }
       Flickable{
           x:15
           y: 30
           id:dflick
           width: 300
           height: 100

           TextArea.flickable: TextArea
           {
               id:describeEdit
               width:dflick.width
               height:dflick.height
               focus: true
               selectByMouse: true
               wrapMode:TextEdit.Wrap
           }
       }
       Rectangle
       {
           y: 200
           x:0
           width: parent.width
           height: 25
           color: '#eeeee4'
           Label
           {
               text: "Начало"
               x:0
           }
           Label
           {
               text: "Окончание"
               x:150
           }

           Label
           {
               text: "Прогресс"
               x:300
           }
       }
       Rectangle
       {
           y: 225
           x:0
           width: parent.width
           height: 25
           color: '#eeeee4'

           Rectangle
           {
               anchors.fill: bedit
           }
           Rectangle
           {
               anchors.fill: endedit
           }

           Rectangle
           {
               anchors.fill: progredit
           }
           TextEdit
           {
               id:bedit
               x:0
               width: 140
               focus: true
               selectByMouse: true
           }
           TextEdit
           {
               id:endedit
               x:150
               width: 140
               focus: true
               selectByMouse: true
           }
           TextEdit
           {
               id:progredit
               x:300
               width: 140
               focus: true
               selectByMouse: true
           }
           Button
           {
               x:450
               width:100
               height: 30
               text: "Обновить"
               onClicked:
               {
                   dbreader.updateTaskData(idt, taskEdit.text, describeEdit.text, bedit.text, endedit.text, progredit.text)
               }
           }

           Button {
               x: 552
               y: 0
               width: 100
               height: 30
               text: "Удалить"
               onClicked:
               {
                    dbreader.deleteTaskData(idt)
               }
           }
       }
       ScrollView {
           y: 250
           width: parent.width
           id:table
           ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
           ScrollBar.vertical.policy: ScrollBar.AlwaysOn
           ActiveUserItem
           {
               width: parent.width
               height: 150
           }
       }
   }
}

