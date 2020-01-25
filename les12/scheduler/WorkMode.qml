import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0

Item {
   property BaseReader basereader: null
   function setWork(fio, bigTask, report, db)
   {
       hellolabel.text = "Здравствуйте, " + fio
       basereader = db
       bigTaskEdit.text = bigTask
       reportEdit.text = report
   }
   Rectangle
   {
       width: parent.width
       height: 30
       color: '#eeeee4'
       Label
       {
         id:hellolabel
         text: "Hello"
       }
   }
   Rectangle
   {
       width: parent.width
       height: parent.height - 30
       y:30
       color: '#eeeeea'
       Flickable
       {
           id:flbigtask
           width: parent.width
           height: parent.height / 2
           TextArea.flickable: TextArea
           {
               id:bigTaskEdit
               width: flbigtask.width
               height: flbigtask.height
          }
       }
       Rectangle
      {
          anchors.fill: flreport
       }
       Flickable
       {
           id:flreport
           width: parent.width
           height: parent.height / 2 - 50
           y: parent.height / 2
           TextArea.flickable: TextArea
           {
               id:reportEdit
               width: flreport.width
               height: flreport.height
               focus:true
               selectByMouse:true
               wrapMode:TextEdit.Wrap
          }
       }
       Button
       {
           width: 150
           height: 30
           text: "Сохранить отчет"
           x: parent.width - width
           y: parent.height - height
           onClicked:
           {
               basereader.saveReport(reportEdit.text)
           }

       }
    }
}
