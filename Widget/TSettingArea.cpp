#include <QDebug>

#include "TSettingArea.h"
#include "TCard.h"
#include "NetworkApp.h"
#include <QGridLayout>

TSettingArea::TSettingArea(QWidget *parent) : QWidget(parent)
{
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

    /*设置条*/
//    m_pWidgetButtonArea = new QWidget(this);
//    m_pWidgetButtonArea->setFixedWidth(m_nButtonMainWidth);
//    m_pWidgetButtonArea->setMinimumWidth(m_nButtonMainWidth);


    /*用户信息显示区*/
//    m_pWidgetUserArea = new QWidget(this);
//    m_pWidgetUserArea->setFixedSize(m_nWidgetMainWidth,210);
//    m_pWidgetUserArea->setMinimumWidth(m_nWidgetMainWidth);
//    m_pWidgetUserArea->setStyleSheet("QWidget{background-color:#cccccc;}");

    /*参数设置区*/
    m_pWidgetSettingArea = new QWidget(this);
    m_pWidgetSettingArea->setFixedWidth(m_nWidgetMainWidth);
    m_pWidgetSettingArea->setFixedHeight(650);
    m_pWidgetSettingArea->setMinimumWidth(m_nWidgetMainWidth);
    m_pWidgetSettingArea->setStyleSheet("QWidget{background-color:#cccccc;}");


    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    bar->setFixedWidth(m_nButtonMainWidth);
    bar->setMinimumWidth(m_nButtonMainWidth);
//    initButtonArea();
//    initUserArea();
    initSettingArea();

    QGridLayout *gLayout = new QGridLayout;
    //gLayout->addWidget(m_pWidgetUserArea);
    gLayout->addWidget(m_pWidgetSettingArea);


    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(bar);
    m_pHLayout->addLayout(gLayout);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);
}

void TSettingArea::initUserArea()
{

}

void TSettingArea::initSettingArea()
{

    NetworkApp *networkApp = new NetworkApp(m_pWidgetSettingArea);
    networkApp->resize(m_pWidgetSettingArea->size());
    qDebug()<<"setingarea size"<<m_pWidgetSettingArea->size();
    //networkApp->setFixedWidth(m_nWidgetMainWidth - 10);
}

void TSettingArea::slotButtonMain()
{
    qDebug()<<"设置按键";

    if(m_pWidgetSettingArea->isVisible()){
        m_pWidgetSettingArea->setVisible(false);
        this->setFixedWidth(m_nButtonMainWidth);
    }else{
        m_pWidgetSettingArea->setVisible(true);
        this->setFixedWidth(m_nWidgetMainWidth + m_sIconSize.width());
    }

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
