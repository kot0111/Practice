/********************************************************************************
** Form generated from reading UI file 'log.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_H
#define UI_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LOG
{
public:
    QWidget *centralwidget;
    QTextEdit *txtOutput;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *fileBtn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbPort;
    QPushButton *btnUpdate;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnConnect;
    QPushButton *btnDisconnect;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LOG)
    {
        if (LOG->objectName().isEmpty())
            LOG->setObjectName(QString::fromUtf8("LOG"));
        LOG->resize(668, 600);
        centralwidget = new QWidget(LOG);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txtOutput = new QTextEdit(centralwidget);
        txtOutput->setObjectName(QString::fromUtf8("txtOutput"));
        txtOutput->setGeometry(QRect(50, 130, 581, 161));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 90, 521, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        fileBtn = new QPushButton(layoutWidget);
        fileBtn->setObjectName(QString::fromUtf8("fileBtn"));

        horizontalLayout_2->addWidget(fileBtn);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(91, 40, 521, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cmbPort = new QComboBox(layoutWidget1);
        cmbPort->setObjectName(QString::fromUtf8("cmbPort"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbPort->sizePolicy().hasHeightForWidth());
        cmbPort->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cmbPort);

        btnUpdate = new QPushButton(layoutWidget1);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));

        horizontalLayout->addWidget(btnUpdate);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 310, 571, 31));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnConnect = new QPushButton(widget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy1);
        btnConnect->setMinimumSize(QSize(171, 0));

        horizontalLayout_3->addWidget(btnConnect);

        btnDisconnect = new QPushButton(widget);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));

        horizontalLayout_3->addWidget(btnDisconnect);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        LOG->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LOG);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 668, 25));
        LOG->setMenuBar(menubar);
        statusbar = new QStatusBar(LOG);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        LOG->setStatusBar(statusbar);

        retranslateUi(LOG);

        QMetaObject::connectSlotsByName(LOG);
    } // setupUi

    void retranslateUi(QMainWindow *LOG)
    {
        LOG->setWindowTitle(QCoreApplication::translate("LOG", "LOG", nullptr));
        label_2->setText(QCoreApplication::translate("LOG", "\320\244\320\260\320\271\320\273", nullptr));
        fileBtn->setText(QCoreApplication::translate("LOG", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("LOG", "\320\237\320\276\321\200\321\202", nullptr));
        btnUpdate->setText(QCoreApplication::translate("LOG", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        btnConnect->setText(QCoreApplication::translate("LOG", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        btnDisconnect->setText(QCoreApplication::translate("LOG", "\320\236\321\202\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        pushButton->setText(QCoreApplication::translate("LOG", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LOG: public Ui_LOG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_H
