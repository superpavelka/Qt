#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicsview.h"
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;
private:
    Ui::MainWindow *ui;
    GraphicsView *view;

    int geometryCounter;
protected:
    void mousePressEvent(QMouseEvent  *event) override;
private slots:
    void reDraw();
};
#endif // MAINWINDOW_H
