#include "loginpage.h"
#include "ui_loginpage.h"
#include "mainwindow.h"

loginPage::loginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginPage)
{
    ui->setupUi(this);

}

loginPage::~loginPage()
{
    delete ui;
}

void loginPage::on_validerLog_clicked()
{
    if(ui->loginText->text() == "Axel" && ui->passText->text()== "PassWord")
    {
        ui->LoginPage->setVisible(false);
        ui->page2->setVisible(true);
        ui->identifConst->setText("Identifiant : Axel");
    }
    else
    {
        ui->messageRetour->setText("Mauvaise combinaison !");
    }
}
