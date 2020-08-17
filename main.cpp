#include "MainWidget.h"
#include <QApplication>
#include "CTcpClientConnection.h"
#include "CFaIcon.h"
#include <QDialog>
#include <QIcon>
#include <QMetaEnum>
#include <QVBoxLayout>
#include "CAdvLogger.h"
#include <QGraphicsDropShadowEffect>
#include <QFile>

void test2();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CAdvLogger::getInstance()->installAdvaLoging();
    CFontInstaller::fontInstaller(":/font/image/font/fontawesome-webfont.ttf");

    QFont globalFont("SimHei",12);
    a.setFont(globalFont);

    /*设置样式*/
//    QFile file(m_strAppPath + "qss/style.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = tr(file.readAll());
//    qApp->setStyleSheet(styleSheet);
//    file.close();

//    test2();

    MainWidget w;
    w.show();


//    w.setStyle(QStyleFactory::create("Windows"));

    return a.exec();
}

void test2()
{


    QFont fontFaIcon("FontAwesome");
    fontFaIcon.setPixelSize(20);

    QFont fontt("SimHei");
    fontt.setPixelSize(10);

    QWidget *pWidgetBg = new QWidget;
    QGridLayout *pGLayout = new QGridLayout(pWidgetBg);

     QMetaEnum enmState = QMetaEnum::fromType<CFaIcon::EnmFaIcon>();

    for(int i = 0; i < enmState.keyCount(); i++){
        QPushButton *pBtn = new QPushButton(pWidgetBg);
        pBtn->setText(QString::number(i)+ "." + CFaIcon::iconsQString(CFaIcon::EnmFaIcon(enmState.value(i))));
        pBtn->setFont(fontFaIcon);
        pBtn->setMinimumSize(10,10);
        pBtn->setStyleSheet("color:#1aa3ff;background:#ffffff;border-radius:3px;");
        pBtn->show();

        QLabel *pLabel = new QLabel(pWidgetBg);
        QString strText = QString(enmState.key(i));
        if(strText.size() > 18){
            strText.insert(18,"\n");
        }
        pLabel->setText(strText);
        pLabel->setFont(fontt);
        pLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *pVLayout = new QVBoxLayout;
        pVLayout->addWidget(pBtn);
        pVLayout->addWidget(pLabel);

        pGLayout->addLayout(pVLayout,i/40,i%40,1,1);
    }

    pWidgetBg->show();

}

