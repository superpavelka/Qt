#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();
    void updateListDisks();
    void changStatusLabel(QString);
    void printFindFile(QString);

private:
    Ui::MainWindow *ui;
    QStringList disksList;
    int disksLstSize;
    Controller *controllerl;

};
#endif // MAINWINDOW_H
