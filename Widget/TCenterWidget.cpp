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
    m_pMsgArea = new TSessions(this);

    connect(m_pStatusBar,SIGNAL(signalVSplitScreen()),m_pMsgArea,SLOT(slotVSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalHSplitScreen()),m_pMsgArea,SLOT(slotHSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalMergeScreen()),m_pMsgArea,SLOT(slotMergeScreen()));

    connect(m_pMsgArea,SIGNAL(sigNewTextEditor(TSessions *)),this,SLOT(slotNewTextEditor(TSessions *)));
    connect(m_pMsgArea,SIGNAL(sigCurrentTextEditor(TSessions *)),this,SLOT(slotSelectedTextEditor(TSessions *)));

    /*参数设置区*/
    m_pSarea = new QScrollArea(this);
    m_pSarea->setFixedWidth(300);
//    m_pSarea->setContentsMargins(5,0,10,0);
    m_pSarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
//    m_pSarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
    m_pSarea->setWidgetResizable(true);
    m_pSarea->setFrameShape(QFrame::NoFrame);
    /*设置分页*/
    m_pStackWidget = new QStackedWidget(this);
    m_pStackWidget->setStyleSheet("QStackedWidget{background:transparent;}");
    m_pSarea->setWidget(m_pStackWidget);

    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    connect(bar,&TSettingBtnBar::sigCloset,[=](bool bIsClose){
        if(bIsClose)
            m_pSarea->hide();
        else
            m_pSarea->show();
    });
    m_pNavigationBar = new NetworkApp(m_pMsgArea->currentTextEditor(),this);
    connect(m_pNavigationBar,SIGNAL(sigStateChanged(QString,int,bool)),
            m_pMsgArea->currentTextEditor(),SLOT(slotsStateChanged(QString,int,bool)));
    m_pNavigationBar->setContentsMargins(5,0,10,0);
    m_pStackWidget->addWidget(m_pNavigationBar);

    m_pSarea->setStyleSheet("background-color:transparent;");//
    QHBoxLayout *pHLayout = new QHBoxLayout;
    pHLayout->setSpacing(0);
    pHLayout->setContentsMargins(0, 0, 0, 0);
    pHLayout->addWidget(m_pMsgArea);
    pHLayout->addWidget(bar);
    pHLayout->addWidget(m_pSarea);


    m_mapTextEdit_App.insert(m_pMsgArea->currentTextEditor(),m_pNavigationBar);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);
    pVLayout->addWidget(m_pStatusBar);
    pVLayout->addLayout(pHLayout);
}

void TCenterWidget::slotNewTextEditor(TSession *pTextEditor)
{
    NetworkApp *pNetworkApp = new NetworkApp(pTextEditor,this);
    connect(pNetworkApp,SIGNAL(sigStateChanged(QString,int,bool)),pTextEditor,SLOT(slotsStateChanged(QString ,int ,bool )));
    m_pStackWidget->addWidget(pNetworkApp);
    m_mapTextEdit_App.insert(pTextEditor,pNetworkApp);
}

void TCenterWidget::slotSelectedTextEditor(TSession *pTextEditor)
{
    m_pStackWidget->setCurrentWidget(m_mapTextEdit_App.value(pTextEditor));
}
