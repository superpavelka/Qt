import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import com.gb.BaseTask 1.0

Item {
   id:item
   property BaseReader basereader:null
Rectangle
{
    color: '#eeeee4'
    anchors.fill: parent

    Rectangle
    {
        color: '#eee10e'
        width: parent.width
        height: 30
        Label
        {
            width: 50
            height: 25
            text: "ФИО:"
        }
        Rectangle
        {
            color: 'white'
            anchors.fill: fio
        }
        TextEdit
        {
            id:fio
            x:100
            width: 300
            text: "ФИО"
            focus: true
            selectByMouse: true
        }
    }

    Rectangle
    {
        color: '#eee10e'
        width: parent.width
        height: 30
        y:35
        Label
        {
            width: 50
            height: 25
            text: "Логин:"
        }
        Rectangle
        {
            color: 'white'
            anchors.fill: login
        }
        TextEdit
        {
            id:login
            x:100
            width: 300
            text: "логин"
            focus: true
            selectByMouse: true
        }
    }

    Rectangle
    {
        color: '#eee10e'
        width: parent.width
        height: 30
        y:70
        Label
        {
            width: 50
            height: 25
            text: "Пароль доступа:"
        }
        Rectangle
        {
            color: 'white'
            anchors.fill: pass
        }
        TextEdit
        {
            id:pass
            x:100
            width: 300
            text: "Пароль"
            focus: true
            selectByMouse: true
        }
    }

    Rectangle
    {
        y:parent.height - 30
        color: 'red'
        width: parent.width
        height: 30

        Rectangle
        {
            color: 'white'
            anchors.fill: apass
        }
        TextEdit
        {
            id:apass
            x:0
            width: 300
            text: "Пароль администратора"
            focus: true
            selectByMouse: true
        }
        Button
        {
            id:addusr
            text: "Добавить"
            x:parent.width-202
            width: 100
            height: 30
            onClicked:
            {
                basereader.addNewUser(fio.text, login.text, pass.text, apass.text)
                basereader.addNewUserCombo(fio.text)
            }
        }
        Button
        {
            id:delusr
            text: "Удалить"
            x:parent.width-100
            width: 100
            height: 30
            onClicked:
            {
                basereader.delUser(fio.text, login.text, pass.text, apass.text)
            }
        }
    }
}
}
