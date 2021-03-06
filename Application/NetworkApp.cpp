﻿#include "NetworkApp.h"
#include <QApplication>
#include "CTcpServerConnection.h"
#include "CUdpConnection.h"
#include "TTreeCard.h"
#include "CConnectTools.h"
#include <QStringList>
#include "CFaIcon.h"

#include "TTabBar.h"
//#include <QHorizonTalLine>

NetworkApp::NetworkApp(TSession *pTextEditor, QWidget *parent)
    : QWidget(parent),m_pOutTextEditor(pTextEditor)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";


    stringToHexString("heello");

    initVal();
    initUI();
    refreshUI();
}

void NetworkApp::initVal()
{
    m_stNetworkConfig.m_bRecvHexAble = false;

    m_stNetworkConfig.m_strListIp = QStringList()<<CConnectTools::getLocalIPv4()<<"127.0.0.1";
    m_stNetworkConfig.m_strListPort = QStringList()<<"3002";
    m_stNetworkConfig.m_strCurrentLocalIp = m_stNetworkConfig.m_strListIp.first();
    m_stNetworkConfig.m_nCurrentLocalPort = QString(m_stNetworkConfig.m_strListPort.first()).toInt();
    m_stNetworkConfig.m_strCurrentRemoteIp = m_stNetworkConfig.m_strCurrentLocalIp;
    m_stNetworkConfig.m_nCurrentRemotePort = m_stNetworkConfig.m_nCurrentLocalPort;
    m_stNetworkConfig.m_enmConnectType = ENM_TCP_CLIENT;
    m_stNetworkConfig.m_enmConnectState = ENM_STATE_DISCONNCTED;
}

void NetworkApp::refreshUI()
{
    m_pCardItemIP->m_pComBox->setCurrentText(m_stNetworkConfig.m_strCurrentLocalIp);
    m_pCardItemPort->m_pComBox->setEditable(m_stNetworkConfig.m_nCurrentLocalPort);

    m_pConnectionsItem->setHidden(true); //默认Tcpclient 时  隐藏此项
}

void NetworkApp::initUI()
{
    /*User Card*/
    //    TUserCardItem *pUserCard = new TUserCardItem(this);
    //    m_pCardUser = new TListCard(this);
    //    m_pCardUser->addWidget(pUserCard);
    //    layout->addWidget(m_pCardUser);

    TTabBar *pTabBar = new TTabBar(this);
    pTabBar->addTab("网络工具",0);
    pTabBar->addTab("串口工具",1);
//    pTabBar->addTab("工具",2);
//    pTabBar->addTab("工具",3);
//    pTabBar->addTab("工具",4);
//    pTabBar->setChecked(2);


    /*通信协议*/
    createProtocal(m_pCardProtocol);
    /*接收设置*/
    createRecv(m_pCardRecv);

    /*发送设置*/
    createSend(m_pCardSend);
    createSendText(m_pCardSendText);

    /*快捷发送*/
    createQuickSend(m_pCardQuickSend);

    /*循环发送*/
    createLoopSend(m_pCardAdvaSend);
    /*触发器*/
    createTrig(m_pCardTrig);

    /*布局*/
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(2,10,2,10);
    layout->addWidget(pTabBar);
    layout->addWidget(m_pCardProtocol);
    layout->addWidget(m_pCardSend);
    layout->addWidget(m_pCardSendText);
    layout->addWidget(m_pCardRecv);
    layout->addWidget(m_pCardQuickSend);
    layout->addWidget(m_pCardAdvaSend);
    layout->addWidget(m_pCardTrig);

    layout->addStretch(4);
}



