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



    initUI();
}

void NetworkApp::initUI()
{
    this->setMinimumHeight(1500);

    /*User Card*/
    TUserCardItem *pUserCard = new TUserCardItem(this);

    m_pCardUser = new TListCard(this);
    m_pCardUser->addWidget(pUserCard);

    createProtocal(m_pCardProtocal);
    createRecv(m_pCardRecv);
    createSend(m_pCardSend);
    createSendText(m_pCardSendText);
    createTrig(m_pCardTrig);
    createAdvaSend(m_pCardAdvaSend);

    /*通信协议*/
    TCardTitle *pCardTitleProtoal = new TCardTitle(m_strAppPath + "image/setting/protocol_n.png","协议设置",this);

    /*接收设置*/
    TCardTitle *pCardTitleRecv = new TCardTitle(m_strAppPath + "image/setting/download_n.png","接收设置",this);

    /*发送设置*/
    TCardTitle *pCardTitleSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","发送设置",this);

    /*发送*/

    /*高级发送*/
    TCardTitle *pCardTitleAdvaSend = new TCardTitle(m_strAppPath + "image/setting/send_n.png","高级发送",this);

    /*触发器*/
    TCardTitle *pCardTitleTrig = new TCardTitle(m_strAppPath + "image/setting/send_n.png","触发器",this);
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

    layout->addStretch(4);
    layout->setContentsMargins(2,0,2,0);

    this->setLayout(layout);
}

void NetworkApp::createProtocal(TListCard *&pCard)
{
    QStringList vecItem;
    vecItem<<"TCP Client"<<"TCP Server"<<"UDP";
    TComBoxCardItem *pCardItemProtocal = new TComBoxCardItem("协议类型",vecItem);


    TComBoxCardItem *pCardItemIP = new TComBoxCardItem("IP地址",CConnectTools::getLocalIPv4()<<"127.0.0.1");
    pCardItemIP->m_pComBox->setEditable(true);
    connect(pCardItemIP->m_pComBox,&QComboBox::currentTextChanged,[=](QString strIp){
        m_strCurrentRemoteIp = strIp;
    });
    vecItem.clear();

    vecItem<<"7006";
    TComBoxCardItem *pCardItemPort = new TComBoxCardItem("端  口",vecItem);
    pCardItemPort->m_pComBox->setEditable(true);
    connect(pCardItemPort->m_pComBox,&QComboBox::currentTextChanged,[=](QString strPort){
        m_nCurrentRemotePort = strPort.toInt();
    });
    QPushButton *pBtnConnect = new QPushButton(this);
    pBtnConnect->setText("连接");
    pBtnConnect->resize(285,35);
    pBtnConnect->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                               "QPushButton:pressed{background-color:#2190db;}");
    connect(pBtnConnect,&QPushButton::clicked,[=]{

        qDebug()<<"按下连接按钮";
        if(m_bIsConnect){ //连接成功
            qDebug()<<"断开连接";
            m_pConnection->disConnect();
            m_bIsConnect = false;
            pBtnConnect->setText("连接");
            pBtnConnect->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                                       "QPushButton:pressed{background-color:#2190db;}");
            return;
        }

        m_strCurrentRemoteIp = pCardItemIP->m_pComBox->currentText();
        m_nCurrentRemotePort = pCardItemPort->m_pComBox->currentText().toInt();

        if(nullptr != m_pConnection){
            qDebug()<<"删除旧的socket";
            delete  m_pConnection;
        }

        switch(pCardItemProtocal->m_pComBox->currentIndex()){
        case ENM_TCP_CLIENT:
            qDebug()<<"创建 Tcp 客户端";
            m_pConnection =  new CTcpClientConnection(this);
            break;
        case ENM_TCP_SERVER:
            qDebug()<<"创建 Tcp 服务器";
            m_pConnection =  new CTcpServerConnection(this);
            break;
        case ENM_UDP:
            qDebug()<<"创建 Udp连接";
            m_pConnection =  new CUdpConnection(this);
            break;
        default:
            break;
        }
        qDebug()<<"创建 socket";
        m_pConnection->connect(m_strCurrentRemoteIp,m_nCurrentRemotePort);

        connect(m_pConnection,&AbsConnection::sigConnectStateChanged,[=](QString strIp,int nPort,bool bState){
            Q_UNUSED(strIp)
            Q_UNUSED(nPort)

            qDebug()<<"######  lainjie  Binahua =="<<bState;
            /*IP Port 输入控制*/

            qDebug()<<"连接状态变化 "<<bState;

            pCardItemPort->m_pComBox->setEnabled(!bState);
            pCardItemProtocal->m_pComBox->setEnabled(!bState);
            pCardItemIP->m_pComBox->setEnabled(!bState);

            m_bIsConnect = bState;
            if(bState){ //连接成功

                pBtnConnect->setText("断开连接");
                pBtnConnect->setStyleSheet("QPushButton{background-color:#EE113D;color:#ffffff;border-radius:0px;}"
                                           "QPushButton:pressed{background-color:#2190db;}");
            }else{
                pBtnConnect->setText("连接");
                pBtnConnect->setStyleSheet("QPushButton{background-color:#30a7f8;color:#ffffff;border-radius:0px;}"
                                           "QPushButton:pressed{background-color:#2190db;}");
            }

        });
        connect(m_pConnection,&AbsConnection::sigRecv,[=](QString strIp,int nPort,QString strMsg){
            Q_UNUSED(strIp)
            Q_UNUSED(nPort)

            qDebug()<<"接收到Server 信息"<<strMsg;
            m_pOutTextEditor->appendPlainText(strMsg);
        });

    });





    connect(pCardItemProtocal->m_pComBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int nIndex){
        pCardItemIP->m_pComBox->clear();
        pCardItemIP->m_pComBox->addItems(CConnectTools::getLocalIPv4()<<"127.0.0.1");

        switch (nIndex) {
        case 0:
        {
            pCardItemIP->m_pLabel->setText("目标服务器IP");
            pCardItemPort->m_pLabel->setText("目标端口");
            pBtnConnect->setText("连接");
        }
            break;
        case 1:
        {
            pCardItemIP->m_pLabel->setText("本地服务器IP");
            pCardItemPort->m_pLabel->setText("开放端口");
            pBtnConnect->setText("开始监听");
        }
            break;
        case 2:
        {
            pCardItemIP->m_pLabel->setText("本地IP");
            pCardItemPort->m_pLabel->setText("本地端口");
            pBtnConnect->setText("开始监听");
        }
            break;
        default:
            break;
        }
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCardItemProtocal);
    pCard->addWidget(pCardItemIP);
    pCard->addWidget(pCardItemPort);
    pCard->addWidget(pBtnConnect);
}

