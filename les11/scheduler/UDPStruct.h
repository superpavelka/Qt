#ifndef UDPSTRUCT_H
#define UDPSTRUCT_H
#include <QString>
enum DBQuery {INIT_DB = 0x0000, GET_NEXT_TASK = 0x0001, ADD_NEW_TASK = 0x0002, ADD_USER = 0x0003, GET_NEXT_USER = 0x0004,
            AUTORIZATION = 0x0005, ADMIN_MODE = 0x0006, USER_MODE = 0x0007, UPDATE_TASK = 0x0008, USER_TASK_NEXT = 0x0009,
            UPDATE_USER_TASK = 0x000A, UPDATE_REPORT = 0x000B, READ_TASK = 0x000C};
struct UDPTask
{
   union{
       struct {
           DBQuery taskUDP;
           unsigned int amountTask;    // Количество задач
           bool correctTask;           // Успешность операции
           unsigned __int8 progress;   // Прогресс выполнения задачи
           unsigned int idtask;        // ID таблицы TaskList
           unsigned pos;               // Считываемая позиция задачи или
                                       // пользователя
           char task[1024];            // Текст задачи
           char describe[8192];        // Описание задачи
           char adminpass[128];        // Пароль администратора для добавления новых задач и пользователей
           char pass[128];
           char s_data[16];            // Дата начала
           char e_data[16];            // Дата планируемого окончания
           char fio[64];               // ФИО пользователя
           char login[64];             // Логин для входа в окно задачи
           char usertask[4096];        // Задача пользователя
           char userreport[4096];      // Отчет пользователя
       }udp;
       char bytes[sizeof udp];
   };
   UDPTask()
   {
       memset(bytes, 0, sizeof bytes); // При инициализации очищаем структуру
   }
};
#endif // UDPSTRUCT_H
