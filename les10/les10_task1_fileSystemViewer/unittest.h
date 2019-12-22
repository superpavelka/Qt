#ifndef UNITTEST_H
#define UNITTEST_H

#include <QObject>
#include <QtTest/QTest>

class UnitTest : public QObject
{
   Q_OBJECT
public:
   explicit UnitTest(QObject *parent = nullptr);

signals:

private slots: // Слоты должны быть приватными, иначе работать не будет
   void testGUI();
};
#endif // UNITTEST_H
