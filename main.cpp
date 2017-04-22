#include "iScissor.h"
#include <QApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    iScissor w;
    w.show();

    return a.exec();
}
