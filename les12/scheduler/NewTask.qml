import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0
Window {
 property BaseReader baseRender: null // Класс работы с БД
 width: 800
 height: 300
 id: dlg
 Rectangle
 {
     color: 'yellow'
     anchors.fill: task
 }
 Label
 {
     id:tasklabel
     x:0
     y:10
     text: "Задача"
 }
 TextEdit
 {
     id:task
     width: 200
     height: 20
     x:50
     y:10
 }
 Label{
     x:0
     y: 70
     text: "Описание"
 }
  Flickable
 {
     id:flick
     x: 50
     y: 80
     width: 600
     height: 60
     TextArea.flickable: TextArea
     {
         anchors.fill:flick
         id:descr
         width: flick.width
         height: flick.height
         focus: true
         wrapMode: TextEdit.Wrap
         selectByMouse: true
     }
 }
 Label{
     x:0
     y: 180
     text: "Начало"
 }
 TextEdit
 {
     id:beg
     x:60
     y: 180
     text: "dd.mm.yyyy"
}
 Label{
     x:400
     y: 180
     text: "Окончание работ"
 }
 TextEdit
 {
     id:end
     x:500
     y: 180
     text: "dd.mm.yyyy"
 }
 Component.onCompleted:
 {
     addline.x = width - addline.width
     addline.y = height - addline.height
     adminpass.x = width - adminpass.width - addline.width
     adminpass.y = height - adminpass.height
     var date = new Date
     beg.text = Qt.formatDate(date, "dd.MM.yyyy");
     end.text = Qt.formatDate(date, "dd.MM.yyyy");
 }
 Button
 {
     id:addline
     text: "Добавить"
     height: 30
     y:0
     x:700
     width: 100
     onClicked:
     {
         var begDate = beg.selectedDate
         var endDate = end.selectedDate
         baseRender.addNew(task.text, descr.text, beg.text, end.text, adminpass.text);
         dlg.close()
     }
 }
 TextEdit {
     id:adminpass
     text: "Пароль администратора"
 }
}
