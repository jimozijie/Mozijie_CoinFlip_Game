#include "mymainwindow.h"
#include "startsence.h"
#include <QApplication>
#include "selectscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MyMainWindow w;
//    w.show();
    //开始场景
    StartSence sc;
    sc.show();
//    SelectScene sc;
//    sc.show();
    return a.exec();
}
