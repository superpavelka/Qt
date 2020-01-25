#include "basetask.h"
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include "UDPStruct.h"

const QString adminPassword = "123456"; // Пароль администратора
BaseTask::BaseTask(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
}

void BaseTask::initBase()
{
    taskY = 0;
    database = QSqlDatabase::addDatabase("QSQLITE");//SQLite-driver
    database.setDatabaseName("./dbtasks.db");                  // Файл БД
    if (!database.open())                                      // Пытаемся загрузить БД
    {
        emit statusLoadBase(false, 0, tr("Couldn't open DB")); // Не удалось подключиться к БД
    }
    else
    {
        query = QSqlQuery(database);                                // Создаем запрос к открытой БД
        bool p = query.exec("create table if not exists TaskList(id int not null,task varchar(256) not null,"
                            "describe varchar(4096),"
                            "begdata varchar(32) not null,enddata varchar(32) not null,prgress int(8) not null)"); // Создаем таблицу, если она еще не создана
        if (!p)                                                      // Ошибка запроса
        {
            emit statusLoadBase(false, 0, query.lastError().text()); // Выводим ошибку в консоль через QML
            return;
        }
        // Создаем таблицы 2 и 3
        p = query.exec("create table if not exists UserList(fio varchar(128)not null,login varchar(128) not null,pass varchar(128) not null)");
        p = query.exec("create table if not exists TaskUser(id int not null, login varchar(128)not null, usertask varchar(4096), userreport varchar(4096))");
        query.exec("select count (*) from TaskList");
        if (query.next())
        {
            quint32 amount = query.value(0).toUInt();
            listIDTask.clear();
            listlogins.clear();
            if (query.exec("select id from TaskList"))
            {
                while (query.next())
                {
                    listIDTask.append(query.value(0).toUInt());
                }
            }
            pos = 0;

            if (query.exec("select login from UserList"))
            {
                while (query.next())
                {
                    // Добавляем в список пользователей уникальное имя пользователя
                    listlogins.append(query.value("login").toString());

                }
            }
            upos = 0;                                        //Обнуляем счетчик

            emit statusLoadBase(true, amount, "");
            socket->bind(QHostAddress::LocalHost, 8888);
            connect(socket, &QUdpSocket::readyRead, this, &BaseTask::serverUDPReceive);
            isInitDB = true;

        } else
        {
            emit statusLoadBase(false, 0, query.lastError().text());
        }

    }
}

void BaseTask::initBaseClient(QString ip)
{
   socket->bind(QHostAddress::LocalHost, 8888);
   serverHost = QHostAddress(ip);
   connect(socket, &QUdpSocket::readyRead, this, &BaseTask::clientUDPReceive);
   isClient = true; // Содержимое БД будет запрашиваться через сеть Ethernet
   UDPTask udptask;
   udptask.udp.taskUDP = DBQuery::INIT_DB;
   socket->writeDatagram(udptask.bytes, sizeof udptask.bytes, serverHost, 8888);
}

void BaseTask::getNext()
{

    if (!isInitDB) return;
    if (isClient)
    {
        UDPTask udp;
        udp.udp.taskUDP = DBQuery::GET_NEXT_TASK; // Операция, которую нужно
                                                  // выполнить над БД
        udp.udp.pos = pos++;                      // Увеличиваем счетчик
                                                  // Отправляем датаграмму на
                                                  // серверный экземпляр
                                                  // программы
        socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
        return;
    }

    if (pos >= listIDTask.size())
        return;
    bool p = query.exec("select * from TaskList where id=" + QString::number(listIDTask[pos++]));
    if (query.next())
    {
        // Вывод задачи в список
        emit printData(query.value(0).toUInt(), query.value(1).toString(),
                       query.value(2).toString(),query.value(3).toString(),
                       query.value(4).toString(),query.value(5).toUInt());
    }
}

void BaseTask::updateList()
{
    taskY = 0;
    query.exec("select count (*) from TaskList");
    if (query.next())
    {
        quint32 amount = query.value(0).toUInt();
        listIDTask.clear();
        listlogins.clear();
        if (query.exec("select id from TaskList"))
        {
            while (query.next())
            {
                listIDTask.append(query.value(0).toUInt());
            }
        }
        pos = 0;

        if (query.exec("select login from UserList"))
        {
            while (query.next())
            {
                // Добавляем в список пользователей уникальное имя пользователя
                listlogins.append(query.value("login").toString());

            }
        }
        upos = 0;                                        //Обнуляем счетчик

        emit statusLoadBase(true, amount, "");

    } else
    {
        emit statusLoadBase(false, 0, query.lastError().text());
    }
}

