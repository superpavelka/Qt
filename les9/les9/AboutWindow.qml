import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
   id:infoWindow
   width: 800
   height: 600
   function setInformation(town, info)
   {
       title = town
       textEdit.text = info

   }
   Flickable
   {
       anchors.fill: parent
       id:flick
       TextArea.flickable: TextArea {
           id: textEdit
           width: flick.width
           height: flick.height
           readOnly: true
           focus: true
           wrapMode: TextEdit.Wrap
           selectByMouse: true
       }
   }
}