void NetworkApp::createProtocal(TListCard *&pCard)
{
    TCardTitle *pCardTitleProtoal = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_newspaper_o),"协议设置","选择网络协议",this);

    QStringList vecItem;
    vecItem<<"TCP Client"<<"TCP Server"<<"UDP";

    TComBoxCardItem *pCardItemProtocal = new TComBoxCardItem("协议类型",vecItem);
    //修改网络协议  Tcp client 、Tcp server 、Udp
    connect(pCardItemProtocal->m_pComBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int nIndex){
        m_stNetworkConfig.m_enmConnectType = (EnmConnectType)nIndex;
        //隐藏或显示 目标主机选择
        if(ENM_TCP_CLIENT == m_stNetworkConfig.m_enmConnectType){
            m_pConnectionsItem->setHidden(true);
        }else{
            m_pConnectionsItem->setHidden(false);
        }
        m_stNetworkConfig.m_enmConnectState = ENM_STATE_DISCONNCTED;
        //释放掉原有的链接  @MAJA不用释放貌似也没毛病  真正发起连接的时候去释放、创建和连接
//        if(m_pBtnConnect != nullptr){
//            delete m_pBtnConnect;
//            m_pBtnConnect = nullptr;
//        }
        refreshBtn();
    });

    m_pCardItemIP = new TComBoxCardItem("IP地址",m_stNetworkConfig.m_strListIp);
    m_pCardItemIP->m_pComBox->setEditable(true);
    connect(m_pCardItemIP->m_pComBox,&QComboBox::currentTextChanged,[=](QString strIp){
        switch (m_stNetworkConfig.m_enmConnectType) {
        case ENM_TCP_CLIENT:
            m_stNetworkConfig.m_strCurrentRemoteIp = strIp;
            break;
        case ENM_TCP_SERVER:
            m_stNetworkConfig.m_strCurrentLocalIp = strIp;
            break;
        case ENM_UDP:
            m_stNetworkConfig.m_strCurrentLocalIp = strIp;
            break;
        default:
            qWarning()<<"设置IP 错误的协议";
            break;
        }
    });

    m_pCardItemPort = new TComBoxCardItem("端  口",m_stNetworkConfig.m_strListPort);
    m_pCardItemPort->m_pComBox->setEditable(true);
    connect(m_pCardItemPort->m_pComBox,&QComboBox::currentTextChanged,[=](QString strPort){
        switch (m_stNetworkConfig.m_enmConnectType) {
        case ENM_TCP_CLIENT:
            m_stNetworkConfig.m_nCurrentRemotePort =  strPort.toInt();
            break;
        case ENM_TCP_SERVER:
            m_stNetworkConfig.m_nCurrentLocalPort =  strPort.toInt();
            break;
        case ENM_UDP:
            m_stNetworkConfig.m_nCurrentLocalPort =  strPort.toInt();
            break;
        default:
            qWarning()<<"设置端口 错误的协议";
            break;
        }
    });


    m_pBtnConnect = new QPushButton(this);
    m_pBtnConnect->resize(285,35);
    refreshBtn(); //初始化按钮的颜色
    connect(m_pBtnConnect,&QPushButton::clicked,[=]{
        if(ENM_STATE_DISCONNCTED == m_stNetworkConfig.m_enmConnectState){ //去连接
            toConnecting();
        }else if(ENM_STATE_CONNECTING == m_stNetworkConfig.m_enmConnectState){//去断开
            toDisconnect();
            //不会自然触发断开连接的槽函数  刷新按钮
            m_stNetworkConfig.m_enmConnectState = ENM_STATE_DISCONNCTED;
            refreshBtn();
        }else if(ENM_STATE_CONNECTED == m_stNetworkConfig.m_enmConnectState){//去断开
            toDisconnect();
        }
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleProtoal);
    pCard->addWidget(pCardItemProtocal);
    pCard->addWidget(m_pCardItemIP);
    pCard->addWidget(m_pCardItemPort);
    pCard->addWidget(m_pBtnConnect);
}