void BaseTask::filterList(QString user)
{
    taskY = 0;
    QList<int> t;
    query.exec("select count (*) from TaskList");
    if (query.next())
    {
        if (user == "admin")
        {

            quint32 amount = query.value(0).toUInt();
            listIDTask.clear();
            listlogins.clear();
            if (query.exec("select id from TaskList"))
            {
                while (query.next())
                {
                    listIDTask.append(query.value(0).toUInt());
                }
            }
            pos = 0;

            if (query.exec("select login from UserList"))
            {
                while (query.next())
                {
                    // Добавляем в список пользователей уникальное имя пользователя
                    listlogins.append(query.value("login").toString());

                }
            }
            upos = 0;                                        //Обнуляем счетчик

            emit statusLoadBase(true, amount, "");

        }
        else
        {
            QString login;
            if (query.exec("select login from UserList where fio='" + user + "'"))
            {
                if (query.next())
                {
                    login = query.value(0).toString();
                }
            }
            if (login.length())
            {
                query.exec("select count (*) from TaskUser where login='" + login + "'");
                if (query.next())
                {
                    if (query.exec("select id from TaskUser where login='" + login + "'"))
                    {
                        while (query.next())
                        {
                            t.append(query.value(0).toInt());
                        }
                    }
                }
            }
            quint32 amount = t.size();
            listIDTask.clear();
            listlogins.clear();
            for (int taskId : t)
                listIDTask.append(taskId);
            pos = 0;

            if (query.exec("select login from UserList"))
            {
                while (query.next())
                {
                    // Добавляем в список пользователей уникальное имя пользователя
                    listlogins.append(query.value("login").toString());

                }
            }
            upos = 0;                                        //Обнуляем счетчик

            emit statusLoadBase(true, amount, "");

        }
    }
    else
    {
        emit statusLoadBase(false, 0, query.lastError().text());
    }
}


void BaseTask::addNew(QString task, QString descr, QString begData, QString endData, QString admpass)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::ADD_NEW_TASK;
           QByteArray ba = admpass.toUtf8();
           memcpy(udp.udp.adminpass, ba.data(), ba.size());
           ba = task.toUtf8();
           memcpy(udp.udp.task, ba.data(), ba.size());
           ba = descr.toUtf8();
           memcpy(udp.udp.describe, ba.data(), ba.size());
           ba = begData.toUtf8();
           memcpy(udp.udp.s_data, ba.data(), ba.size());
           ba = endData.toUtf8();
           memcpy(udp.udp.e_data, ba.data(), ba.size());
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }

    if (admpass != adminPassword) {
        return;
    }
    quint32 id = 0;
    for (;;id++) // Определяем свободный ID
    {
        query.exec("select count (*) from TaskList where id=" + QString::number(id)); // Запрашиваем количество задач с данным ID
        if (query.next())
        {
            if (!query.value(0).toInt()) break; // Если количество равно 0, используем данный ID для добавляемой задачи
        }
    }
    bool corr = query.exec("insert into TaskList VALUES(" +
                           QString::number(id) + ",'" +
                           task + "','" +
                           descr + "','" +
                           begData + "','" +
                           endData + "',0)"
                           );                              // SQL-запрос на добавление строки задачи в таблицу БД
    if (!corr) emit logMistake(query.lastError().text());
    else
    {
        listIDTask.append(id);
        emit emitNextLine();
    }
}


void BaseTask::getFirstUser()
{
    if (!isInitDB) return;
    upos = 0;
    getNextUser();
}

void BaseTask::getNextUser()
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::GET_NEXT_USER;
           udp.udp.pos = upos++;
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }
    if (upos < listlogins.size())
    {
        bool p = query.exec("select fio from UserList where login='" + listlogins.at(upos++) + "'");
        if (p)
        {
            if (query.next())
            {
                emit addUserToList(query.value("fio").toString());
            }
        } else emit logMistake("Ошибка SQL-запрос");
    }
}

