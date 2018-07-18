#include "mainwindow.h"
#include <QApplication>
#include "category_man.h"
int main(int argc, char *argv[])
{
    //category_man cat;

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();

}
