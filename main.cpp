﻿#include "MainWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont globalFont("黑体",12);
    a.setFont(globalFont);

    MainWidget w;
    w.show();

    return a.exec();
}