void BaseTask::getNextUserCombo()
{
    if (upos < listlogins.size())
    {
        bool p = query.exec("select fio from UserList where login='" + listlogins.at(upos++) + "'");
        if (p)
        {
            if (query.next())
            {
                emit addUserToCombo(query.value("fio").toString());
            }
        } else emit logMistake("Ошибка SQL-запрос");
    }
}

void BaseTask::addNewUser(QString fio, QString login, QString passwrd, QString apasswrd)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::ADD_USER;
           QByteArray ba = apasswrd.toUtf8();
           memcpy(udp.udp.adminpass, ba.data(), ba.size());
           ba = fio.toUtf8();
           memcpy(udp.udp.fio, ba.data(), ba.size());
           ba = login.toUtf8();
           memcpy(udp.udp.login, ba.data(), ba.size());
           ba = passwrd.toUtf8();
           memcpy(udp.udp.pass, ba.data(), ba.size());
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }

    if (fio.length() == 0 || login.length() == 0 || passwrd.length() == 0 || apasswrd != adminPassword || login == "admin") return;
    bool user = query.exec("select * from UserList where login='" + login + "'");        // Проверяем, нет ли уже такого пользователя

    if (!user)
    {
        logMistake("Ошибка SQL");
        return;
    }

    if (query.next())
    {
        logMistake("Такой пользователь есть"); // Логин должен быть уникальным
        return;
    }

    user = query.exec("insert into UserList values('" + fio +
                      "','" + login + "','" + passwrd + "')"
                      );
    if (user)
    {
        listlogins.append(login);
        getNextUser();
    }
    else
    {
        logMistake("Не удалось добавить");
    }
}

void BaseTask::addNewUserCombo(QString fio)
{
    emit signalAddNewUserCombo(fio);
}

void BaseTask::delUser(QString fio, QString login, QString passwrd, QString apasswrd)
{
    if (fio.length() == 0 || login.length() == 0 || passwrd.length() == 0 || apasswrd != adminPassword || login == "admin") return;
    bool user = query.exec("select * from UserList where login='" + login + "'");        // Проверяем, есть ли такой пользователь
    if (!user)
    {
        logMistake("Ошибка SQL");
        return;
    }
    if (query.next())
    {
        user = query.exec("delete from UserList where login='" + login + "'");
        if (user)
        {
            int i = listlogins.indexOf(login);
            listlogins.erase(listlogins.begin() + i);
        }
        emit closeUsrWindow(fio);
    }
    else
    {
        logMistake("Такого пользователя нет");
        return;
    }
}

void BaseTask::getLine(int id)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::READ_TASK;
           udp.udp.idtask = id;
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }

    if (query.exec("select * from TaskList where id = " + QString::number(id)))
    {
        if (query.next())
        {
            curID = query.value(0).toUInt();
            tupos = 0;
            emit taskFullInformation(curID, query.value(1).toString(),
                                     query.value(2).toString(),query.value(3).toString(),
                                     query.value(4).toString(),query.value(5).toUInt());
        }
    } else emit logMistake("Ошибка SQL-запрос");
}

void BaseTask::autorization(QString login, QString passwrd)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::AUTORIZATION;
           QByteArray ba = passwrd.toUtf8();
           memcpy(udp.udp.pass, ba.data(), ba.size());
           ba = login.toUtf8();
           memcpy(udp.udp.login, ba.data(), ba.size());
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }

    if (login == "admin" && passwrd == adminPassword) // Режим
        // администрирования
    {
        emit setAdminModeEditTask();
        return;
    }
    if (query.exec("select * from UserList where login='" + login + "' and pass='" + passwrd + "'"))
    {
        if (query.next())
        {

            QString fio = query.value("fio").toString();
            query.exec("select * from TaskUser where id=" + QString::number(curID) + " and login='" + login + "'");
            if (query.next())
            {
                curlogin = login;                    // Сохраняем логин
                // пользователя, который
                // запустил задачу
                QString usertask = query.value("usertask").toString();
                QString report = query.value("userreport").toString();
                QString mtask = "", describe = "";
                if (query.exec("select * from TaskList where id=" + QString::number(curID)))
                {
                    if (query.next())
                    {
                        mtask = query.value("task").toString();
                        describe = query.value("describe").toString();
                    }
                } else return;
                QString info = "Основная задача:" + mtask + "\nОписание:" + describe + "\nВаша задача:" + usertask;
                emit setWorkMode(fio, info, report);
                return;
            }
        }emit logMistake("Нет такого пользователя");
    }else emit logMistake("Ошибка SQL-запрос");
}

