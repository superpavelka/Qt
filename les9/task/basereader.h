#ifndef BASEREADER_H
#define BASEREADER_H

#include <QObject>
#include <QFile>

class BaseReader : public QObject
{
   Q_OBJECT
public:
   explicit BaseReader();
   virtual ~BaseReader();
   Q_INVOKABLE
   void loadBase();
   Q_INVOKABLE
   void getNextRecord();
   Q_INVOKABLE
   void writeNewInformation(QString, QString, QString, QString);
private:
   QFile *file;
signals:
   void initEnd(bool succeed);
   void loadTown(QString id, QString task, QString desc, QString date_beg);
private slots:
};

#endif // BASEREADER_H

