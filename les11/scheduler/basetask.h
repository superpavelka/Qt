
#ifndef BASETASK_H
#define BASETASK_H

#include <QObject>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHash>
#include <QUdpSocket>

struct BData{
   int day, mounth, year;
};
struct DataBase
{
   quint32 idTask;
   QChar task[512];
   QChar discrib[4096];
   BData beginDate, endDate;
   quint8 progress;
};

class BaseTask : public QObject
{
   Q_OBJECT
public:
   explicit BaseTask(QObject *parent = nullptr);

signals:
   void statusLoadBase(bool correct, quint32 amount, QString error);
   void printData(int id, QString task, QString descr, QString begDate, QString endDate, quint32 progress);
   void logMistake(QString msg);
   void emitNextLine();
   void emitDelAndUpdate();
   void addUserToList(QString fio);
   void addUserToCombo(QString fio);
   //void delUserFromList(QString fio);
   void closeUsrWindow(QString fio);
   void taskFullInformation(int id, QString task, QString descr, QString begDate, QString endDate, quint32 progress);
   void setAdminModeEditTask();
   void setWorkMode(QString fio, QString bigTask, QString report);
   void adminUserTask(bool active, QString fio, QString login, QString usertask, QString report);
   void signalAddNewUserCombo(QString fio);
public slots:
   void initBase();
    void initBaseClient(QString ip);
   void updateList();
   void filterList(QString user);
   void getNext();
   int getY();
   void incY(int dy);
   void getLine(int id);
   void addNew(QString task, QString descr, QString begData, QString endData, QString admpass);
   void addNewUser(QString fio, QString login, QString passwrd, QString apasswrd);
   void addNewUserCombo(QString fio);
   void delUser(QString fio, QString login, QString passwrd, QString apasswrd);
   void getFirstUser();
   void getNextUser();
   void getNextUserCombo();
   void autorization(QString login, QString passwrd);
   void updateTaskData(quint32 id, QString task, QString describe, QString stDate, QString endDate, QString progress);
   void deleteTaskData(quint32 id);

   void getFirstUserTask();
   void getNextUserTask();
   void changeTaskUser(QString login, QString task);
   void saveReport(QString report);
   void serverUDPReceive();
   void clientUDPReceive();

private:
   QSqlDatabase database;
   QSqlQuery query;
   // Список задач
   QList<quint32>listIDTask; // Список ID задач
   quint32 pos;              // Текущая задача
   // Список пользователей
   QList<QString>listlogins; // Список пользователей
   quint32 upos;             // Текущей пользователь
   //-----------------------
   quint32 curID;            // Текущая авторизованная задача
   quint32 tupos;            // Позиция пользователей, у которых может быть
                             // доступ к задаче
   QString curlogin;
   int taskY;
   //---------- Сокет ------------
     QUdpSocket *socket;
     bool isInitDB;
     bool isClient;
     QHostAddress serverHost;
     QHostAddress clienHost;
     unsigned short clientport;

};

#endif // BASETASK_H