void NetworkApp::createRecv(TListCard *&pCard)
{
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
    TLockButtonCardItem *pCItemHexSendAble = new TLockButtonCardItem("十六进制发送",this);

    pCard = new TListCard(this);
    pCard->addWidget(pCItemSendDAble);
    pCard->addWidget(pCItemHexSendAble);
}

void NetworkApp::createSendText(TListCard *&pCard)
{
    /*主发送窗口*/

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
    });

    pCard = new TListCard(this);
    pCard->addWidget(m_pTextEdit);
    pCard->addWidget(pBtnSend);
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
    connect(pBtnAddTrig,&QPushButton::clicked,[this](){
        TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);
        m_pCardTrig->insertWidget(1,pCItemTrig);
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
    });

    pCard = new TListCard(this);
    pCard->addWidget(pCItemLoopAble);
    pCard->addWidget(pCItemLoopText);
    pCard->addWidget(pBtnAddLoop);

}

void NetworkApp::slotAddTrig()
{
    qDebug()<<"add 1";
    TTriggerCardItem *pCItemTrig = new TTriggerCardItem(this);

    qDebug()<<"add 2";
    //    m_pCardTrig->insert(m_pCardTrig->count()-1,pCItemTrig);
    //    m_pCardTrig->bindDelSig(pCItemTrig);

    this->resize(this->width(),this->height() + 42);
}

void NetworkApp::slotAddLoop()
{
    qDebug()<<"add l 1";
    TLoopTextCardItem *pCItemLoopText = new TLoopTextCardItem(this);

    qDebug()<<"add l 2";
    //    m_pCardAdvaSend->insert(m_pCardAdvaSend->count()-1,pCItemLoopText);
    //    m_pCardAdvaSend->bindDelSig(pCItemLoopText);

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

void NetworkApp::slotConnected()
{



    qDebug()<<"连接";
#if 0
    QString strIp = qobject_cast<TComBoxCardItem *>(m_pCardProtocal->at(1))->comBox()->currentText();
    int nPort = qobject_cast<TComBoxCardItem *>(m_pCardProtocal->at(2))->comBox()->currentText().toInt();

    //@TODO 判断IP port是否合法

    int nProIndex = qobject_cast<TComBoxCardItem *>(m_pCardProtocal->at(0))->comBox()->currentIndex();
    switch(nProIndex)
    {
    case 0:
        //Tcp客户端
        break;
    case 1:
        //Tcp服务器
        break;
    case 2:
        //Udp
        break;

    }
#endif
}

void NetworkApp::slotRecv(QString strIp, int nPort, QString strMsg)
{

}

void NetworkApp::slotConnectStateChanged(QString strIp, int nPort, bool bState)
{

}
