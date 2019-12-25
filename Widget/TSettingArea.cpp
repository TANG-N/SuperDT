#include <QDebug>

#include "TSettingArea.h"
#include "TCard.h"
#include "NetworkApp.h"
#include <QGridLayout>
#include <QApplication>

TSettingArea::TSettingArea(QWidget *parent) : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initVal();
    initUI();
}

void TSettingArea::initVal()
{
    m_sIconSize = QSize(32,32);
    m_nWidgetMainWidth = 300;
    m_nButtonMainWidth = m_sIconSize.width() + 10;
}

void TSettingArea::initUI()
{
    /*初始化背景*/
    this->setMaximumWidth(m_nWidgetMainWidth + m_sIconSize.width());
    this->setMinimumWidth(m_nButtonMainWidth);
    this->setFixedWidth(m_nWidgetMainWidth + m_sIconSize.width());

    /*参数设置区*/
    m_pSarea = new QScrollArea(this);
    m_pSarea->setFixedWidth(m_nWidgetMainWidth);
    m_pSarea->setMinimumWidth(m_nWidgetMainWidth);
    m_pSarea->setStyleSheet("background-color:#cccccc;");//QScrollArea{
    m_pSarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    m_pSarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条

//    m_pWidgetSettingArea = new QWidget(this);
//    m_pWidgetSettingArea->setFixedWidth(m_nWidgetMainWidth);
//    m_pWidgetSettingArea->setFixedHeight(650);
//    m_pWidgetSettingArea->setMinimumWidth(m_nWidgetMainWidth);
//    m_pWidgetSettingArea->setStyleSheet("QWidget{background-color:#cccccc;}");


    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    bar->setFixedWidth(m_nButtonMainWidth);
    bar->setMinimumWidth(m_nButtonMainWidth);

    initSettingArea();

    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(bar);
    m_pHLayout->addWidget(m_pSarea);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);
}

void TSettingArea::initSettingArea()
{
    NetworkApp *networkApp = new NetworkApp;
    m_pSarea->setWidget(networkApp);
}

void TSettingArea::slotButtonMain()
{
    qDebug()<<"设置按键";

//    if(m_pWidgetSettingArea->isVisible()){
//        m_pWidgetSettingArea->setVisible(false);
//        this->setFixedWidth(m_nButtonMainWidth);
//    }else{
//        m_pWidgetSettingArea->setVisible(true);
//        this->setFixedWidth(m_nWidgetMainWidth + m_sIconSize.width());
//    }

    static bool bIsOpen = true;
    bIsOpen = !bIsOpen;

    /*设置按钮的图标*/
    if(bIsOpen){
        m_pButtonMain->setStyleSheet(getImageStytle("you.png"));
    }else{
        m_pButtonMain->setStyleSheet(getImageStytle("zuo.png"));
    }

}

QString TSettingArea::getImageStytle(QString strImage)
{
    return "QPushButton {border-image:url(:/image/icon/" + strImage + ")}";
}
