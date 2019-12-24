#include "reader.h"

#include <QDataStream>

Reader::Reader() : file(nullptr)
{
}
Reader::~Reader()
{
   if (file) file->close();
}

void Reader::loadBase()
{
   file = new QFile("./testbase.bin", this);
   if (!file) return;
   if (!file->open(QIODevice::ReadWrite))
   {
           emit initEnd(false);
           return;
   }
   emit initEnd(true);
}

void Reader::getNextRecord()
{
    if (file->atEnd()) return;
    QDataStream stream(file);
    int len = 0;

    stream.readRawData((char*)&len, sizeof len);
    QByteArray b;
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_id = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_task = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_desc = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_datebeg = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_dateend = QString::fromUtf8(b);

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    QString l_prog = QString::fromUtf8(b);

    emit load(l_id, l_task, l_desc, l_datebeg, l_dateend, l_prog);
}

void Reader::writeNewInformation(QString id, QString task, QString desc, QString date_beg, QString date_end, QString prog) // Записываем
{
   QDataStream stream(file);
   auto bytes = id.toUtf8();
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

   bytes = date_beg.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);

   bytes = date_end.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);

   bytes = prog.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
}

void Reader::rewriteFile()
{
    file->remove();
    file->close();
    file = new QFile("./testbase.bin", this);
    file->open(QIODevice::ReadWrite);
}

