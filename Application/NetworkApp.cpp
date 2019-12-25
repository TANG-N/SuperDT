#include "NetworkApp.h"

NetworkApp::NetworkApp(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void NetworkApp::initUI()
{
    //m_pScrollArea = new QScrollArea(this);
    this->setMinimumHeight(1500);

    /*User Card*/
    TUserCardItem *pUserCard = new TUserCardItem(this);

    TCard *pCardUser = new TCard(this);
    pCardUser->addWidget(pUserCard,"#b9b9b9",100);

    /*通信协议*/
    TCardTitle *pCardTitleProtoal = new TCardTitle(":/image/icon/setting/protocol_n.png","协议设置",this);
    QVector<QString> vecItem;
    vecItem<<"TcpClient"<<"TcpServer"<<"Udp";
    TComBoxCardItem *pCardItemProtocal = new TComBoxCardItem("协议类型",vecItem);
    vecItem.clear();
    vecItem<<"127.0.0.1";
    TComBoxCardItem *pCardItemIP = new TComBoxCardItem("IP地址",vecItem);
    vecItem.clear();
    vecItem<<"8080";
    TComBoxCardItem *pCardItemPort = new TComBoxCardItem("端  口",vecItem);
    QPushButton *pBtnConnect = new QPushButton(this);
    pBtnConnect->setText("连接");

    TCard *pCardProtocal = new TCard(this);
    pCardProtocal->addWidget(pCardItemProtocal);
    pCardProtocal->addWidget(pCardItemIP);
    pCardProtocal->addWidget(pCardItemPort);
    pCardProtocal->addWidget(pBtnConnect,"#30a7f8");

    /*接收设置*/
    TCardTitle *pCardTitleRecv = new TCardTitle(":/image/icon/setting/download_n.png","接收设置",this);
    TLockButtonCardItem *pCItemSaveAble = new TLockButtonCardItem("保存到文件",this);
    vecItem.clear();
    vecItem<<"log.txt"<<"log1.txt"<<"log2.txt";
    TComBoxCardItem *pCItemFileName = new TComBoxCardItem("文件名",vecItem);
    vecItem.clear();
    vecItem<<"../Log";
    TComBoxCardItem *pCItemPath = new TComBoxCardItem("默认路径",vecItem);
    TLockButtonCardItem *pCItemRecvDAble = new TLockButtonCardItem("接收显示",this);
    TLockButtonCardItem *pCItemHexAble = new TLockButtonCardItem("十六进制显示",this);

    TCard *pCardRecv = new TCard(this);
    pCardRecv->addWidget(pCItemSaveAble);
    pCardRecv->addWidget(pCItemFileName);
    pCardRecv->addWidget(pCItemPath);
    pCardRecv->addWidget(pCItemRecvDAble);
    pCardRecv->addWidget(pCItemHexAble);

    /*发送设置*/
    TCardTitle *pCardTitleSend = new TCardTitle(":/image/icon/setting/send_n.png","发送设置",this);
    TLockButtonCardItem *pCItemSendDAble = new TLockButtonCardItem("显示发送",this);
    TLockButtonCardItem *pCItemHexSendAble = new TLockButtonCardItem("十六进制发送",this);

    TCard *pCardSend = new TCard(this);
    pCardSend->addWidget(pCItemSendDAble);
    pCardSend->addWidget(pCItemHexSendAble);

    /*发送*/
    TCardTitle *pCardTitleSendText = new TCardTitle(":/image/icon/setting/send_n.png","发送设置",this);
    QWidget *pWidgetBg = new QWidget(this);
    m_pTextEdit = new QTextEdit(pWidgetBg);
    m_pTextEdit->setStyleSheet("color:#000000;");
    m_pTextEdit->setEnabled(true);
    m_pTextEdit->append("test...");
    QPushButton *pBtnSend = new QPushButton(this);
    pBtnSend->setText("发送");

    TCard *pCardSendText = new TCard(this);
    pCardSendText->addWidget(pWidgetBg,"#ffffff",150);
    pCardSendText->addWidget(pBtnSend,"#30a7f8");

    /*高级发送*/
    TCardTitle *pCardTitleAdvaSend = new TCardTitle(":/image/icon/setting/send_n.png","高级发送",this);
    TLockButtonCardItem *pCItemLoopAble = new TLockButtonCardItem("循环列表",this);

    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
    QPushButton *pBtnAddLoop = new QPushButton(this);
    pBtnAddLoop->setText("+");
    connect(pBtnAddLoop,SIGNAL(clicked(bool)),this,SLOT(slotAddLoop()));

    m_pCardAdvaSend = new TCard(this);
    m_pCardAdvaSend->addWidget(pCItemLoopAble);
    m_pCardAdvaSend->addWidget(pCItemLoopText);
    m_pCardAdvaSend->addWidget(pBtnAddLoop,"#30a7f8");

    /*触发器*/
    TCardTitle *pCardTitleTrig = new TCardTitle(":/image/icon/setting/send_n.png","触发器",this);
    TLockButtonCardItem *pCItemTrigAble = new TLockButtonCardItem("触发器",this);
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
    QPushButton *pBtnAddTrig = new QPushButton(this);
    pBtnAddTrig->setText("+");
    connect(pBtnAddTrig,SIGNAL(clicked()),this,SLOT(slotAddTrig()));

    m_pCardTrig = new TCard(this);
    m_pCardTrig->addWidget(pCItemTrigAble);
    m_pCardTrig->addWidget(pCItemTrig);
    m_pCardTrig->bindDelSig(pCItemTrig);
    m_pCardTrig->addWidget(pBtnAddTrig,"#30a7f8");
    /*布局*/
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(20);
    layout->addWidget(pCardUser);

    layout->addWidget(pCardTitleProtoal);
    layout->addWidget(pCardProtocal);

    layout->addWidget(pCardTitleRecv);
    layout->addWidget(pCardRecv);

    layout->addWidget(pCardTitleSend);
    layout->addWidget(pCardSend);

    layout->addWidget(pCardTitleSendText);
    layout->addWidget(pCardSendText);

    layout->addWidget(pCardTitleAdvaSend);
    layout->addWidget(m_pCardAdvaSend);

    layout->addWidget(pCardTitleTrig);
    layout->addWidget(m_pCardTrig);

    layout->addStretch(1);
    layout->setContentsMargins(2,0,2,0);


    this->setLayout(layout);
}

void NetworkApp::slotAddTrig()
{
    qDebug()<<"add 1";
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);

    qDebug()<<"add 2";
    m_pCardTrig->insert(m_pCardTrig->count()-1,pCItemTrig);
    m_pCardTrig->bindDelSig(pCItemTrig);

    this->resize(this->width(),this->height() + 42);
}

void NetworkApp::slotAddLoop()
{
    qDebug()<<"add l 1";
    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);

    qDebug()<<"add l 2";
    m_pCardAdvaSend->insert(m_pCardTrig->count()-1,pCItemLoopText);
    m_pCardAdvaSend->bindDelSig(pCItemLoopText);

    this->resize(this->width(),this->height() + 42);
}
