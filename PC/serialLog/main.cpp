#include "seriallog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serialLog w;
    w.show();
    return a.exec();
}
