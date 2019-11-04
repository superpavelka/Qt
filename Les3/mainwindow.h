#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringList undo_list;
    bool edit;
    int cur_undo_pos;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_save_clicked();

    void on_btn_open_clicked();

    void on_btn_undo_clicked();

    void on_btn_redo_clicked();

    void on_desc_btn_clicked();

    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
