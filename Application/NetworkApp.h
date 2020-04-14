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


class NetworkApp : public QWidget
{
    enum EnmConnectType{
        ENM_TCP_CLIENT = 0,
        ENM_TCP_SERVER,
        ENM_UDP,
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
    void createTrig(TListCard *&pCard);
    void createAdvaSend(TListCard *&pCard);
private:
    QString m_strAppPath;
    QScrollArea *m_pScrollArea;
    QTextEdit *m_pTextEdit; //编辑发送内容

    TListCard *m_pCardUser;
    TListCard *m_pCardProtocal;
    TListCard *m_pCardRecv;
    TListCard *m_pCardSend;
    TListCard *m_pCardSendText;
    TListCard *m_pCardTrig;
    TListCard *m_pCardAdvaSend;

private slots:
    void slotAddTrig();
    void slotAddLoop();

    void slotChangeForProtocal();
    void slotChangeForRecv();
    void slotChangeForSend();
    void slotChangeForSendText();
    void slotChangeForTrig();
    void slotChangeForAdvaSend();

    /*协议槽函数*/
    void slotConnected();

    void slotRecv(QString strIp,int nPort,QString strMsg);
    void slotConnectStateChanged(QString strIp,int nPort,bool bState);
private:

    /*Connection*/
    CTcpClientConnection *m_pTcpClient = nullptr;
    CTcpServerConnection *m_pTcpServer = nullptr;
    CUdpConnection *m_pUdpConnect = nullptr;

    AbsConnection *m_pConnection = nullptr;
    TTextEditor *m_pOutTextEditor = nullptr;  //输出内容显示
    QString m_strCurrentRemoteIp = "";
    int m_nCurrentRemotePort = 0;
    bool m_bIsConnect = false;
};

#endif // NETWORKAPP_H
