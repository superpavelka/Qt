#include "basereader.h"
#include <QDataStream>

BaseReader::BaseReader() : file(nullptr)
{
}
BaseReader::~BaseReader()
{
   if (file) file->close();
}

void BaseReader::loadBase()
{
   file = new QFile("./testbase.bin", this);                 // Файл с данными
                                                             // о городах
   if (!file) return;
   if (!file->open(QIODevice::ReadWrite))
   {
           emit initEnd(false);
           return;
   }
   emit initEnd(true);
}

void BaseReader::getNextRecord()                              // Читаем запись
                                                              // о следующем
                                                              // городе
{
   if (file->atEnd()) return;
   QDataStream stream(file);
   int len = 0;
   stream.readRawData((char*)&len, sizeof len);
   QByteArray b;
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString task_id = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString task = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString info = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString desc = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString datebeg = QString::fromUtf8(b);

   emit loadTown(task_id,task,desc,datebeg);
}

void BaseReader::writeNewInformation(QString task_id, QString task, QString desc, QString datebeg) // Записываем
{
   QDataStream stream(file);
   auto bytes = task_id.toUtf8();
   int len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = task.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = desc.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = datebeg.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
}
