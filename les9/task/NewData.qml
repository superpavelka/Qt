import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
   color: '#eeeee4'
   width: 600
   height: 300
   id:mainrect

   Text {
       x:10
       y:10
       text: qsTr("Id")
   }
   Rectangle
   {
       color: 'white'
       x:id.x
       y:id.y
       width: id.width
       height: id.height
   }

   TextEdit{
       id:id
       y:10
       x:100
       width: 400
       focus: true
       height: 25
   }
   Text {
       x:10
       y:70
       text: qsTr("Description")
   }
   Rectangle
   {
       color: 'white'
       x:flick.x
       y:flick.y
       width: flick.width
       height: flick.height
   }

   Flickable{
       id:flick
       x:100
       y:70
       width: 400
       height: 50
       ScrollBar.vertical: ScrollBar{}
       TextArea.flickable: TextArea {
           id:desc
           width: flick.width
           height: flick.height
           focus: true
           wrapMode: TextEdit.Wrap
           selectByMouse: true
       }
   }
   Text {
       x:10
       y:40
       text: qsTr("Task")
   }
   Rectangle
   {
       color: 'white'
       x:task.x
       y:task.y
       width: task.width
       height: task.height
   }

   TextEdit{
       id:task
       y:40
       x:100
       width: 400
       focus: true
       height: 25
   }
   Text {
       x:10
       y:130
       text: qsTr("Date Begin")
   }
   Rectangle
   {
       color: 'white'
       x:date_beg.x
       y:date_beg.y
       width: date_beg.width
       height: date_beg.height
   }

   TextEdit{
       id:date_beg
       y:125
       x:100
       width: 400
       focus: true
       height: 25
   }
   Button{
       id:addData
       x: 485
       y: 242
       text: qsTr("Add")
       onClicked:
       {
           var id = id.text
           var task = task.text
           var desc = desc.text
           var date_beg = date_beg.text
           mainrect.parent.add(id, task, desc,date_beg)
       }
       Component.onCompleted: {
           x = mainrect.width - 100;
           y = mainrect.height - 30;
           width=100
           height=30
       }
   }
}
