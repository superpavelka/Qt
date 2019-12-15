import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
   id:infoWindow
   width: 800
   height: 600
   function setInformation(id, task,desc,datebeg)
   {
       title = id
       textEdit.text = task
       textEdit2.text = desc
       textEdit3.text = datebeg

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
   Flickable
   {
       anchors.fill: parent
       id:flick2
       TextArea.flickable: TextArea {
           id: textEdit2
           width: flick2.width
           height: flick2.height
           readOnly: true
           focus: true
           wrapMode: TextEdit.Wrap
           selectByMouse: true
       }
   }
   Flickable
   {
       anchors.fill: parent
       id:flick3
       TextArea.flickable: TextArea {
           id: textEdit3
           width: flick2.width
           height: flick2.height
           readOnly: true
           focus: true
           wrapMode: TextEdit.Wrap
           selectByMouse: true
       }
   }
}