void NetworkApp::createRecv(TListCard *&pCard)
{
    TCardTitle *pCardTitleRecv = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_download),"接收设置","接收数据的设置",this);

    /*接收设置*/
    QStringList vecItem;
    TLockButtonCardItem *pCItemSaveAble = new TLockButtonCardItem("保存到文件",this);
    vecItem.clear();
    vecItem<<"log.txt"<<"log1.txt"<<"log2.txt";
    TComBoxCardItem *pCItemFileName = new TComBoxCardItem("文件名",vecItem,this);
    vecItem.clear();
    vecItem<<"../Log";
    TComBoxCardItem *pCItemPath = new TComBoxCardItem("默认路径",vecItem,this);
    TLockButtonCardItem *pCItemRecvDAble = new TLockButtonCardItem("接收显示",this);
    TLockButtonCardItem *pCItemHexAble = new TLockButtonCardItem("十六进制显示",this);
    connect(pCItemHexAble->m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){
        m_stNetworkConfig.m_bRecvHexAble = bIsChecked;
    });
    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleRecv);
    pCard->addWidget(pCItemSaveAble);
    pCard->addWidget(pCItemFileName);
    pCard->addWidget(pCItemPath);
    pCard->addWidget(pCItemRecvDAble);
    pCard->addWidget(pCItemHexAble);
}

void NetworkApp::createSend(TListCard *&pCard)
{
    TCardTitle *pCardTitleSend = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_paper_plane_o),"发送设置","发送设置",this);

    TLockButtonCardItem *pCItemSendDAble = new TLockButtonCardItem("显示发送",this);
    connect(pCItemSendDAble->m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){
        m_stNetworkConfig.m_bDispalySendAble = bIsChecked;
    });
    TLockButtonCardItem *pCItemHexSendAble = new TLockButtonCardItem("十六进制发送",this);
    connect(pCItemHexSendAble->m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){
        m_stNetworkConfig.m_bSendHexAble = bIsChecked;
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleSend);
    pCard->addWidget(pCItemSendDAble);
    pCard->addWidget(pCItemHexSendAble);
}

void NetworkApp::createSendText(TListCard *&pCard)
{
    /*主发送窗口*/
    m_pCurrentConnections = new TComBoxCardItem("目标主机",QStringList());
    m_pCurrentConnections->m_pComBox->setFixedWidth(200);
    m_pCurrentConnections->m_pComBox->setEditable(true);
    connect(m_pCurrentConnections->m_pComBox,&QComboBox::currentTextChanged,[=](QString strIpPort){
        QStringList strList = strIpPort.split(":");
        if(2 == strList.count()){
            m_stNetworkConfig.m_strCurrentRemoteIp = strList.first();
            m_stNetworkConfig.m_nCurrentRemotePort = strList.last().toInt();
            qDebug()<<"重设Remote Ip: "<< m_stNetworkConfig.m_strCurrentRemoteIp <<"Port: "<<m_stNetworkConfig.m_nCurrentRemotePort;
        }
    });

    m_pTextEdit = new QTextEdit(this);
    m_pTextEdit->setStyleSheet("background-color:transparent;color:#000000;border-radius:0px;");
    m_pTextEdit->setEnabled(true);
    m_pTextEdit->append("01 02 1a ff010203f");
    m_pTextEdit->resize(285,200);

    QPushButton *pBtnSend = new QPushButton(this);
    pBtnSend->setText("发送");
    pBtnSend->setAutoRepeat(true); //启用长按
    pBtnSend->setAutoRepeatDelay(400);//触发长按的时间
    pBtnSend->setAutoRepeatInterval(50);//长按时click信号间隔
    pBtnSend->resize(285,35);
    pBtnSend->setStyleSheet("QPushButton{background-color:#30a7f8;border-radius:0px;}"
                            "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnSend,&QPushButton::clicked,[=]{
        QString strText = m_pTextEdit->toPlainText();
        send(strText);
    });

    pCard = new TListCard(this);
    pCard->addWidget(m_pTextEdit);
    m_pConnectionsItem = pCard->addWidget(m_pCurrentConnections);
    pCard->addWidget(pBtnSend);
}

