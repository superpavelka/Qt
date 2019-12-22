#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPlainTextEdit* te;
    QPlainTextEdit* te2;
    QPlainTextEdit* getPlainTextEdit() {return te;}
    QPlainTextEdit* getPlainTextEdit2() {return te2;}

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
