import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0
Item {
   id: rootItem
   property string  taskTxt: "task";
   property string  begTxt: "b";
   property string  endTxt: "e";
   property string  prgTxt: "p";
   property BaseReader dbreader: null
   property int idt: 0
   Rectangle{
       id:rect
       anchors.fill: parent
       color: '#eeeee4'
   }
   Component.onCompleted: // По факту загрузки компонентов разделим таблицу на
                          // колонки равной ширины
   {
       width = parent.width;
       height = 25
       taskText.width = parent.width / 4;
       startText.width = parent.width / 4;
       endText.width = parent.width / 4;
       progtxt.width = parent.width / 4;
       var p = 0;
       taskText.x = p;
       p += taskText.width
       startText.x = p;
       p += taskText.width
       endText.x = p;
       p += taskText.width
       progtxt.x = p;
        }
        TextEdit {
            id:taskText
            text: taskTxt
        }
        TextEdit {
            id:startText
            text: begTxt
        }
        TextEdit {
            id:endText
            text: endTxt
        }
        Label {
            id:progtxt
            text: prgTxt
        }
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                dbreader.getLine(idt)
                console.log(idt)
            }
        }
     }

