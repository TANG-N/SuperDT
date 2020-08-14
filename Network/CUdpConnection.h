#ifndef CUDPCONNECTION_H
#define CUDPCONNECTION_H

#include "AbsConnection.h"
#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>

class CUdpConnection : public AbsConnection
{
    Q_OBJECT
public:
    explicit CUdpConnection(QObject *parent = nullptr);

    void connect(QString strIp,int nPort);
    void disConnect();
    void send(QString strIp,int nPort,QString strMsg);

    /*先设置远端IP  之后就可以不写Ip  直接发送*/
    void send(QString strMsg);
    void setRemoteAddress(QString strIp,int nPort);
signals:
    void sigRecvLine(QString strIp,int nPort,QString strMsg);
//    void sigRecv(QString strIp,int nPort,QString strMsg);
//    void sigConnectStateChanged(QString strIp,int nPort,bool bState); //无连接的Udp  绑定本地即为已连接
private:
    void init();
private:
    QUdpSocket *m_pUdpSocket = nullptr;
    QString m_strLIp = "";  //本地IP
    int m_nLPort = 9009; //默认端口

    QHostAddress m_hostRemote;  //远程Ip  目标主机Ip
    int m_nRPort = 0;
};

#endif // CUDPCONNECTION_H
