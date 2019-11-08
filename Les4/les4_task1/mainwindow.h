#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

protected:

    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

signals:
    void signal__setTitleText(QString);

private slots:
    void slot__setTitleText(QString);
};
#endif // MAINWINDOW_H