void BaseTask::getFirstUserTask()
{
    tupos = 0;
    getNextUserTask();
}
void BaseTask::getNextUserTask()
{
    if (listlogins.size() <= tupos) return;

    bool res = query.exec("select * from TaskUser where id=" + QString::number(curID));
    if (res)
    {
        QString task = "";
        QString report = "";
        QString fio = "";
        bool act= false;
        while(query.next())
        {
            if (query.value("login").toString() == listlogins.at(tupos))
            {
                act = true;
                break;
            }
        }
        //p = query.exec("create table if not exists TaskUser(id int not null, login varchar(128)not null, usertask varchar(4096), userreport varchar(4096))");
        if (act)
        {
            task = query.value("usertask").toString();
            report = query.value("userreport").toString();
        }
        res = query.exec("select fio from UserList where login='" + listlogins.at(tupos) + "'");
        if (res)
        {
            res = query.next();
            if(!res) return;
            fio = query.value("fio").toString();
        } else return;
        quint32 t = tupos;
        tupos++;
        emit adminUserTask(act, fio, listlogins.at(t), task, report);
    }
}

void BaseTask::updateTaskData(quint32 id, QString task, QString describe, QString stDate, QString endDate, QString progress)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::UPDATE_TASK;
           udp.udp.idtask = curID;
           QByteArray ba = task.toUtf8();
           memcpy(udp.udp.task, ba.data(), ba.size());
           ba = describe.toUtf8();
           memcpy(udp.udp.describe, ba.data(), ba.size());
           ba = stDate.toUtf8();
           memcpy(udp.udp.s_data, ba.data(), ba.size());
           ba = endDate.toUtf8();
           memcpy(udp.udp.e_data, ba.data(), ba.size());
           int prog = progress.toUInt();
           if (prog < 0) prog = 0;
           if (prog > 100) prog = 100;
           udp.udp.progress = prog;
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
           return;
       }

    int prog = progress.toUInt();
    if (prog < 0) prog = 0;
    if (prog > 100) prog = 100;
    QString cmd = "task='" + task + "',";
    cmd += "describe='" + describe + "',";
    cmd += "begdata='" + stDate + "',";
    cmd += "enddata='" + endDate+ "',";
    cmd += "prgress=" + QString::number(prog);
    bool res = query.exec("update TaskList set " + cmd + " where id=" + QString::number(id));
    if (!res)
    {
        emit logMistake(query.lastError().text());
    }
}

void BaseTask::deleteTaskData(quint32 id)
{
    bool res = query.exec("delete from TaskList where id=" + QString::number(id));
    if (!res)
    {
        emit logMistake(query.lastError().text());
    }
    bool res2 = query.exec("delete from TaskUser where id=" + QString::number(id));
    if (!res2)
    {
        emit logMistake(query.lastError().text());
    }
    emit emitDelAndUpdate();
}

void BaseTask::changeTaskUser(QString login, QString task)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::UPDATE_USER_TASK;
           udp.udp.idtask = curID;
           QByteArray ba = curlogin.toUtf8();
           memcpy(udp.udp.login, ba.data(), ba.size());
           ba = task.toUtf8();
           memcpy(udp.udp.usertask, ba.data(), ba.size());
           return;
       }

    bool res = query.exec("select * from TaskUser where id=" + QString::number(curID) + " and login='" + login + "'");
    if (!res)
    {
        emit logMistake(query.lastError().text());
        return;
    }
    if (query.next())
    {
        if (!query.exec("update TaskUser set usertask='" + task + "' where id=" + QString::number(curID) + " and login='" + login + "'"))
        {
            emit logMistake(query.lastError().text());
        }

    } else
    {
        //p = query.exec("create table if not exists TaskUser(id int not null, login varchar(128)not null, usertask varchar(4096), userreport varchar(4096))");
        if (!query.exec("insert into TaskUser values(" + QString::number(curID) +
                        ",'" + login + "','" + task + "','')"
                        ))
        {
            emit logMistake(query.lastError().text());
        }
    }
}

