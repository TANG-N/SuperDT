#ifndef NETWORKAPP_H
#define NETWORKAPP_H

#include <QWidget>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>
#include "TCardTitle.h"
#include <QDebug>
#include "TComBoxCardItem.h"
#include "TLockButtonCardItem.h"
#include "TUserCardItem.h"
#include "TLoopTextCardItem.h"
#include "TTriggerCardItem.h"
#include <QList>
#include "CTcpClientConnection.h"
#include "TListCard.h"
#include "TTextEditor.h"
#include "CTcpClientConnection.h"
#include "CTcpServerConnection.h"
#include "CUdpConnection.h"
#include "TLineEditCardItem.h"

#include <QObject>
#include <QVector>
#include <QPair>
#include <QMap>
#include <QScrollArea>
#include <QMap>

class StNetworkConfig
{
public:
    /*会话Id*/
    QString m_strId;

    /*协议参数*/
    QString m_strProcoalType;
    QString m_strIp;
    int m_strPort;
    int m_nNetState;

    /*接收设置*/
    bool m_bSaveAble;
    QString m_strLogFileName;
    QString m_strFilePath;
    bool m_bRecvAble;
    bool m_bRecvHexAble;

    /*发送设置*/
    bool m_bDispalySendAble;   //显示发送
    bool m_bSendHexAble;

    /*高级设置*/
    bool m_bLoopSendAble;
    QVector<QPair<QString,int>> m_vecLoopText; //循环文本条目 <文本，n秒后发送> 不自动排序

    /*触发器*/
    bool m_bTriggerAble; //触发器开关
    QMap<QString,QString> m_mapTrg; //触发列表 <接收文本，发送文本>
};
class NetworkApp : public QWidget
{
    enum EnmConnectType{
        ENM_TCP_CLIENT = 0,
        ENM_TCP_SERVER,
        ENM_UDP,
    };
    enum EnmConnectStatus{
        ENM_STATUS_CLI_CONNECTED = 0,
        ENM_STATUS_CLI_CONNECTING,
        ENM_STATUS_CLI_DISCONNECTED,
        ENM_STATUS_SER_NOT_LISTENING,
        ENM_STATUS_SER_LISTENING,
        ENM_STATUS_SER_CONNECTED,
        ENM_STATUS_UDP_NOT_BINDING,
        ENM_STATUS_UDP_BINDING,
    };

    Q_OBJECT
public:
    explicit NetworkApp(TTextEditor *pTextEditor,QWidget *parent = 0);

    void initUI();
private:
    void createProtocal(TListCard *&pCard);
    void createRecv(TListCard *&pCard);
    void createSend(TListCard *&pCard);
    void createSendText(TListCard *&pCard);
    void createQuickSend(TListCard *&pCard);
    void createTrig(TListCard *&pCard);
    void createAdvaSend(TListCard *&pCard);

    //void addQuickSendItem();
    int getProtocalPort(){return m_pCardItemPort->m_pComBox->currentText().toInt();}
    QString getProtocalIp(){return m_pCardItemIP->m_pComBox->currentText();}
    void setBtnStatus(QPushButton *pBtn,EnmConnectStatus enmStatus);
    int chToChar(char ch);
    QString stringToHexString(QString strMsg);
private:

private slots:
    /*协议槽函数*/
//    void slotRecv(QString strIp,int nPort,QString strMsg);
//    void slotConnectStateChanged(QString strIp,int nPort,bool bState);
private:
    //共用
    QString m_strAppPath;
    QScrollArea *m_pScrollArea = nullptr;
    QTextEdit *m_pTextEdit = nullptr;         //编辑发送内容
    TComBoxCardItem *m_pCardItemIP = nullptr; //协议Ip
    TComBoxCardItem *m_pCardItemPort = nullptr;//协议端口
    TComBoxCardItem *m_pCurrentConnections = nullptr;  //当前所有连接
    StNetworkConfig m_stNetworkConfig;
    TListCard *m_pCardUser = nullptr;           //用户信息卡片
    TListCard *m_pCardProtocol = nullptr;       //网络协议
    TListCard *m_pCardRecv = nullptr;           //接收设置
    TListCard *m_pCardSend = nullptr;           //发送设置
    TListCard *m_pCardQuickSend = nullptr;      //快速发送
    TListCard *m_pCardSendText = nullptr;       //发送编辑区域
    TListCard *m_pCardTrig = nullptr;           //接收触发器
    TListCard *m_pCardAdvaSend = nullptr;       //高级发送

    StNetworkConfig TLineEditCardItemm_stNetworkConfig;
    /*Connection*/
    CTcpClientConnection *m_pTcpClient = nullptr;
    CTcpServerConnection *m_pTcpServer = nullptr;
    CUdpConnection *m_pUdpConnect = nullptr;

    EnmConnectType m_enmProtocolType = ENM_TCP_CLIENT;
    EnmConnectStatus m_enmConnectStatus = ENM_STATUS_CLI_DISCONNECTED;  //初始状态与连接类型对应
    AbsConnection *m_pConnection = nullptr;
    TTextEditor *m_pOutTextEditor = nullptr;  //输出内容显示
    QString m_strCurrentLocalIp = "";   //设置本地ip
    int m_nCurrentLocalPort = 0;        //本地端口
    QString m_strCurrentRemoteIp = "";  //远程ip
    int m_nCurrentRemotePort = 0;       //远程端口
    bool m_bIsConnected = false;
    bool m_bIsConnecting = false;
    /*变长项*/
    QMap<QPushButton*,QListWidgetItem*> m_mapQuckSend;
    QMap<QPushButton*,QListWidgetItem*> m_mapTrigger;
    QMap<QPushButton*,QListWidgetItem*> m_mapLoopSend;  //循环发送

};


#endif // NETWORKAPP_H
