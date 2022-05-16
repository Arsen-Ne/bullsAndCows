#include "bulls_and_cows.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bulls_and_cows w;
    w.show();
    return a.exec();
}
