#include <QApplication>
#include "mainwindow.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginPage w;
        w.show();

        return a.exec();
}
