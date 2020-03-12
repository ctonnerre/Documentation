/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QCheckBox *checkBox;

    void setupUi(QDialog *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(700, 400);
        mainWindow->setAutoFillBackground(true);
        checkBox = new QCheckBox(mainWindow);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(320, 190, 72, 19));

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QDialog *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "Dialog", nullptr));
        checkBox->setText(QApplication::translate("mainWindow", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