void NetworkApp::createQuickSend(TListCard *&pCard)
{
    TCardTitle *pCardTitleQuickSend = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_fighter_jet),"快捷发送","您可以在这创建快捷发送的内容",this);

    /*快捷发送*/
    QPushButton *pBtnAdd = new QPushButton(this);
    pBtnAdd->setText("+");
    pBtnAdd->resize(285,35);
    pBtnAdd->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                           "QPushButton:pressed{background-color:#2190db;}");


    connect(pBtnAdd,&QPushButton::clicked,[=](){
        TLineEditCardItem *pQuickSendItem = new TLineEditCardItem("发送",this);
        QListWidgetItem *tmpItem = m_pCardQuickSend->insertWidget(m_pCardQuickSend->count() - 1,pQuickSendItem);//添加项之后 需要自动调大高度值
        this->adjustSize();//添加项之后 需要自动调大高度值

        connect(pQuickSendItem->m_pBtn,&QPushButton::clicked,this,[=]{
            qDebug()<<"快捷发送 点击发送"<<pQuickSendItem->m_pLineEdit->text();
            send(pQuickSendItem->m_pLineEdit->text());
        });
        m_mapQuckSend.insert(pQuickSendItem->m_pBtnDel,tmpItem);
        //删除
        connect(pQuickSendItem->m_pBtnDel,&QPushButton::clicked,this,[=]{
            pCard->removeItem(m_mapQuckSend.value(pQuickSendItem->m_pBtnDel)); //@TODO  bugs
        });
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleQuickSend);
    pCard->addWidget(pBtnAdd);
    //emit pBtnAdd->clicked();
}

void NetworkApp::createLoopSend(TListCard *&pCard)
{
    TCardTitle *pCardTitleAdvaSend = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_hourglass_half),"循环发送","加入循环的文本会遍历发送",this);

    /*循环发送定时器*/
    m_pTimerLoop = new QTimer(this);
    connect(m_pTimerLoop,SIGNAL(timeout()),this,SLOT(slotLoop()));

    TLockButtonCardItem *pCItemLoopAble = new TLockButtonCardItem("循环列表",this);
    connect(pCItemLoopAble->m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){ //循环开关
        if(bIsChecked)
            m_pTimerLoop->start(1000);
        else
           m_pTimerLoop->stop();
//        m_nLoopIndex = 0;  //考虑开关时候是否置零
    });
//    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
    QPushButton *pBtnAddLoop = new QPushButton(this);
    pBtnAddLoop->setText("+");
    pBtnAddLoop->resize(285,35);
    pBtnAddLoop->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");

    connect(pBtnAddLoop,&QPushButton::clicked,[this,pCard](){
        addLoopItem();
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleAdvaSend);
    pCard->addWidget(pCItemLoopAble);
//    pCard->addWidget(pCItemLoopText);
    pCard->addWidget(pBtnAddLoop);

}

void NetworkApp::createTrig(TListCard *&pCard)
{
    TCardTitle *pCardTitleTrig = new TCardTitle(CFaIcon::iconsQString(CFaIcon::Fa_slack),"触发器","接收到前边自定的文本，会发送后边自定义的文本回去",this);

    /*触发器开关*/
    TLockButtonCardItem *pCItemTrigAble = new TLockButtonCardItem("触发器",this);
    connect(pCItemTrigAble->m_pBtn,&QPushButton::toggled,[=](bool bIsChecked){
        m_stNetworkConfig.m_bTriggerAble = bIsChecked;
    });
    QPushButton *pBtnAddTrig = new QPushButton(this);
    pBtnAddTrig->setText("+");
    pBtnAddTrig->resize(285,35);
    pBtnAddTrig->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnAddTrig,&QPushButton::clicked,[=](){
        addTrigItem();
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleTrig);
    pCard->addWidget(pCItemTrigAble);
    pCard->addWidget(pBtnAddTrig);
}

