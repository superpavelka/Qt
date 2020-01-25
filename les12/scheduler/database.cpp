#include "basetask.h"
#include <QSqlError>
#include <QVariant>

const QString adminPassword = "JeFiHi"; // Пароль администратора
BaseTask::BaseTask(QObject *parent) : QObject(parent)
{
    // Инициализация БД произойдет после загрузки окна QML
}
