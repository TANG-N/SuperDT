#include "TCenterWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CQuickQss.h"

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
    m_pSessions = new TSessions(this);

    connect(m_pStatusBar,SIGNAL(signalVSplitScreen()),m_pSessions,SLOT(slotVSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalHSplitScreen()),m_pSessions,SLOT(slotHSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalMergeScreen()),m_pSessions,SLOT(slotMergeScreen()));

    connect(m_pSessions,SIGNAL(sigNewSession(TSession *)),this,SLOT(slotNewTextEditor(TSession *)));
    connect(m_pSessions,SIGNAL(sigSelected(TSession *)),this,SLOT(slotSelectedTextEditor(TSession *)));

    /*参数设置区*/
    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setFixedWidth(310);
//    m_pScrollArea->setContentsMargins(5,0,10,0);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
    m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->setFrameShape(QFrame::NoFrame);
    CQuickQss::setScrollBarQss(m_pScrollArea->horizontalScrollBar(),5,5,5);
    /*设置分页*/
    m_pStackWidget = new QStackedWidget(this);
    m_pStackWidget->setStyleSheet("QStackedWidget{background:transparent;}");
    m_pScrollArea->setWidget(m_pStackWidget);

    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(this);
    connect(bar,&TSettingBtnBar::sigCloset,[=](bool bIsClose){
        if(bIsClose)
            m_pScrollArea->hide();
        else
            m_pScrollArea->show();
    });
    m_pNavigationBar = new NetworkApp(m_pSessions->currentTextEditor(),this);
    connect(m_pNavigationBar,SIGNAL(sigStateChanged(QString,int,bool)),
            m_pSessions->currentTextEditor(),SLOT(slotsStateChanged(QString,int,bool)));
    m_pNavigationBar->setContentsMargins(5,0,10,0);
    m_pStackWidget->addWidget(m_pNavigationBar);

    m_pScrollArea->setStyleSheet("background-color:transparent;");//
    QHBoxLayout *pHLayout = new QHBoxLayout;
    pHLayout->setSpacing(0);
    pHLayout->setContentsMargins(0, 0, 0, 0);
    pHLayout->addWidget(m_pSessions);
    pHLayout->addWidget(bar);
    pHLayout->addWidget(m_pScrollArea);


    m_mapTextEdit_App.insert(m_pSessions->currentTextEditor(),m_pNavigationBar);

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
