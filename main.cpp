#include "sipmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SIPMAINWINDOW w;
    w.show();

    return a.exec();
}
