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

#include "TSessions.h"

enum EnmConnectType{
    ENM_TCP_CLIENT = 0,
    ENM_TCP_SERVER,
    ENM_UDP,
};

enum EnmConnectState{
    ENM_STATE_DISCONNCTED = 0,
    ENM_STATE_CONNECTING,
    ENM_STATE_CONNECTED,
};

class StNetworkConfig
{
public:
    /*会话Id*/
    QString m_strId;

    /*协议参数*/
    EnmConnectType m_enmConnectType;
    EnmConnectState m_enmConnectState;
    QStringList m_strListIp;
    QStringList m_strListPort;
    QString m_strCurrentLocalIp = "";   //设置本地ip
    int m_nCurrentLocalPort = 0;        //本地端口
    QString m_strCurrentRemoteIp = "";  //远程ip
    int m_nCurrentRemotePort = 0;       //远程端口

    /*接收设置*/
    bool m_bSaveAble;
    QString m_strLogFileName;
    QString m_strFilePath;
    bool m_bRecvAble;
    bool m_bRecvHexAble;

    /*发送设置*/
    bool m_bDispalySendAble;   //显示发送
    bool m_bSendHexAble;
    QMap<QString,int> m_mapIpPort; //存储所有的远程连接

    /*快捷发送*/
    QStringList m_strListQuickText; //快捷发送文本项

    /*高级设置*/
    bool m_bLoopSendAble;
    QMap<QString,int> m_mapLoopSend; //循环文本条目 <文本，n秒后发送>

    /*触发器*/
    bool m_bTriggerAble; //触发器开关
    QMap<QString,QString> m_mapTrg; //触发列表 <接收文本，发送文本>
};
class NetworkApp : public QWidget
{
    Q_OBJECT
public:

//    Q_ENUM(EnmConnectState)


public:
    explicit NetworkApp(TSession *pTextEditor,QWidget *parent = 0);

    void initUI();
signals:
    void sigStateChanged(QString strIp,int nIp,bool bIsConnected);
private:
    void initVal(); //先与UI
    void createProtocal(TListCard *&pCard);
    void createRecv(TListCard *&pCard);
    void createSend(TListCard *&pCard);
    void createSendText(TListCard *&pCard);
    void createQuickSend(TListCard *&pCard);
    void createTrig(TListCard *&pCard);
    void createLoopSend(TListCard *&pCard);

    //连接
    void toConnecting();
    void toDisconnect();
    void send(QString strIp,int nPort,QString strMsg);
    void send(QString strMsg);
    //设置远程Ip
    void setRemoteAddress(QString strIp,int nPort);

    void refreshBtn(); //点击按钮
    void refreshUI();
    QString stringToHexString(QString strMsg);

    //
    void addQuickItem(); //添加快捷发送
    void addLoopItem(); //添加循环条目
    void addTrigItem(); //添加触发器条目

    //十六进制字符串转换
    QByteArray hexStr2ByteArray(QString str);
    QString byteArray2HexStr(QByteArray byteArr);
private slots:
    void slotLoop();

private:
    //共用
    QString m_strAppPath;
    StNetworkConfig m_stNetworkConfig;  //所有的设置信息

    //各部分
    TListCard *m_pCardUser = nullptr;           //用户信息卡片
    TListCard *m_pCardProtocol = nullptr;       //网络协议
    TListCard *m_pCardRecv = nullptr;           //接收设置
    TListCard *m_pCardSend = nullptr;           //发送设置
    TListCard *m_pCardQuickSend = nullptr;      //快速发送
    TListCard *m_pCardSendText = nullptr;       //发送编辑区域
    TListCard *m_pCardTrig = nullptr;           //接收触发器
    TListCard *m_pCardAdvaSend = nullptr;       //高级发送

    /*Connection*/
    AbsConnection *m_pConnection = nullptr;
    QPushButton *m_pBtnConnect = nullptr;

    /*协议*/
    TComBoxCardItem *m_pCardItemIP = nullptr; //协议Ip
    TComBoxCardItem *m_pCardItemPort = nullptr;//协议端口


    //发送区域
    QTextEdit *m_pTextEdit = nullptr;         //编辑发送内容
    TSession *m_pOutTextEditor = nullptr;  //输出内容显示
    TComBoxCardItem *m_pCurrentConnections = nullptr;  //当前所有连接  TcpClient不必 显示   因为只有一个发送目标  server和Udp都可选择
    QListWidgetItem *m_pConnectionsItem = nullptr;

    /*变长项*/
    QMap<QPushButton*,QListWidgetItem*> m_mapQuckSend;
    QMap<QPushButton*,QListWidgetItem*> m_mapTrigger;
    QMap<TLoopTextCardItem*,QListWidgetItem*> m_mapLoopSend;  //高级循环发送
    QVector<TLoopTextCardItem *> m_vecLoopItems;

    /*循环发送*/
    QTimer *m_pTimerLoop = nullptr;
    int m_nLoopIndex = 0;
};


#endif // NETWORKAPP_H
