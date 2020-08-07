#include "TCenterWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

TCenterWidget::TCenterWidget(QWidget *parent) : QWidget(parent)
{
    init();
}

void TCenterWidget::init()
{
//    this->setStyleSheet("border:1px solid red;");
    /*状态栏*/
    m_pStatusBar = new StatusBar(this);

    /*编辑区*/
    m_pMsgArea = new TMsgArea(this);

    connect(m_pStatusBar,SIGNAL(signalVSplitScreen()),m_pMsgArea,SLOT(slotVSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalHSplitScreen()),m_pMsgArea,SLOT(slotHSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalMergeScreen()),m_pMsgArea,SLOT(slotMergeScreen()));

    /*参数设置区*/
    m_pSarea = new QScrollArea(this);
    m_pSarea->setFixedWidth(300);
    m_pSarea->setStyleSheet("background-color:#cccccc;");//QScrollArea{
    m_pSarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    m_pSarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
    m_pSarea->setWidgetResizable(true);

    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    connect(bar,&TSettingBtnBar::sigCloset,[=](bool bIsClose){
        if(bIsClose)
            m_pSarea->hide();
        else
            m_pSarea->show();
    });
    m_pNavigationBar = new NetworkApp(m_pMsgArea->currentTextEditor(),this);
    m_pNavigationBar->setContentsMargins(5,0,5,0);
    m_pSarea->setWidget(m_pNavigationBar);

    QHBoxLayout *pHLayout = new QHBoxLayout;
    pHLayout->setSpacing(0);
    pHLayout->setContentsMargins(0, 0, 0, 0);
    pHLayout->addWidget(m_pMsgArea);
    pHLayout->addWidget(bar);
    pHLayout->addWidget(m_pSarea);


    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);
    pVLayout->addWidget(m_pStatusBar);
    pVLayout->addLayout(pHLayout);
}
