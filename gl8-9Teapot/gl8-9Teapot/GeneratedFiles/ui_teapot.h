/********************************************************************************
** Form generated from reading UI file 'teapot.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAPOT_H
#define UI_TEAPOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeapotClass
{
public:

    void setupUi(QWidget *TeapotClass)
    {
        if (TeapotClass->objectName().isEmpty())
            TeapotClass->setObjectName(QStringLiteral("TeapotClass"));
        TeapotClass->resize(600, 400);

        retranslateUi(TeapotClass);

        QMetaObject::connectSlotsByName(TeapotClass);
    } // setupUi

    void retranslateUi(QWidget *TeapotClass)
    {
        TeapotClass->setWindowTitle(QApplication::translate("TeapotClass", "Teapot", 0));
    } // retranslateUi

};

namespace Ui {
    class TeapotClass: public Ui_TeapotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAPOT_H
