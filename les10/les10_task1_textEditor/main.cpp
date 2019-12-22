#include "mainwindow.h"
#include "unittest.h"
#include <QApplication>
#include <QtTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new UnitTest(), argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
