/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLineEdit *le_a;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QLineEdit *le_b;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLineEdit *le_c;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *le_x1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *le_x2;
    QPushButton *btn_calc;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(420, 170);
        MainWindow->setMinimumSize(QSize(420, 170));
        MainWindow->setMaximumSize(QSize(420, 170));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 301, 31));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 40, 401, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        le_a = new QLineEdit(horizontalLayoutWidget);
        le_a->setObjectName(QString::fromUtf8("le_a"));

        verticalLayout_4->addWidget(le_a);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_6->addWidget(label_6);

        le_b = new QLineEdit(horizontalLayoutWidget);
        le_b->setObjectName(QString::fromUtf8("le_b"));

        verticalLayout_6->addWidget(le_b);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        le_c = new QLineEdit(horizontalLayoutWidget);
        le_c->setObjectName(QString::fromUtf8("le_c"));

        verticalLayout_5->addWidget(le_c);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        le_x1 = new QLineEdit(horizontalLayoutWidget);
        le_x1->setObjectName(QString::fromUtf8("le_x1"));

        verticalLayout_3->addWidget(le_x1);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        le_x2 = new QLineEdit(horizontalLayoutWidget);
        le_x2->setObjectName(QString::fromUtf8("le_x2"));

        verticalLayout_2->addWidget(le_x2);


        horizontalLayout->addLayout(verticalLayout_2);

        btn_calc = new QPushButton(centralwidget);
        btn_calc->setObjectName(QString::fromUtf8("btn_calc"));
        btn_calc->setGeometry(QRect(170, 100, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 420, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "quadratic equation", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\320\276\320\265\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213 \320\272\320\262\320\260\320\264\321\200\320\260\321\202\320\275\320\276\320\263\320\276 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\321\217 a, b, c", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "a", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "b", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "c", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "x1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "x2", nullptr));
        btn_calc->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
