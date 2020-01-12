import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0

Window {
   property  BaseReader bdreader: null
   property int idt: 0
   property string taskname: ''
   property string describe: ''
   property string startDate: ''
   property string endDate: ''
   property int progress: 0

   property AdminControlTask adminmode: null
   property WorkMode workItem: null

   id:mainwindow
   width: 800
   height: 600

   function setAdminMode()
   {
       autorization.destroy();
       adminmode = Qt.createQmlObject("AdminControlTask{anchors.fill: parent}",mainwindow, 'adminmode')
       adminmode.setInformation(taskname, describe, startDate, endDate, progress)
       adminmode.idt = idt
       adminmode.dbreader = bdreader
       bdreader.getFirstUserTask()
   }

   function setWorkMode(fio, bigTask, report)
   {
       autorization.destroy();
       workItem = Qt.createQmlObject("WorkMode{anchors.fill: parent}",mainwindow, 'workItem')
       workItem.setWork(fio, bigTask, report, bdreader)
   }

   Rectangle
   {
       id:autorization
       width: 400
       height: 100
       color: '#eee104'
       Component.onCompleted:
       {
           x = (mainwindow.width - width) / 2
           y = (mainwindow.height - height) / 2
       }

       Rectangle
       {
           height: 30
           width: parent.width - 20
           color: '#eeeee4'
           x:10
           y:10
           Label
           {
               x:0
               text: "Логин:"
           }
           Rectangle
           {
               color: 'white'
               anchors.fill: loginedit
           }
           TextEdit
           {
               id:loginedit
               x: 100
               width: parent.width - 120
               focus: true
               selectByMouse: true
           }
       }
       Rectangle
       {
           height: 30
           width: parent.width - 20
           color: '#eeeee4'
           x:10
           y:40
           Label
           {
               x:0
               text: "Пароль:"
           }
           Rectangle
           {
               color: 'white'
               anchors.fill: passedit
           }
           TextEdit
           {
               id:passedit
               x: 100
               width: parent.width - 120
               focus: true
               selectByMouse: true
           }
       }
       Button
       {
           text: "Войти"
           height: 30
           width:150
           x:parent.width - width - 10
           y:parent.height - height
           onClicked:
           {
               bdreader.autorization(loginedit.text, passedit.text)
           }
       }
   }
}
