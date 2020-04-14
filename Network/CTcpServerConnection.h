#ifndef CTCPSERVERCONNECTION_H
#define CTCPSERVERCONNECTION_H

#include "AbsConnection.h"
#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>

class CTcpServerConnection : public AbsConnection
{
    Q_OBJECT
public:
    explicit CTcpServerConnection(QObject *parent = nullptr);

    /*扩展接口*/
    void connect(QString strIp,int nPort);
    void disConnect();
    void send(QString strIp,int nPort,QString strMsg);
    void sendAll(QString strMsg);
signals:
    void sigRecvLine(QString strIp,int nPort,QString strMsg);

private:
    void init();
    QString toIpPort(QString strIP,int nPort){return strIP + QString::number(nPort);}
private:
    int m_nMaxReadSize = 1024;

    QTcpServer *m_pTcpServer = nullptr;
    int m_nPort = 0;
    QMap<QString,QTcpSocket *> m_mapConnections;
};

#endif // CTCPSERVERCONNECTION_H
