#include "MainWidget.h"
#include <QApplication>

#include "clog.h"
#include "CTcpClientConnection.h"

void test1();
void test2();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont globalFont("SimHei",12);
    a.setFont(globalFont);

    /*设置样式*/
//    QFile file(m_strAppPath + "qss/style.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = tr(file.readAll());
//    this->setStyleSheet(styleSheet);
//    file.close();

    test2();

    MainWidget w;
    w.show();

    return a.exec();
}

void test2()
{
    //bool ok = CTableLogWin::getInstance()->init();


}
void test1()
{
    bool tb = true;
    char tc = 'C';
    short ts = 234;
    int ti = 12345;
    double td = 12.13141314;
    float tf = 13.123;
    QString tstr = "hello";
    QByteArray tarr("byteayy");

    for(int i = 0; i< 2;i++){
    logFatalWin()<< "ssssssssssssssss" <<tb<<tc<<ts<<ti<<td<<tf<<tstr<<tarr<<flushWin;
    logErrorWin()<< "ssssssssssssssss" <<tb<<tc<<ts<<ti<<td<<tf<<tstr<<tarr<<flushWin;
    logWarnningWin()<< "ssssssssssssssss" <<tb<<tc<<ts<<ti<<td<<tf<<tstr<<tarr<< flushWin;
    logImpInfoWin()<< "ssssssssssssssss" <<tb<<tc<<ts<<ti<<td<<tf<<tstr<<tarr<< flushWin;
    logDebugWin()<< "ssssssssssssssss" <<tb<<tc<<ts<<ti<<td<<tf<<tstr<<tarr<< flushWin;
    }
}
