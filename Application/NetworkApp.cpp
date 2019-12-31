#include "NetworkApp.h"
#include <QApplication>

NetworkApp::NetworkApp(QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";

    initUI();
}

void NetworkApp::initUI()
{
    this->setMinimumHeight(1500);

    /*User Card*/
    TUserCardItem *pUserCard = new TUserCardItem(this);

    m_pCardUser = new TCard(this);
    m_pCardUser->addWidget(pUserCard,QString("#b9b9b9"),100);

    /*通信协议*/
    TCardTitle *pCardTitleProtoal = new TCardTitle(m_strAppPath + "image/setting/protocol_n.png","协议设置",this);
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

    m_pCardProtocal = new TCard(this);
    m_pCardProtocal->addWidget(pCardItemProtocal,true);
    m_pCardProtocal->addWidget(pCardItemIP,true);
    m_pCardProtocal->addWidget(pCardItemPort,true);
    m_pCardProtocal->addWidget(pBtnConnect,QString("#30a7f8"));
    connect(m_pCardProtocal,SIGNAL(sigSettingChanged()),this,SLOT(slotChangeForProtocal()));

    /*接收设置*/
    TCardTitle *pCardTitleRecv = new TCardTitle(m_strAppPath + "image/setting/download_n.png","接收设置",this);
    TLockButtonCardItem *pCItemSaveAble = new TLockButtonCardItem("保存到文件",this);
    vecItem.clear();
    vecItem<<"log.txt"<<"log1.txt"<<"log2.txt";
    TComBoxCardItem *pCItemFileName = new TComBoxCardItem("文件名",vecItem);
    vecItem.clear();
    vecItem<<"../Log";
    TComBoxCardItem *pCItemPath = new TComBoxCardItem("默认路径",vecItem);
    TLockButtonCardItem *pCItemRecvDAble = new TLockButtonCardItem("接收显示",this);
    TLockButtonCardItem *pCItemHexAble = new TLockButtonCardItem("十六进制显示",this);

    m_pCardRecv = new TCard(this);
    m_pCardRecv->addWidget(pCItemSaveAble,true);
    m_pCardRecv->addWidget(pCItemFileName,true);
    m_pCardRecv->addWidget(pCItemPath,true);
    m_pCardRecv->addWidget(pCItemRecvDAble,true);
    m_pCardRecv->addWidget(pCItemHexAble,true);
    connect(m_pCardRecv,SIGNAL(sigSettingChanged()),this,SLOT(slotChangeForRecv()));

    /*发送设置*/
    TCardTitle *pCardTitleSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","发送设置",this);
    TLockButtonCardItem *pCItemSendDAble = new TLockButtonCardItem("显示发送",this);
    TLockButtonCardItem *pCItemHexSendAble = new TLockButtonCardItem("十六进制发送",this);

    m_pCardSend = new TCard(this);
    m_pCardSend->addWidget(pCItemSendDAble,true);
    m_pCardSend->addWidget(pCItemHexSendAble,true);
    connect(m_pCardSend,SIGNAL(sigSettingChanged()),this,SLOT(slotChangeForSend()));
    /*发送*/
    QWidget *pWidgetBg = new QWidget(this);
    m_pTextEdit = new QTextEdit(pWidgetBg);
    m_pTextEdit->setStyleSheet("color:#000000;");
    m_pTextEdit->setEnabled(true);
    m_pTextEdit->append("test...");
    QPushButton *pBtnSend = new QPushButton(this);
    pBtnSend->setText("发送");

    m_pCardSendText = new TCard(this);
    m_pCardSendText->addWidget(pWidgetBg,QString("#ffffff"),150);
    m_pCardSendText->addWidget(pBtnSend,QString("#30a7f8"));

    /*高级发送*/
    TCardTitle *pCardTitleAdvaSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","高级发送",this);
    TLockButtonCardItem *pCItemLoopAble = new TLockButtonCardItem("循环列表",this);

    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
    QPushButton *pBtnAddLoop = new QPushButton(this);
    pBtnAddLoop->setText("+");
    connect(pBtnAddLoop,SIGNAL(clicked(bool)),this,SLOT(slotAddLoop()));

    m_pCardAdvaSend = new TCard(this);
    m_pCardAdvaSend->addWidget(pCItemLoopAble,true);
    m_pCardAdvaSend->addWidget(pCItemLoopText,false,true);
    m_pCardAdvaSend->addWidget(pBtnAddLoop,QString("#30a7f8"));
    connect(m_pCardAdvaSend,SIGNAL(sigSettingChanged()),this,SLOT(slotChangeForAdvaSend()));
    /*触发器*/
    TCardTitle *pCardTitleTrig = new TCardTitle(m_strAppPath + "image/setting/send_n.png","触发器",this);
    TLockButtonCardItem *pCItemTrigAble = new TLockButtonCardItem("触发器",this);
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
    QPushButton *pBtnAddTrig = new QPushButton(this);
    pBtnAddTrig->setText("+");
    connect(pBtnAddTrig,SIGNAL(clicked()),this,SLOT(slotAddTrig()));

    m_pCardTrig = new TCard(this);
    m_pCardTrig->addWidget(pCItemTrigAble,true);
    m_pCardTrig->addWidget(pCItemTrig,false,true);
    m_pCardTrig->addWidget(pBtnAddTrig,QString("#30a7f8"));
    connect(m_pCardAdvaSend,SIGNAL(sigSettingChanged()),this,SLOT(slotChangeForTrig()));
    /*布局*/
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(20);
    layout->addWidget(m_pCardUser);

    layout->addWidget(pCardTitleProtoal);
    layout->addWidget(m_pCardProtocal);

    layout->addWidget(pCardTitleRecv);
    layout->addWidget(m_pCardRecv);

    layout->addWidget(pCardTitleSend);
    layout->addWidget(m_pCardSend);
    layout->addWidget(m_pCardSendText);

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
    m_pCardAdvaSend->insert(m_pCardAdvaSend->count()-1,pCItemLoopText);
    m_pCardAdvaSend->bindDelSig(pCItemLoopText);

    this->resize(this->width(),this->height() + 42);
}

void NetworkApp::slotChangeForProtocal()
{
    qDebug()<<"slotChangeForProtocal";
    qDebug()<<__FUNCTION__;
}

void NetworkApp::slotChangeForRecv()
{
    qDebug()<<__FUNCTION__;
}

void NetworkApp::slotChangeForSend()
{
    qDebug()<<__FUNCTION__;
}

void NetworkApp::slotChangeForSendText()
{
    qDebug()<<__FUNCTION__;
}

void NetworkApp::slotChangeForTrig()
{
    qDebug()<<__FUNCTION__;
}

void NetworkApp::slotChangeForAdvaSend()
{
    qDebug()<<__FUNCTION__;
}
