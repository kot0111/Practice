#include "log.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOG w;
    w.show();
    return a.exec();
}
