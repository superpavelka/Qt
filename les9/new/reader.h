#ifndef READER_H
#define READER_H

#include <QObject>
#include <QFile>

class Reader : public QObject
{
   Q_OBJECT
public:
   explicit Reader();
   virtual ~Reader();
   Q_INVOKABLE
   void loadBase();
   Q_INVOKABLE
   void getNextRecord();
   Q_INVOKABLE
   void writeNewInformation(QString, QString, QString, QString, QString, QString);
   Q_INVOKABLE
   void rewriteFile();
private:
   QFile *file;
signals:
   void initEnd(bool succeed);
   void load(QString id, QString task, QString desc, QString date_beg, QString date_end, QString prog);
private slots:
};

#endif // READER_H
