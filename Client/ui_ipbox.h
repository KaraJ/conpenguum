/********************************************************************************
** Form generated from reading UI file 'ipbox.ui'
**
** Created: Sat Mar 20 20:16:54 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPBOX_H
#define UI_IPBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IpBox
{
public:
    QPushButton *okbutton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *ipentry;
    QLineEdit *portentry;
    QLineEdit *nameentry;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *iplabel;
    QLabel *portlabel;
    QLabel *namelabel;

    void setupUi(QDialog *IpBox)
    {
        if (IpBox->objectName().isEmpty())
            IpBox->setObjectName(QString::fromUtf8("IpBox"));
        IpBox->resize(235, 191);
        IpBox->setMaximumSize(QSize(235, 191));
        okbutton = new QPushButton(IpBox);
        okbutton->setObjectName(QString::fromUtf8("okbutton"));
        okbutton->setGeometry(QRect(140, 160, 85, 27));
        widget = new QWidget(IpBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(64, 30, 131, 89));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ipentry = new QLineEdit(widget);
        ipentry->setObjectName(QString::fromUtf8("ipentry"));

        verticalLayout->addWidget(ipentry);

        portentry = new QLineEdit(widget);
        portentry->setObjectName(QString::fromUtf8("portentry"));

        verticalLayout->addWidget(portentry);

        nameentry = new QLineEdit(widget);
        nameentry->setObjectName(QString::fromUtf8("nameentry"));

        verticalLayout->addWidget(nameentry);

        widget1 = new QWidget(IpBox);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(20, 30, 40, 91));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        iplabel = new QLabel(widget1);
        iplabel->setObjectName(QString::fromUtf8("iplabel"));

        verticalLayout_2->addWidget(iplabel);

        portlabel = new QLabel(widget1);
        portlabel->setObjectName(QString::fromUtf8("portlabel"));

        verticalLayout_2->addWidget(portlabel);

        namelabel = new QLabel(widget1);
        namelabel->setObjectName(QString::fromUtf8("namelabel"));

        verticalLayout_2->addWidget(namelabel);


        retranslateUi(IpBox);

        QMetaObject::connectSlotsByName(IpBox);
    } // setupUi

    void retranslateUi(QDialog *IpBox)
    {
        IpBox->setWindowTitle(QApplication::translate("IpBox", "IpBox", 0, QApplication::UnicodeUTF8));
        okbutton->setText(QApplication::translate("IpBox", "OK", 0, QApplication::UnicodeUTF8));
        nameentry->setText(QString());
        iplabel->setText(QApplication::translate("IpBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">IP:</p></body></html>", 0, QApplication::UnicodeUTF8));
        portlabel->setText(QApplication::translate("IpBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Port:</p></body></html>", 0, QApplication::UnicodeUTF8));
        namelabel->setText(QApplication::translate("IpBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Name:</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IpBox: public Ui_IpBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPBOX_H
