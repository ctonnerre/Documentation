#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpage.h"
#include <QStackedWidget>

mainWindow::mainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);


   /* login = new loginPage();
    QStackedWidget *stackPage = new QStackedWidget;
    stackPage->addWidget(login);
    stackPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stackPage->setCurrentIndex(0);
    stackPage->adjustSize();
*/

}


mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::changerDePage(int index)
{
stackPage->setCurrentIndex(index);
}

