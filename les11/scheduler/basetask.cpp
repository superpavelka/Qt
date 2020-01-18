#include "basetask.h"
#include <QSqlError>
#include <QVariant>

const QString adminPassword = "123456"; // Пароль администратора
BaseTask::BaseTask(QObject *parent) : QObject(parent)
{
    // Инициализация БД произойдет после загрузки окна QML
}

void BaseTask::initBase()
{
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

       } else
       {
           emit statusLoadBase(false, 0, query.lastError().text());
       }

   }
}


void BaseTask::getNext()
{
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

void BaseTask::addNew(QString task, QString descr, QString begData, QString endData, QString admpass)
{
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
   upos = 0;
   getNextUser();
}

void BaseTask::getNextUser()
{
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

void BaseTask::addNewUser(QString fio, QString login, QString passwrd, QString apasswrd)
{
   if (fio.length() == 0 || login.length() == 0 || passwrd.length() == 0 || apasswrd != adminPassword || login == "admin") return;
   bool user = query.exec("select * from UserList where login='" + login + "'");                                        // Проверяем, нет ли уже такого
                                             // пользователя

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

void BaseTask::getLine(int id)
{
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
   /*
    * bool p = query.exec("create table if not exists TaskList(id int not null,task varchar(256) not null,"
                           "describe varchar(4096),"
                  "begdata varchar(32) not null,enddata varchar(32) not null,prgress int(8) not null)");
   */
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
    emit emitInitBase();
}

void BaseTask::changeTaskUser(QString login, QString task)
{
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
   if (!query.exec("update TaskUser set userreport = '" + report + "' where id=" + QString::number(curID) + " and login='" + curlogin + "'")) // curId и curlogin ранее были сохранены в других методах, без которых данный метод не запуститься
   {
       emit logMistake(query.lastError().text());
   }
}
