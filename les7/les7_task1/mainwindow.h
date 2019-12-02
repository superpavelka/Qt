#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool edit;
    bool read_only;
    bool hrMode;
    bool parMode;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_save_clicked();
    void on_btn_open_clicked();
    void on_desc_btn_clicked();
    void read_only_switch();
    void print();
    void newlineToBr();
    void paragraphMode();
    void tableIns();
    void fontChange();
    void leftAlign();
    void rightAlign();
    void centerAlign();
    void copyFmt();
    void pasteFmt();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QMenu* m_menu;
    QAction* roAct;
    QAction* printAct;
    QAction* hrAct;
    QAction* parAct;
    QAction* tableInsAct;
    QAction* fontAct;
    QAction* leftAlignAct;
    QAction* rightAlignAct;
    QAction* centerAlignAct;
    QAction* copyFmtAct;
    QAction* pasteFmtAct;
    QMdiArea *mdiArea;
    QTextEdit* te2;
    QTextCharFormat format;
};
#endif // MAINWINDOW_H
