#include "NetworkApp.h"
#include <QApplication>
#include "CTcpServerConnection.h"
#include "CUdpConnection.h"
#include "TTreeCard.h"
#include "CConnectTools.h"
#include <QStringList>

NetworkApp::NetworkApp(TTextEditor *pTextEditor, QWidget *parent)
    : QWidget(parent),m_pOutTextEditor(pTextEditor)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";


    stringToHexString("heello");
    m_stNetworkConfig.m_bRecvHexAble = false;
    initUI();
}

void NetworkApp::initUI()
{

    this->setFixedWidth(300);
    //this->setMinimumWidth(300);

    /*布局*/
    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addSpacing(20);
    layout->setSpacing(3);
    /*User Card*/
    //    TUserCardItem *pUserCard = new TUserCardItem(this);
    //    m_pCardUser = new TListCard(this);
    //    m_pCardUser->addWidget(pUserCard);
    //    layout->addWidget(m_pCardUser);


    /*通信协议*/
//    TCardTitle *pCardTitleProtoal = new TCardTitle(m_strAppPath + "image/setting/protocol_n.png","协议设置",this);
    createProtocal(m_pCardProtocol);
//    layout->addWidget(pCardTitleProtoal);
    layout->addWidget(m_pCardProtocol);
    /*接收设置*/
    TCardTitle *pCardTitleRecv = new TCardTitle(m_strAppPath + "image/setting/download_n.png","接收设置",this);
    createRecv(m_pCardRecv);
    layout->addWidget(pCardTitleRecv);
    layout->addWidget(m_pCardRecv);

    /*发送设置*/
    TCardTitle *pCardTitleSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","发送设置",this);
    createSend(m_pCardSend);
    createSendText(m_pCardSendText);
    layout->addWidget(pCardTitleSend);
    layout->addWidget(m_pCardSend);
    layout->addWidget(m_pCardSendText);

    /*快捷发送*/
    TCardTitle *pCardTitleQuickSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","快捷发送",this);
    createQuickSend(m_pCardQuickSend);
    layout->addWidget(pCardTitleQuickSend);
    layout->addWidget(m_pCardQuickSend);

    /*高级发送*/
    TCardTitle *pCardTitleAdvaSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","高级发送",this);
    createAdvaSend(m_pCardAdvaSend);
    layout->addWidget(pCardTitleAdvaSend);
    layout->addWidget(m_pCardAdvaSend);
    /*触发器*/
    TCardTitle *pCardTitleTrig = new TCardTitle(m_strAppPath + "image/setting/send_n.png","触发器",this);
    createTrig(m_pCardTrig);
    layout->addWidget(pCardTitleTrig);
    layout->addWidget(m_pCardTrig);


    layout->addStretch(4);
    layout->setContentsMargins(2,0,2,0);

    this->setLayout(layout);
}

