#include "unittest.h"
#include "mainwindow.h"
#include <QMenu>
#include <QtTest>
#include <QDebug>
UnitTest::UnitTest(QObject *parent) : QObject(parent)
{

}

void UnitTest::testGUI()
{
   MainWindow w;
   w.show();

   QTest::keyClicks(w.getPlainTextEdit(), "C:");
   qDebug() << "Отправляем строку C: и смотрим содержимое диска C";
   QString s = w.getPlainTextEdit2()->toPlainText();
   qDebug() << s;

   //QTest::qWait(1000);
   //QTest::keyClick(menu, Qt::Key_Down);
}
