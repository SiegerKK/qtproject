#include "painter.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Painter w;
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
