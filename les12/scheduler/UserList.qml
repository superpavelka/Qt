import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Layouts 1.12
import com.gb.BaseTask 1.0

Window {
   property BaseReader baseRender: null
   property int amount: 0
   property var users : new Array (0)
   id:window

   function addUser(username)
   {
       var line = 'import QtQuick.Controls 2.5;Label{width:500;height:30;x:10;y:' + (160 + 30 * amount) + ';text:"' + username + '"}'
       var newUser = Qt.createQmlObject(line, table, 'user' + amount++)
       users.push(newUser)
   }
   /*function delUser(username)
   {
       var delIndex = -1
       for (var i=0; i<users.length; i++)
           if (users[i].text === username)
               delIndex = i
       if (delIndex >= 0)
       {
           users[delIndex].destroy()
       }
   }*/
   width: 600
   height: 600
   ScrollView {
       id:table
       ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
       ScrollBar.vertical.policy: ScrollBar.AlwaysOn
       AddNewUser{
           width: 500
           height: 150
           basereader: window.baseRender
       }
   }
}
