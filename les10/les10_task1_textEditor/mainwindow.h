#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QTextEdit>
#include <QPushButton>

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
    QPushButton* getMenuBtn() {return  btn_menu;}
    QAction* getRoAction() {return roAct;}
    QMenu* getMenu() {return m_menu;}
    QTextEdit* getTextEdit() {return te;}

    ~MainWindow();
    QMenu* m_publ_menu;
    QPushButton* btn_menu;
    QTextEdit* te;
private slots:
    void on_btn_save_clicked();
    void on_btn_open_clicked();
    void on_desc_btn_clicked();
    void read_only_switch();
    void print();
    void newlineToBr();
    void paragraphMode();
    void tableIns();
    void dateIns();
    void timeIns();
    //void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QMenu *m_menu;
    QAction* roAct;
    QAction* printAct;
    QAction* hrAct;
    QAction* parAct;
    QAction* tableInsAct;
    QAction* dateInsAct;
    QAction* timeInsAct;
    QMdiArea *mdiArea;
    QTextEdit* te2;
};
#endif // MAINWINDOW_H
