
import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import com.gb.BaseTask 1.0
Item {
   property string usrlogin: 'value'
   property BaseReader br: null
   function setValue(task,rep,user, login, a, dbreader)
   {
       taskofuser.text = task
       report.text = rep
       userl.text = user + "(" + login + ")"
       if (a) head.color = 'green'
       br = dbreader
       usrlogin = login
   }
  Rectangle
  {
     id:head
     color: 'red'
     x:0
     width: parent.width
     height: 25
     Label
     {
        id:userl
     }
   }
   Rectangle
   {
       y:30
       width: parent.width
       height: parent.height - 60
       color: '#eeeee4'
       Rectangle
       {
           anchors.fill: tflick
       }
       Flickable
       {
           id:tflick
           height: parent.height
           width: parent.width / 2 - 30
           TextArea.flickable: TextArea
        {
        id:taskofuser
        focus:true
        text:"task"
        selectByMouse:true
        wrapMode:TextEdit.Wrap
        width:tflick.width
        height:tflick.height
      }
  }
  Flickable
  {
      id:rflick
      height: parent.height
      width: parent.width / 2 - 30
      x:parent.width / 2
      TextArea.flickable: TextArea
      {
          id:report
          focus:true
          selectByMouse:true
          wrapMode:TextEdit.Wrap
          width:rflick.width
          height:rflick.height
          readOnly: true
      }
  }
  Button
  {
      text: "Изменить"
      x:parent.width - width
      y:parent.height - height
      onClicked:
      {
          br.changeTaskUser(usrlogin, taskofuser.text)
      }
  }
 }
}
