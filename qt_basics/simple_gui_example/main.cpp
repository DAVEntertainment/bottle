//
// Description: the simple example main file.
//


#include <QApplication>

#include "simple.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ms::demos::Simple s;
    s.show();
    return app.exec();
}
