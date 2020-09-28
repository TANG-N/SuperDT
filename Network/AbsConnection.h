#ifndef ABSCONNECTION_H
#define ABSCONNECTION_H


/* Func:连接的基类  包含Tcp Udp
 * Note:两种使用方式 继承 和 实例化
 */

#include <QString>
#include <QObject>


class AbsConnection: public QObject
{
    Q_OBJECT
public:
    explicit AbsConnection(QObject *parent = nullptr):QObject(parent){}

    virtual void connect(QString strIp,int nPort) = 0;
    virtual void disConnect() = 0;
    virtual void send(QString strIp,int nPort,QString strMsg) = 0;
    virtual void send(QString strIp,int nPort,QByteArray arrMsg) = 0;
signals:
    void sigRecv(QString strIp,int nPort,QString strMsg);
    void sigConnectStateChanged(QString strIp,int nPort,bool bState);
};

#endif // ABSCONNECTION_H