void NetworkApp::toConnecting()
{
    if(m_pConnection != nullptr)
        delete  m_pConnection; //删除旧的连接

    //重置连接状态
    m_stNetworkConfig.m_enmConnectState = ENM_STATE_DISCONNCTED;

    switch(m_stNetworkConfig.m_enmConnectType){
        case ENM_TCP_CLIENT:
            qDebug()<<"创建 Tcp 客户端";
            m_pConnection = new CTcpClientConnection(this);
            m_pConnection->connect(m_stNetworkConfig.m_strCurrentRemoteIp,m_stNetworkConfig.m_nCurrentRemotePort); //@BUG 远程ip没有改动的话 需要重新获取

            break;
        case ENM_TCP_SERVER:
            qDebug()<<"创建 Tcp 服务器";
            m_pConnection = new CTcpServerConnection(this);
            m_pConnection->connect(m_stNetworkConfig.m_strCurrentLocalIp,m_stNetworkConfig.m_nCurrentLocalPort);

            break;
        case ENM_UDP:
            qDebug()<<"创建 Udp连接";
            m_pConnection = new CUdpConnection(this);
            m_pConnection->connect(m_stNetworkConfig.m_strCurrentLocalIp,m_stNetworkConfig.m_nCurrentLocalPort);
            break;
        default:
            break;
    }

    connect(m_pConnection,&AbsConnection::sigConnectStateChanged,[=](QString strIp,int nPort,bool bState){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)

        qDebug()<<"连接状态变化： "<<bState;
        emit sigStateChanged(strIp,nPort,bState);

        m_pCardItemPort->m_pComBox->setEnabled(!bState);
//        pCardItemProtocal->m_pComBox->setEnabled(!bState);
        m_pCardItemIP->m_pComBox->setEnabled(!bState);


        m_stNetworkConfig.m_enmConnectState = bState ? ENM_STATE_CONNECTED : ENM_STATE_DISCONNCTED;
        refreshBtn();

    });
    connect(m_pConnection,&AbsConnection::sigRecv,[=](QString strIp,int nPort,QString strMsg){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)

        qDebug()<<"接收到Server 信息"<<strMsg;

        //QByteArray::number(strMsg.toLocal8Bit().toHex().toInt(nullptr,16),16);
        if(m_stNetworkConfig.m_bRecvHexAble)
            m_pOutTextEditor->appendPlainText(stringToHexString(strMsg));
        else
            m_pOutTextEditor->appendPlainText(strMsg);
    });

    m_stNetworkConfig.m_enmConnectState = ENM_STATE_CONNECTING;
    refreshBtn();
}

void NetworkApp::toDisconnect()
{
    if(nullptr != m_pConnection){
        m_pConnection->disConnect();
        delete m_pConnection;
        m_pConnection = nullptr;
    }
}

void NetworkApp::send(QString strIp, int nPort, QString strMsg)
{
    if(m_pConnection != nullptr || m_stNetworkConfig.m_enmConnectState == ENM_STATE_CONNECTED){
        if(m_stNetworkConfig.m_bSendHexAble){
            m_pConnection->send(strIp,nPort,hexStr2ByteArray(strMsg));
        }else{
            m_pConnection->send(strIp,nPort,strMsg);
        }

        if(m_stNetworkConfig.m_bDispalySendAble) //显示我发送的
            m_pOutTextEditor->appendPlainText("[send:]" + strMsg);

        qDebug()<<"发送:"<<strIp << nPort;
    }else{
        qWarning()<<"未连接，不能发送";
    }
}

void NetworkApp::send(QString strMsg)
{
    send(m_stNetworkConfig.m_strCurrentRemoteIp,m_stNetworkConfig.m_nCurrentRemotePort,strMsg);
}

void NetworkApp::setRemoteAddress(QString strIp, int nPort)
{
    m_stNetworkConfig.m_strCurrentRemoteIp = strIp;
    m_stNetworkConfig.m_nCurrentRemotePort = nPort;
}

void NetworkApp::refreshBtn()
{
    QStringList strListText;
    switch(m_stNetworkConfig.m_enmConnectType){
        case ENM_TCP_CLIENT: strListText<<"连接"<<"连接中"<<"断开连接";break;
        case ENM_TCP_SERVER: strListText<<"开始监听"<<"监听中"<<"关闭连接";break;
        case ENM_UDP: strListText<<"开放端口"<<"端口开放中"<<"关闭端口";break;
        default:break;
    }

    QColor color;
    if(ENM_STATE_DISCONNCTED == m_stNetworkConfig.m_enmConnectState){
        color.setNamedColor("#33ccff");
        if(strListText.count() > 0)
            m_pBtnConnect->setText(strListText.at(0));
    }else if(ENM_STATE_CONNECTING == m_stNetworkConfig.m_enmConnectState){
        color.setNamedColor("#FF7D50");
        if(strListText.count() > 1)
            m_pBtnConnect->setText(strListText.at(1));
    }else if(ENM_STATE_CONNECTED == m_stNetworkConfig.m_enmConnectState){
        color.setNamedColor("#ff3333");
        if(strListText.count() > 2)
            m_pBtnConnect->setText(strListText.at(2));
    }

    //根据背景色 降低明度  得到略深的点击色
    QString strBgColor = color.name();
    int nH,nS,nV; //色相 饱和度 明度
    color.getHsv(&nH,&nS,&nV);
    nV -= 20;  //降低明度
    color.setHsv(nH,nS,nV);
    QString strBgColorPressed = color.name();

    m_pBtnConnect->setStyleSheet(QString("QPushButton{background-color:%1;color:%2;border-radius:0px;}"
                                "QPushButton:pressed{background-color:%3;}")
                                 .arg(strBgColor).arg("#ffffff").arg(strBgColorPressed));
}