void BaseTask::saveReport(QString report)
{
    if (!isInitDB) return;
       if (isClient)
       {
           UDPTask udp;
           udp.udp.taskUDP = DBQuery::UPDATE_REPORT;
           udp.udp.idtask = curID;
           QByteArray ba = curlogin.toUtf8();
           memcpy(udp.udp.login, ba.data(), ba.size());
           ba = report.toUtf8();
           memcpy(udp.udp.userreport, ba.data(), ba.size());
           socket->writeDatagram(udp.bytes, sizeof udp.bytes, serverHost, 8888);
       }

    if (!query.exec("update TaskUser set userreport = '" + report + "' where id=" + QString::number(curID) + " and login='" + curlogin + "'")) // curId и curlogin ранее были сохранены в других методах, без которых данный метод не запуститься
    {
        emit logMistake(query.lastError().text());
    }
}


void BaseTask::serverUDPReceive()
{
    UDPTask udp;
    if (!socket->hasPendingDatagrams())
    {
        return;
    }
    socket->readDatagram(udp.bytes, sizeof udp, &clienHost, &clientport);
    if (udp.udp.taskUDP = DBQuery::INIT_DB)
    {
        udp.udp.correctTask = isInitDB;
        udp.udp.amountTask = listIDTask.size();
        socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
        return;
    }
    if (udp.udp.taskUDP == DBQuery::GET_NEXT_TASK)
    {

        if (pos >= listIDTask.size())return;
        bool p = query.exec("select * from TaskList where id=" + QString::number(listIDTask[udp.udp.pos]));
        if (query.next())
        {
            udp.udp.idtask = query.value(0).toInt();
            QByteArray ba = query.value(1).toString().toUtf8();
            memcpy(udp.udp.task, ba.data(), ba.size());
            ba = query.value(2).toString().toUtf8();
            memcpy(udp.udp.describe, ba.data(), ba.size());
            ba = query.value(3).toString().toUtf8();
            memcpy(udp.udp.s_data, ba.data(), ba.size());
            ba = query.value(4).toString().toUtf8();
            memcpy(udp.udp.e_data, ba.data(), ba.size());
            udp.udp.progress = query.value(5).toInt();
            socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::ADD_NEW_TASK)
    {
        int curAmountTasks = listIDTask.size();
        addNew(QString::fromUtf8(udp.udp.task), QString::fromUtf8(udp.udp.describe), QString::fromUtf8(udp.udp.s_data),
               QString::fromUtf8(udp.udp.e_data), QString::fromUtf8(udp.udp.adminpass));
        if (curAmountTasks < listIDTask.size())
        {
            bool p = query.exec("select * from TaskList where id=" + QString::number(listIDTask[curAmountTasks]));
            if (query.next())
            {
                udp.udp.idtask = query.value(0).toInt();
                QByteArray ba = query.value(1).toString().toUtf8();
                memcpy(udp.udp.task, ba.data(), ba.size());
                ba = query.value(2).toString().toUtf8();
                memcpy(udp.udp.describe, ba.data(), ba.size());
                ba = query.value(3).toString().toUtf8();
                memcpy(udp.udp.s_data, ba.data(), ba.size());
                ba = query.value(4).toString().toUtf8();
                memcpy(udp.udp.e_data, ba.data(), ba.size());
                udp.udp.progress = query.value(5).toInt();
                udp.udp.taskUDP == DBQuery::GET_NEXT_TASK;
                socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
            }
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::GET_NEXT_USER)
    {
        if (udp.udp.pos < listlogins.size())
        {
            bool p = query.exec("select fio from UserList where login='" + listlogins.at(udp.udp.pos) + "'");
            if (p)
            {
                if (query.next())
                {
                    QByteArray ba = udp.udp.fio;
                    memcpy(udp.udp.fio, ba.data(), ba.size());
                    socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
                }
            }
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::ADD_USER)
    {
        udp.udp.taskUDP = DBQuery::GET_NEXT_USER;
        QString fio = QString::fromUtf8(udp.udp.fio);
        QString login = QString::fromUtf8(udp.udp.login);
        QString passwrd = QString::fromUtf8(udp.udp.pass);
        QString apasswrd = QString::fromUtf8(udp.udp.adminpass);
        int curAmountUser = listlogins.size();
        addNewUser(fio, login, passwrd, apasswrd);
        if (curAmountUser = listlogins.size())
        {
            socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::READ_TASK)
    {
        if (query.exec("select * from TaskList where id = " + QString::number(udp.udp.idtask)))
        {
            if (query.next())
            {
                QByteArray ba = query.value(1).toString().toUtf8();
                memcpy(udp.udp.task, ba.data(), ba.size());
                ba = query.value(2).toString().toUtf8();
                memcpy(udp.udp.describe, ba.data(), ba.size());
                ba = query.value(3).toString().toUtf8();
                memcpy(udp.udp.s_data, ba.data(), ba.size());
                ba = query.value(4).toString().toUtf8();
                memcpy(udp.udp.e_data, ba.data(), ba.size());
                udp.udp.progress = query.value(5).toInt();
                socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
            }
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::AUTORIZATION)
    {
        QString login = QString::fromUtf8(udp.udp.login);
        QString passwrd = QString::fromUtf8(udp.udp.pass);
        if (login == "admin" && passwrd == adminPassword)
        {
            udp.udp.taskUDP = DBQuery::ADMIN_MODE;
            socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
            return;
        }
        if (login == "admin" || login.length() == 0 || passwrd.length() == 0) return;
        if (query.exec("select * from UserList where login='" + login + "' and pass='" + passwrd + "'"))
        {
            if (query.next())
            {

                QString fio = query.value("fio").toString();
                query.exec("select * from TaskUser where id=" + QString::number(udp.udp.idtask) + " and login='" + login + "'");
                if (query.next())
                {
                    QString usertask = query.value("usertask").toString();
                    QString report = query.value("userreport").toString();
                    QString mtask = "", describe = "";
                    if (query.exec("select * from TaskList where id=" + QString::number(udp.udp.idtask)))
                    {
                        if (query.next())
                        {
                            mtask = query.value("task").toString();
                            describe = query.value("describe").toString();
                        }
                    } else return;
                    QString info = "Основная задача:" + mtask + "\nОписание:" + describe + "\nВаша задача:" + usertask;
                    // emit setWorkMode(fio, info, report);
                    udp.udp.taskUDP = DBQuery::USER_MODE;
                    QByteArray ba = fio.toUtf8();
                    memcpy(udp.udp.fio, ba.data(),  ba.size());
                    ba = info.toUtf8();
                    memcpy(udp.udp.describe, ba.data(),  ba.size());
                    ba = report.toUtf8();
                    memcpy(udp.udp.userreport, ba.data(),  ba.size());
                    socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
                    return;
                }
            }emit
        }
        return;
    }
    if (udp.udp.taskUDP == DBQuery::USER_TASK_NEXT)
    {
        if (listlogins.size() <= udp.udp.pos) return;
        /***********************************************************/
        bool res = query.exec("select * from TaskUser where id=" + QString::number(udp.udp.idtask));
        if (res)
        {
            QString task = "";
            QString report = "";
            QString fio = "";
            bool act= false;
            while(query.next())
            {
                if (query.value("login").toString() == listlogins.at(udp.udp.pos))
                {
                    act = true;
                    break;
                }
            }
            if (act)
            {
                task = query.value("usertask").toString();
                report = query.value("userreport").toString();
            }
            res = query.exec("select fio from UserList where login='" + listlogins.at(udp.udp.pos) + "'");
            if (res)
            {
                res = query.next();
                if(!res) return;
                fio = query.value("fio").toString();
            } else return;
            // emit adminUserTask(act, fio, listlogins.at(t), task, report);
            udp.udp.correctTask = act;
            QByteArray ba = fio.toUtf8();
            memcpy(udp.udp.fio, ba.data(), ba.size());
            ba = listlogins.at(udp.udp.pos).toUtf8();
            memcpy(udp.udp.login, ba.data(), ba.size());
            ba = task.toUtf8();
            memcpy(udp.udp.usertask, ba.data(), ba.size());
            ba = report.toUtf8();
            memcpy(udp.udp.userreport, ba.data(), ba.size());
            socket->writeDatagram(udp.bytes, sizeof udp, clienHost, clientport);
        }
        /***********************************************************/
        return;
    }
    if (udp.udp.taskUDP == DBQuery::UPDATE_USER_TASK)
    {
        //*****************************************************************
        bool res = query.exec("select * from TaskUser where id=" +
                              QString::number(udp.udp.idtask) + " and login='" + QString::fromUtf8(udp.udp.login) + "'");
        if (!res)
        {
            return;
        }
        if (query.next())
        {
            if (!query.exec("update TaskUser set usertask='" + QString::fromUtf8(udp.udp.usertask) + "' where id=" + QString::number(udp.udp.idtask)
                            + " and login='" + QString::fromUtf8(udp.udp.login) + "'"))
            {
                emit logMistake(query.lastError().text());
            }

        } else
        {
            query.exec("insert into TaskUser values(" + QString::number(udp.udp.idtask) +
                            ",'" + QString::fromUtf8(udp.udp.login) + "','" + QString::fromUtf8(udp.udp.usertask) + "','')");
        }
        //*****************************************************************
        return;
    }
    if (udp.udp.taskUDP == DBQuery::UPDATE_TASK)
    {
        int prog = udp.udp.progress;
        QString cmd = "task='" + QString::fromUtf8(udp.udp.usertask) + "',";
        cmd += "describe='" + QString::fromUtf8(udp.udp.describe) + "',";
        cmd += "begdata='" + QString::fromUtf8(udp.udp.s_data) + "',";
        cmd += "enddata='" + QString::fromUtf8(udp.udp.e_data)+ "',";
        cmd += "prgress=" + QString::number(prog);
        query.exec("update TaskList set " + cmd + " where id=" + QString::number(udp.udp.idtask));
        return;
    }
    if (udp.udp.taskUDP == DBQuery::UPDATE_TASK)
    {
        query.exec("update TaskUser set userreport = '" + QString::fromUtf8(udp.udp.userreport)
                   + "' where id=" + QString::number(udp.udp.idtask) + " and login='" + QString::fromUtf8(udp.udp.login) + "'");
        return;
    }
}


void BaseTask::clientUDPReceive()
{
   UDPTask udp;
   if (udp.udp.taskUDP = DBQuery::INIT_DB)
   {
       emit statusLoadBase(udp.udp.correctTask, udp.udp.amountTask, "");
       pos = 0;
       upos = 0;
       return;
   }
   if (udp.udp.taskUDP == DBQuery::GET_NEXT_TASK)
   {
       emit printData(udp.udp.idtask, QString::fromUtf8(udp.udp.task), QString::fromUtf8(udp.udp.describe),
                      QString::fromUtf8(udp.udp.s_data), QString::fromUtf8(udp.udp.e_data), udp.udp.progress);
       return;
   }
   if (udp.udp.taskUDP == DBQuery::GET_NEXT_USER)
   {
       emit addUserToList(QString(udp.udp.fio));
       return;
   }
   if (udp.udp.taskUDP == DBQuery::READ_TASK)
   {
       curID = udp.udp.idtask;
       tupos = 0;
       emit taskFullInformation(curID, QString::fromUtf8(udp.udp.task), QString::fromUtf8(udp.udp.describe),
                                QString::fromUtf8(udp.udp.s_data), QString::fromUtf8(udp.udp.e_data), udp.udp.progress);
       return;
   }
   if (udp.udp.taskUDP == DBQuery::ADMIN_MODE)
   {
       emit setAdminModeEditTask();
       return;
   }
   if (udp.udp.taskUDP == DBQuery::USER_MODE)
   {
       curlogin = QString::fromUtf8(udp.udp.login);
       emit setWorkMode(QString::fromUtf8(udp.udp.fio), QString::fromUtf8(udp.udp.describe), QString::fromUtf8(udp.udp.userreport));
       return;
   }
   if (udp.udp.taskUDP == DBQuery::USER_TASK_NEXT)
   {
       emit adminUserTask(udp.udp.correctTask, QString::fromUtf8(udp.udp.fio), QString::fromUtf8(udp.udp.login),
                          QString::fromUtf8(udp.udp.usertask), QString::fromUtf8(udp.udp.userreport));
       return;
   }
}


int BaseTask::getY()
{
    return taskY;
}

void BaseTask::incY(int dy)
{
    taskY += dy;
}

