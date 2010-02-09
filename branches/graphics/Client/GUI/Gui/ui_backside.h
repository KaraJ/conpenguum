/********************************************************************************
** Form generated from reading UI file 'backside.ui'
**
** Created: Tue Feb 9 12:14:39 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKSIDE_H
#define UI_BACKSIDE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackSide
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *hostName;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;

    void setupUi(QWidget *BackSide)
    {
        if (BackSide->objectName().isEmpty())
            BackSide->setObjectName(QString::fromUtf8("BackSide"));
        BackSide->resize(378, 385);
        verticalLayout_2 = new QVBoxLayout(BackSide);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(BackSide);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        groupBox->setCheckable(true);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        hostName = new QLineEdit(groupBox);
        hostName->setObjectName(QString::fromUtf8("hostName"));

        gridLayout->addWidget(hostName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(groupBox);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));

        gridLayout->addWidget(dateTimeEdit, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setValue(42);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setValue(42);

        horizontalLayout->addWidget(spinBox);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        QWidget::setTabOrder(groupBox, hostName);
        QWidget::setTabOrder(hostName, dateTimeEdit);
        QWidget::setTabOrder(dateTimeEdit, horizontalSlider);
        QWidget::setTabOrder(horizontalSlider, spinBox);

        retranslateUi(BackSide);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(BackSide);
    } // setupUi

    void retranslateUi(QWidget *BackSide)
    {
        BackSide->setWindowTitle(QApplication::translate("BackSide", "BackSide", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("BackSide", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BackSide", "Title:", 0, QApplication::UnicodeUTF8));
        hostName->setText(QApplication::translate("BackSide", "Conpenguum", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BackSide", "Modified:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("BackSide", "Extent", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BackSide: public Ui_BackSide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKSIDE_H