void NetworkApp::createProtocal(TListCard *&pCard)
{
    TCardTitle *pCardTitleProtoal = new TCardTitle(m_strAppPath + "image/setting/protocol_n.png","协议设置",this);

    QStringList vecItem;
    vecItem<<"TCP Client"<<"TCP Server"<<"UDP";
    TComBoxCardItem *pCardItemProtocal = new TComBoxCardItem("协议类型",vecItem);
    connect(pCardItemProtocal->m_pComBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int nIndex){
        m_enmProtocolType = (EnmConnectType)nIndex;
    });


    m_pCardItemIP = new TComBoxCardItem("IP地址",CConnectTools::getLocalIPv4()<<"127.0.0.1");
    m_pCardItemIP->m_pComBox->setEditable(true);
    connect(m_pCardItemIP->m_pComBox,&QComboBox::currentTextChanged,[=](QString strIp){
        switch (m_enmProtocolType) {
        case ENM_TCP_CLIENT:
            m_strCurrentRemoteIp = strIp;
            break;
        case ENM_TCP_SERVER:
            m_strCurrentLocalIp = strIp;
            break;
        case ENM_UDP:
            m_strCurrentLocalIp = strIp;
            break;
        default:
            qWarning()<<"设置IP 错误的协议";
            break;
        }
    });
    vecItem.clear();

    vecItem<<"3002";
    m_pCardItemPort = new TComBoxCardItem("端  口",vecItem);
    m_pCardItemPort->m_pComBox->setEditable(true);
    connect(m_pCardItemPort->m_pComBox,&QComboBox::currentTextChanged,[=](QString strPort){
        switch (m_enmProtocolType) {
        case ENM_TCP_CLIENT:
            m_nCurrentRemotePort =  strPort.toInt();
            break;
        case ENM_TCP_SERVER:
            m_nCurrentLocalPort =  strPort.toInt();
            break;
        case ENM_UDP:
            m_nCurrentLocalPort =  strPort.toInt();
            break;
        default:
            qWarning()<<"设置端口 错误的协议";
            break;
        }
    });

    QPushButton *pBtnConnect = new QPushButton(this);
    pBtnConnect->setText("连接");
    pBtnConnect->resize(285,35);
    pBtnConnect->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnConnect,&QPushButton::clicked,[=]{


        qDebug()<<"按下连接按钮";
        if(m_bIsConnected){ //连接成功状态  此时点击  断开操作
            qDebug()<<"断开连接";
            m_pConnection->disConnect();
            m_bIsConnected = false;
            m_bIsConnecting = false;
            setBtnStatus(pBtnConnect,ENM_STATUS_CLI_DISCONNECTED);
            return;
        }else if(m_bIsConnecting && (false == m_bIsConnected)){//未连接成功 连接中  此时点击  断开操作
            m_pConnection->disConnect();
            m_bIsConnected = false;
            m_bIsConnecting = false;
            setBtnStatus(pBtnConnect,ENM_STATUS_CLI_DISCONNECTED);
        }else if((false == m_bIsConnecting) && (false == m_bIsConnected)){


                m_bIsConnecting = true;
                setBtnStatus(pBtnConnect,ENM_STATUS_CLI_CONNECTING);
            if(nullptr != m_pConnection){
                qDebug()<<"删除旧的socket";
                delete  m_pConnection;
            }

            switch(m_enmProtocolType){
            case ENM_TCP_CLIENT:
                qDebug()<<"创建 Tcp 客户端";
                m_strCurrentRemoteIp = getProtocalIp();
                m_nCurrentRemotePort = getProtocalPort();
                m_pConnection =  new CTcpClientConnection(this);
                m_pConnection->connect(m_strCurrentRemoteIp,m_nCurrentRemotePort);
                break;
            case ENM_TCP_SERVER:
                qDebug()<<"创建 Tcp 服务器";
                m_strCurrentLocalIp = getProtocalIp();
                m_nCurrentLocalPort = getProtocalPort();
                m_pConnection =  new CTcpServerConnection(this);
                m_pConnection->connect(m_strCurrentLocalIp,m_nCurrentLocalPort);
                setBtnStatus(pBtnConnect,ENM_STATUS_SER_LISTENING);
                break;
            case ENM_UDP:
                qDebug()<<"创建 Udp连接";
                m_pConnection =  new CUdpConnection(this);
                m_pConnection->connect(m_strCurrentLocalIp,m_nCurrentLocalPort);
                break;
            default:
                break;
            }
            qDebug()<<"创建 socket";


            connect(m_pConnection,&AbsConnection::sigConnectStateChanged,[=](QString strIp,int nPort,bool bState){
                Q_UNUSED(strIp)
                Q_UNUSED(nPort)

                qDebug()<<"######  lainjie  Binahua =="<<bState;
                /*IP Port 输入控制*/

                qDebug()<<"连接状态变化 "<<bState;

                m_pCardItemPort->m_pComBox->setEnabled(!bState);
                pCardItemProtocal->m_pComBox->setEnabled(!bState);
                m_pCardItemIP->m_pComBox->setEnabled(!bState);

                m_bIsConnected = bState;
                if(bState){ //连接成功

                    m_bIsConnecting = false;

                    m_pCurrentConnections->m_pComBox->addItem(strIp + ":" + QString::number(nPort));
                    setBtnStatus(pBtnConnect,ENM_STATUS_CLI_CONNECTED);
                    //                pBtnConnect->setText("断开连接");
                    //                pBtnConnect->setStyleSheet("QPushButton{background-color:#EE113D;color:#ffffff;border-radius:0px;}"
                    //                                           "QPushButton:pressed{background-color:#2190db;}");
                }else{
                    setBtnStatus(pBtnConnect,ENM_STATUS_CLI_DISCONNECTED);
                    //                pBtnConnect->setText("连接");
                    //                pBtnConnect->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                    //                                           "QPushButton:pressed{background-color:#2190db;}");
                }

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
        }

    });



    connect(pCardItemProtocal->m_pComBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int nIndex){
        m_pCardItemIP->m_pComBox->clear();
        m_pCardItemIP->m_pComBox->addItems(CConnectTools::getLocalIPv4()<<"127.0.0.1");

        switch (nIndex) {
        case 0:
        {
            m_pCardItemIP->m_pLabel->setText("目标服务器IP");
            m_pCardItemPort->m_pLabel->setText("目标端口");
            setBtnStatus(pBtnConnect,ENM_STATUS_CLI_DISCONNECTED);
            //pBtnConnect->setText("连接");
        }
            break;
        case 1:
        {
            m_pCardItemIP->m_pLabel->setText("本地服务器IP");
            m_pCardItemPort->m_pLabel->setText("开放端口");
            setBtnStatus(pBtnConnect,ENM_STATUS_SER_NOT_LISTENING);
            //pBtnConnect->setText("开始监听");
        }
            break;
        case 2:
        {
            m_pCardItemIP->m_pLabel->setText("本地IP");
            m_pCardItemPort->m_pLabel->setText("本地端口");
            setBtnStatus(pBtnConnect,ENM_STATUS_UDP_NOT_BINDING);
            //pBtnConnect->setText("开始监听");
        }
            break;
        default:
            break;
        }
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardTitleProtoal);
    pCard->addWidget(pCardItemProtocal);
    pCard->addWidget(m_pCardItemIP);
    pCard->addWidget(m_pCardItemPort);
    pCard->addWidget(pBtnConnect);
}

