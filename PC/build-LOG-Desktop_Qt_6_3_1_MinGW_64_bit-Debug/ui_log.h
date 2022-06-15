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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbPort;
    QTextEdit *txtOutput;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *fileBtn;
    QPushButton *btnConnect;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LOG)
    {
        if (LOG->objectName().isEmpty())
            LOG->setObjectName(QString::fromUtf8("LOG"));
        LOG->resize(668, 600);
        centralwidget = new QWidget(LOG);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 40, 521, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cmbPort = new QComboBox(layoutWidget);
        cmbPort->setObjectName(QString::fromUtf8("cmbPort"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbPort->sizePolicy().hasHeightForWidth());
        cmbPort->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cmbPort);

        txtOutput = new QTextEdit(centralwidget);
        txtOutput->setObjectName(QString::fromUtf8("txtOutput"));
        txtOutput->setGeometry(QRect(50, 130, 581, 161));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 90, 521, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        fileBtn = new QPushButton(layoutWidget1);
        fileBtn->setObjectName(QString::fromUtf8("fileBtn"));

        horizontalLayout_2->addWidget(fileBtn);

        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(250, 310, 171, 29));
        btnConnect->setMinimumSize(QSize(171, 0));
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
        label->setText(QCoreApplication::translate("LOG", "\320\237\320\276\321\200\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("LOG", "\320\244\320\260\320\271\320\273", nullptr));
        fileBtn->setText(QCoreApplication::translate("LOG", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        btnConnect->setText(QCoreApplication::translate("LOG", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LOG: public Ui_LOG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_H
