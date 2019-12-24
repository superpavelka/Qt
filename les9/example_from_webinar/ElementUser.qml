import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
   property string townname: ""    // Свойства объекта
   property string towninfo: ""

function setValue(t, inf)
{
   console.log(t + inf)
}

id: comps
color: '#eeeee4'
width: 500
height: 150
   Text {
       id:name
       text: townname
       y:10
   }
   ScrollView
   {
       id:scroll
       ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
       ScrollBar.vertical.policy: ScrollBar.AlwaysOn
       Text {
           id: informatio
           text: towninfo
           height: scroll.height
           width: scroll.width
           wrapMode: TextEdit.Wrap // Чтобы текст не вылезал за границу поля
       }
   }

   Component.onCompleted: {
       name.y = 10;
       name.x = parent.width / 2;
       scroll.y = 40;
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
       obj.setInformation(townname, towninfo)
       obj.show()

   }
}
}