void NetworkApp::createRecv(TListCard *&pCard)
{
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
    pCard->addWidget(pCItemSaveAble);
    pCard->addWidget(pCItemFileName);
    pCard->addWidget(pCItemPath);
    pCard->addWidget(pCItemRecvDAble);
    pCard->addWidget(pCItemHexAble);
}

void NetworkApp::createSend(TListCard *&pCard)
{
    TLockButtonCardItem *pCItemSendDAble = new TLockButtonCardItem("显示发送",this);
    connect(pCItemSendDAble->m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){
        m_stNetworkConfig.m_bDispalySendAble = bIsChecked;
    });
    TLockButtonCardItem *pCItemHexSendAble = new TLockButtonCardItem("十六进制发送",this);

    pCard = new TListCard(this);
    pCard->addWidget(pCItemSendDAble);
    pCard->addWidget(pCItemHexSendAble);
}

void NetworkApp::createSendText(TListCard *&pCard)
{
    /*主发送窗口*/

    m_pCurrentConnections = new TComBoxCardItem("目标主机",QStringList());
    m_pCurrentConnections->m_pComBox->setFixedWidth(200);
    connect(m_pCurrentConnections->m_pComBox,&QComboBox::currentTextChanged,[=](QString strIpPort){
        QStringList strList = strIpPort.split(":");
        if(2 == strList.count()){
            m_strCurrentRemoteIp = strList.first();
            m_nCurrentRemotePort = strList.last().toInt();
            qDebug()<<"重设Remote Ip: "<< m_strCurrentRemoteIp <<"Port: "<<m_nCurrentRemotePort;
        }
    });

    m_pTextEdit = new QTextEdit(this);
    m_pTextEdit->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:0px;");
    m_pTextEdit->setEnabled(true);
    m_pTextEdit->append("test...");
    m_pTextEdit->resize(285,200);

    QPushButton *pBtnSend = new QPushButton(this);
    pBtnSend->setText("发送");
    pBtnSend->resize(285,35);
    pBtnSend->setStyleSheet("QPushButton{background-color:#30a7f8;border-radius:0px;}"
                            "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnSend,&QPushButton::clicked,[=]{
        QString strText = m_pTextEdit->toPlainText();
        if(m_pConnection != nullptr)
            m_pConnection->send(m_strCurrentRemoteIp,m_nCurrentRemotePort,strText);

        if(m_stNetworkConfig.m_bDispalySendAble) //显示我发送的
            m_pOutTextEditor->appendPlainText("#send:" + strText);
    });

    pCard = new TListCard(this);
    pCard->addWidget(m_pTextEdit);
    pCard->addWidget(m_pCurrentConnections);
    pCard->addWidget(pBtnSend);
}

