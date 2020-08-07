#include <QDebug>
#include "TSettingArea.h"
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

    m_pMsgArea = new TMsgArea(this);
    connect(this,SIGNAL(signalVSplitScreen()),m_pMsgArea,SLOT(slotVSplitScreen()));
    connect(this,SIGNAL(signalHSplitScreen()),m_pMsgArea,SLOT(slotHSplitScreen()));
    connect(this,SIGNAL(signalMergeScreen()),m_pMsgArea,SLOT(slotMergeScreen()));

    /*参数设置区*/
    m_pSarea = new QScrollArea(this);
    m_pSarea->setFixedWidth(m_nWidgetMainWidth);
    m_pSarea->setMinimumWidth(m_nWidgetMainWidth);
    m_pSarea->setStyleSheet("background-color:#cccccc;");//QScrollArea{
    m_pSarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    m_pSarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条

    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    bar->setFixedWidth(m_nButtonMainWidth);
    connect(bar,&TSettingBtnBar::sigCloset,[=](bool bIsClose){
        if(bIsClose)
            m_pSarea->hide();
        else
            m_pSarea->show();
    });
    m_pNavigationBar = new NetworkApp(m_pMsgArea->currentTextEditor(),this);
    m_pNavigationBar->setContentsMargins(5,0,5,0);
    m_pNavigationBar->setFixedWidth(m_nWidgetMainWidth);
    m_pSarea->setWidget(m_pNavigationBar);

    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(m_pMsgArea);
    m_pHLayout->addWidget(bar);
    m_pHLayout->addWidget(m_pSarea);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);
}
