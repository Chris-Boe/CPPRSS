#include "mainwindow.h"
#include <QApplication>
//Stars the application and opens the MainWindow.
//a.exec() starts a thread on the window that listens for events and responds
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
