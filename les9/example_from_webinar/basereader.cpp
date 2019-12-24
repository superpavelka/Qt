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
   QString town = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString info = QString::fromUtf8(b);
   emit loadTown(town, info);
}

void BaseReader::writeNewInformation(QString town, QString info) // Записываем
{
   QDataStream stream(file);
   auto bytes = town.toUtf8();
   int len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = info.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
}
