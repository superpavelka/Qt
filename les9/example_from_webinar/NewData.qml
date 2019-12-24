import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
   color: '#eeeee4'
   width: 500
   height: 300
   id:mainrect

   Text {
       x:10
       y:10
       text: qsTr("Name of town")
   }
   Rectangle
   {
       color: 'white'
       x:townName.x
       y:townName.y
       width: townName.width
       height: townName.height
   }

   TextEdit{
       id:townName
       y:10
       x:100
       width: 400
       focus: true
       height: 25
   }
   Text {
       x:10
       y:40
       text: qsTr("Information")
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
       y:40
       width: 400
       height: 80
       ScrollBar.vertical: ScrollBar{}
       TextArea.flickable: TextArea {
           id:information
           width: flick.width
           height: flick.height
           focus: true
           wrapMode: TextEdit.Wrap
           selectByMouse: true
       }
   }

   Button{
       id:addData
       text: qsTr("Add")
       onClicked:
       {
           var town = townName.text
           var info = information.text
           mainrect.parent.add(town, info)
       }
       Component.onCompleted: {
           x = mainrect.width - 100;
           y = mainrect.height - 30;
           width=100
           height=30
       }
   }
}
