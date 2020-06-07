#ifndef CTCPCLIENTCONNECTION_H
#define CTCPCLIENTCONNECTION_H

/* Func:实现一个TcpClent  包含自动重连 排队发送
 * Note:2种使用方法
 *      1.继承该类  重载接收和连接变化虚函数 即可接收 消息  connect（ip port） 发起连接
 *      2.实例化该类  绑定接收信号 状态变化信号  用来接收信息和捕获连接变化
 */


#include "AbsConnection.h"
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QQueue>


class CTcpClientConnection : public AbsConnection
{
    Q_OBJECT
public:
    explicit CTcpClientConnection(QObject *parent = nullptr);

    void connect(QString strIp,int nPort) override;
    void disConnect() override;
    void send(QString strIp,int nPort,QString strMsg) override;

    void setIpPort(QString strIp,int nPort);
    void setEnableQueue(bool bIsOpen){m_bIsOpenQueue = bIsOpen;} //开关消息队列
    void setQueueSPan(int nMs){m_nMsgSpan = nMs;m_pTimerQueue->setInterval(m_nMsgSpan);} //消息队列时间间隔
signals:
    void sigRecvLine(QString strMsg);
private slots:
    void slotReConnection();
private:
    void init();
    void initQueue();
private:
    int m_nMsgSpan = 0;             //两条消息之间的最小时间间隔 ms
    int m_nMaxReadSize = 1024;      //每次最多读取的字节数
    int m_nReConnectionSpan = 3000; //重连时间间隔

    QString m_strIp = "";
    int  m_nPort = 0;

    QTcpSocket *m_pTcpSocket = nullptr;
    QHostAddress *m_pServerIp = nullptr;
    bool m_bIsConnected = false;
    QTimer *m_pTimerReconnection = nullptr;

    /*消息队列*/
    bool m_bIsOpenQueue = false; //只要初始化  就会开启
    QTimer *m_pTimerQueue = nullptr;
    QQueue<QString> m_queueMsg;
};

#endif // CTCPCLIENTCONNECTION_H
