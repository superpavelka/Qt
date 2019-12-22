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
   //QTest::mousePress(w.getMenuBtn(), Qt::LeftButton);
   //QTest::mousePress(w.getRoAction(), Qt::LeftButton);
   QMenu* menu = w.getMenu();
   QTest::keyClick(menu, Qt::Key_Enter);
   QList<QAction *> actions = menu->actions();

   QTest::keyClicks(w.getTextEdit(), "");
   qDebug() << "Отправляем символ T и тест пройден";
   QTest::keyClicks(w.getTextEdit(), "T");
   QCOMPARE(w.getTextEdit()->toPlainText(), "T");
   qDebug() << "Удаляем символ T";
   QTest::keyClick(w.getTextEdit(), Qt::Key_Backspace);

   foreach (QAction *action, actions) {
       qDebug() << action->text();
       if (action->text() == "Только чтение(ВКЛ)") {
           QTest::keyClick(menu, Qt::Key_Enter);
           qDebug() << "Включили режим только чтение";
           break;
       }
   }
   qDebug() << "Отправляем строку Test";
   QTest::keyClicks(w.getTextEdit(), "Test");
   qDebug() << "Проверяем пустую строку и тест пройден";
   QCOMPARE(w.getTextEdit()->toPlainText(), "");
   qDebug() << "ПРоверяем строку Test и тест не пройден";
   QCOMPARE(w.getTextEdit()->toPlainText(), "Test");

   //QTest::qWait(1000);
   //QTest::keyClick(menu, Qt::Key_Down);
}

