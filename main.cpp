#include "mainwindow.h"
#include <QApplication>

int main(int argc,char *argv[])
{
    QApplication Sorting(argc,argv);
    MainWindow sort;
    sort.show();

    return Sorting.exec();
}