void NetworkApp::createQuickSend(TListCard *&pCard)
{
    /*快捷发送*/
    QPushButton *pBtnAdd = new QPushButton(this);
    pBtnAdd->setText("+");
    pBtnAdd->resize(285,35);
    pBtnAdd->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                           "QPushButton:pressed{background-color:#2190db;}");


    connect(pBtnAdd,&QPushButton::clicked,[=](){
        TLineEditCardItem *pQuickSendItem = new TLineEditCardItem("发送",this);
        QListWidgetItem *tmpItem = m_pCardQuickSend->insertWidget(0,pQuickSendItem);//添加项之后 需要自动调大高度值
        this->adjustSize();//添加项之后 需要自动调大高度值

        connect(pQuickSendItem->m_pBtn,&QPushButton::clicked,this,[=]{
            qDebug()<<"快捷发送 点击发送"<<pQuickSendItem->m_pLineEdit->text();
            if(m_pConnection != nullptr)
                m_pConnection->send(m_strCurrentRemoteIp,m_nCurrentRemotePort,pQuickSendItem->m_pLineEdit->text());
        });
        m_mapQuckSend.insert(pQuickSendItem->m_pBtnDel,tmpItem);
        connect(pQuickSendItem->m_pBtnDel,&QPushButton::clicked,this,[=]{
            pCard->removeItem(m_mapQuckSend.value(pQuickSendItem->m_pBtnDel)); //@TODO  bugs
        });
    });

    pCard = new TListCard(this);
    pCard->addWidget(pBtnAdd);
    //emit pBtnAdd->clicked();
}

void NetworkApp::createTrig(TListCard *&pCard)
{
    TLockButtonCardItem *pCItemTrigAble = new TLockButtonCardItem("触发器",this);
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
    QPushButton *pBtnAddTrig = new QPushButton(this);
    pBtnAddTrig->setText("+");
    pBtnAddTrig->resize(285,35);
    pBtnAddTrig->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnAddTrig,&QPushButton::clicked,[=](){
        TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
        m_pCardTrig->insertWidget(1,pCItemTrig);
        this->adjustSize();//添加项之后 需要自动调大高度值
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCItemTrigAble);
    pCard->addWidget(pCItemTrig);
    pCard->addWidget(pBtnAddTrig);
}

void NetworkApp::createAdvaSend(TListCard *&pCard)
{
    TLockButtonCardItem *pCItemLoopAble = new TLockButtonCardItem("循环列表",this);

    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
    QPushButton *pBtnAddLoop = new QPushButton(this);
    pBtnAddLoop->setText("+");
    pBtnAddLoop->resize(285,35);
    pBtnAddLoop->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnAddLoop,&QPushButton::clicked,[this](){
        TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);
        m_pCardAdvaSend->insertWidget(1,pCItemLoopText);
        this->adjustSize();//添加项之后 需要自动调大高度值
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCItemLoopAble);
    pCard->addWidget(pCItemLoopText);
    pCard->addWidget(pBtnAddLoop);

}

void NetworkApp::setBtnStatus(QPushButton *pBtn, NetworkApp::EnmConnectStatus enmStatus)
{
    QString strColor = "";
    QString strPressColor = "";
    QString strTextColor = "";
    QString strText = "";
    QColor a;
    switch(enmStatus){
    case ENM_STATUS_CLI_CONNECTED:
        strColor = "#ff6666";  //红
        strPressColor = "#ff3333";
        strText = "断开连接";
        break;
    case ENM_STATUS_CLI_CONNECTING:
        strColor = "#00aa00";  //黄
        strPressColor = "#ff3333";
        strText = "连接中";
        break;
    case ENM_STATUS_CLI_DISCONNECTED:
        strColor = "#33ccff";
        strPressColor = "#00bfff";
        strText = "连接";
        break;
    case ENM_STATUS_SER_NOT_LISTENING:
        strColor = "#33ccff";
        strPressColor = "#00bfff";
        strText = "开始监听";
        break;
    case ENM_STATUS_SER_LISTENING:
        strColor = "#ffff66";
        strPressColor = "#e5e600";
        strText = "停止监听";
        break;
    case ENM_STATUS_SER_CONNECTED:
        strColor = "#ff6666";
        strPressColor = "#ff3333";
        strText = "断开连接";
        break;
    case ENM_STATUS_UDP_NOT_BINDING:
        strColor = "";
        strPressColor = "";
        strText = "绑定";
        break;
    case ENM_STATUS_UDP_BINDING:
        strColor = "";
        strPressColor = "";
        strText = "解除绑定";
        break;
    }

    pBtn->setStyleSheet(QString("QPushButton{background-color:%1;color:%2;border-radius:0px;}"
                                "QPushButton:pressed{background-color:%3;}")
                        .arg(strColor).arg(strTextColor).arg(strPressColor));
    pBtn->setText(strText);
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


//void NetworkApp::slotRecv(QString strIp, int nPort, QString strMsg)
//{

//}

//void NetworkApp::slotConnectStateChanged(QString strIp, int nPort, bool bState)
//{

//}
