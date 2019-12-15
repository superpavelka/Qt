import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
   property string id: ""    // Свойства объекта
   property string task: ""
   property string desc: ""

function setValue(id, task,desc)
{
   console.log(id + task + desc)
}

id: comps
color: '#eeeee4'
width: 500
height: 150
   Text {
       id:id
       text: id
       y:10
   }
   Text {
       id:task
       text: task
       y:40
   }
   ScrollView
   {
       id:scroll
       ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
       ScrollBar.vertical.policy: ScrollBar.AlwaysOn
       Text {
           id: desc
           text: description
           height: scroll.height
           width: scroll.width
           wrapMode: TextEdit.Wrap // Чтобы текст не вылезал за границу поля
       }
   }

   Component.onCompleted: {
       name.y = 10;
       name.x = parent.width / 2;
       scroll.y = 70;
       scroll.width = parent.width
       scroll.height = 200
   }
MouseArea {
   acceptedButtons: Qt.LeftButton
   anchors.fill: parent
   cursorShape: "OpenHandCursor"
   onPressed: {
       console.log("THIS")
       var component = Qt.createComponent("AboutWindow.qml")
       console.log(component)
       var obj = component.createObject(AboutWindow)
       console.log(obj)
       obj.setInformation(id, task, desc, datebeg)
       obj.show()

   }
}
}
