#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "loginpage.h"
#include <QStackedWidget>

namespace Ui {
class mainWindow;
}

class mainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

    void changerDePage(int index);

private:
    Ui::mainWindow *ui;
    QStackedWidget *stackPage;
    loginPage *login;

};

#endif // MAINWINDOW_H
