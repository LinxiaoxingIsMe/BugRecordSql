#include "bugrecordpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BugRecordPage w;
    w.show();
    return a.exec();
}
