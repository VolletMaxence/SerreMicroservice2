#include <QCoreApplication>
#include "MCulTT.h"
#include "TestAplicationMotBus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TestAplicationMotBus w;
    return a.exec();
}