QString NetworkApp::stringToHexString(QString strMsg)
{
    QString strResult;

    QByteArray arry = strMsg.toUtf8();

    for (int i = 0; i < arry.size(); ++i) {
        strResult += "0x";

        int arrHex[2];
        arrHex[0] = arry[i]/16;
        arrHex[1] = arry[i]%16;

        for(int j = 0; j < (int)(sizeof(arrHex)/sizeof(int)); j++){
            char ch = arrHex[j];
            if ((ch >= 0) && (ch <= 9))
                strResult.append(ch + '0');
            else
                strResult.append(ch + 55);
        }

        strResult += " ";
    }

    return strResult;
}

void NetworkApp::addLoopItem()
{
    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
    m_vecLoopItems.append(pCItemLoopText);
    QListWidgetItem *pItem = m_pCardAdvaSend->insertWidget(m_pCardAdvaSend->count()-1,pCItemLoopText);
    connect(pCItemLoopText->m_pBtnDel,&QPushButton::clicked,this,[=]{
        m_vecLoopItems.removeOne(pCItemLoopText);
        m_pCardAdvaSend->removeItem(pItem);
    });

    this->adjustSize();//添加项之后 需要自动调大高度值
}

void NetworkApp::addTrigItem()
{
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
    connect(m_pConnection,&AbsConnection::sigRecv,[=](QString strIp,int nPort,QString strMsg){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)

        if(!m_stNetworkConfig.m_bTriggerAble) //触发器关闭直接返回
            return ;

        if(pCItemTrig->m_pLineEditR->text() == strMsg){
            send(pCItemTrig->m_pLineEditS->text());
        }
    });
    m_pCardTrig->insertWidget(2,pCItemTrig);
    this->adjustSize();//添加项之后 需要自动调大高度值
}

QByteArray NetworkApp::hexStr2ByteArray(QString str)
{
    QByteArray byteArr;
    str = str.replace(" ",""); //去空格
    if (0 != (str.size() % 2)) {
        str.insert(str.size() - 1,'0'); //不是2的倍数 给最后一个补0 例如: a0 8 ,凑成 a0 08
    }

    for (int nIndex = 0; nIndex < str.size(); nIndex += 2) {
        char ch = QString(str[nIndex]).toInt(nullptr,16) * 16 + QString(str[nIndex + 1]).toInt(nullptr,16);
        byteArr.append(ch);
    }

//    qDebug()<<"reslut:"<<byteArr;
    return byteArr;
}

QString NetworkApp::byteArray2HexStr(QByteArray byteArr)
{
    QString str = byteArr.toHex().toUpper();

    for (int nIndex = 3; nIndex < str.size();nIndex += 3) {
        str = str.insert(nIndex-1," ");
    }

//    qDebug()<<"reslut:"<<str;
    return str;
}

void NetworkApp::slotLoop()
{
    /*循环发送*/
    if((m_vecLoopItems.count() > m_nLoopIndex)){
        QString strText = m_vecLoopItems.at(m_nLoopIndex)->m_pLineEdit->text();
        send(strText);
        qDebug()<<"index:"<<m_nLoopIndex<<"text:"<<strText;

        m_nLoopIndex = (++m_nLoopIndex)%m_vecLoopItems.count();
    }else{
        m_nLoopIndex = 0;
    }
}
