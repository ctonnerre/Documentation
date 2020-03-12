/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginPage
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page2;
    QLabel *identifConst;
    QPushButton *paramBouton;
    QPushButton *mesureBouton;
    QWidget *LoginPage;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *passText;
    QPushButton *validerLog;
    QLineEdit *loginText;
    QLabel *label_2;
    QLabel *label;
    QLabel *messageRetour;

    void setupUi(QDialog *loginPage)
    {
        if (loginPage->objectName().isEmpty())
            loginPage->setObjectName(QStringLiteral("loginPage"));
        loginPage->resize(700, 400);
        stackedWidget = new QStackedWidget(loginPage);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 681, 381));
        page2 = new QWidget();
        page2->setObjectName(QStringLiteral("page2"));
        identifConst = new QLabel(page2);
        identifConst->setObjectName(QStringLiteral("identifConst"));
        identifConst->setGeometry(QRect(90, 40, 181, 21));
        QFont font;
        font.setPointSize(10);
        identifConst->setFont(font);
        paramBouton = new QPushButton(page2);
        paramBouton->setObjectName(QStringLiteral("paramBouton"));
        paramBouton->setGeometry(QRect(200, 110, 311, 41));
        QFont font1;
        font1.setPointSize(15);
        paramBouton->setFont(font1);
        mesureBouton = new QPushButton(page2);
        mesureBouton->setObjectName(QStringLiteral("mesureBouton"));
        mesureBouton->setGeometry(QRect(200, 190, 311, 41));
        mesureBouton->setFont(font1);
        stackedWidget->addWidget(page2);
        LoginPage = new QWidget();
        LoginPage->setObjectName(QStringLiteral("LoginPage"));
        widget = new QWidget(LoginPage);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(140, 50, 461, 251));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        passText = new QLineEdit(widget);
        passText->setObjectName(QStringLiteral("passText"));
        passText->setFont(font1);
        passText->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passText, 3, 0, 1, 1);

        validerLog = new QPushButton(widget);
        validerLog->setObjectName(QStringLiteral("validerLog"));

        gridLayout->addWidget(validerLog, 4, 1, 1, 1);

        loginText = new QLineEdit(widget);
        loginText->setObjectName(QStringLiteral("loginText"));
        loginText->setFont(font1);

        gridLayout->addWidget(loginText, 1, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        messageRetour = new QLabel(widget);
        messageRetour->setObjectName(QStringLiteral("messageRetour"));

        gridLayout->addWidget(messageRetour, 4, 0, 1, 1);

        stackedWidget->addWidget(LoginPage);

        retranslateUi(loginPage);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(loginPage);
    } // setupUi

    void retranslateUi(QDialog *loginPage)
    {
        loginPage->setWindowTitle(QApplication::translate("loginPage", "Dialog", nullptr));
        identifConst->setText(QApplication::translate("loginPage", "Identifiant :", nullptr));
        paramBouton->setText(QApplication::translate("loginPage", "Aller dans les param\303\250tre r\303\251seaux", nullptr));
        mesureBouton->setText(QApplication::translate("loginPage", "Effectuer une nouvelle mesure", nullptr));
        validerLog->setText(QApplication::translate("loginPage", "Valider", nullptr));
        label_2->setText(QApplication::translate("loginPage", "Mot de passe :", nullptr));
        label->setText(QApplication::translate("loginPage", "Identifiant :", nullptr));
        messageRetour->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginPage: public Ui_loginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
