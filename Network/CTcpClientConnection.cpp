#include "CTcpClientConnection.h"

CTcpClientConnection::CTcpClientConnection(QObject *parent)
    : AbsConnection(parent)
{
    init();
}

void CTcpClientConnection::connect(QString strIp, int nPort)
{
    setIpPort(strIp,nPort);

    slotReConnection();
    if(!m_pTimerReconnection->isActive()){
        m_pTimerReconnection->start();
    }
}

void CTcpClientConnection::disConnect()
{
    m_pTcpSocket->disconnectFromHost();
    if(m_pTimerReconnection->isActive()){
        m_pTimerReconnection->stop();
    }
}

void CTcpClientConnection::send(QString strIp, int nPort, QString strMsg)
{
    send(strIp,nPort,strMsg.toUtf8());
}

void CTcpClientConnection::send(QString strIp, int nPort, QByteArray arrMsg)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    m_pTcpSocket->write(arrMsg);
}

void CTcpClientConnection::setIpPort(QString strIp, int nPort)
{
    m_strIp = strIp;
    m_nPort = nPort;

    m_pServerIp->setAddress(m_strIp);
}

void CTcpClientConnection::slotReConnection()
{
    if(!m_bIsConnected){
        qDebug()<<"Tcp 发起重连";
        m_pTcpSocket->abort();
        m_pTcpSocket->connectToHost(*m_pServerIp,m_nPort);
    }
}

void CTcpClientConnection::init()
{
    m_pTcpSocket = new QTcpSocket(this);
    QObject::connect(m_pTcpSocket, &QTcpSocket::connected,[=]{ //连接成功处理
        m_bIsConnected = true;
        emit sigConnectStateChanged(m_strIp,m_nPort,m_bIsConnected);

        m_pTimerReconnection->stop(); //关闭重连

        qDebug()<<"连接成功"<<m_pServerIp->toString();
    });

    QObject::connect(m_pTcpSocket,&QTcpSocket::disconnected,[=]{ //断开连接处理  与连接成功操作步骤一致
        m_bIsConnected = false;
        emit sigConnectStateChanged(m_strIp,m_nPort,m_bIsConnected);

        m_pTimerReconnection->start(); //开启重连
        qDebug()<<"断开连接"<<m_pServerIp->toString();
    });

    QObject::connect(m_pTcpSocket,&QTcpSocket::readyRead,[=]{  //接收到数据
        /*接收到一行数据*/
//        while(m_pTcpSocket->canReadLine()){
//            QByteArray arrLine = m_pTcpSocket->readLine(m_nMaxReadSize);
//            QString strMsg(arrLine);
//            emit sigRecvLine(strMsg.toUtf8());
//        }

        /*接收到数据*/
        QByteArray arrByte = m_pTcpSocket->readAll();
        qDebug()<<"Tcp接收到数据"<<arrByte;
        emit sigRecv(m_strIp,m_nPort,QString(arrByte));
    });
    m_pTcpSocket->abort(); //丢弃缓冲区数据

    m_pServerIp = new QHostAddress();
    m_pServerIp->setAddress(m_strIp);

    /*重连检测*/
    m_pTimerReconnection = new QTimer(this);
    m_pTimerReconnection->setInterval(m_nReConnectionSpan);
    QObject::connect(m_pTimerReconnection,SIGNAL(timeout()),this,SLOT(slotReConnection()));
//    QObject::connect(m_pTimerReconnection,&QTimer::timeout,[=]{
//        qDebug()<<"Tcp 发起重连";
//        if(!m_bIsConnected){
//            m_pTcpSocket->abort();
//            m_pTcpSocket->connectToHost(*m_pServerIp,m_nPort);
//        }
//    });


//    initQueue(); //初始化命令队列机制
}

//void CTcpClientConnection::initQueue()
//{
//    //m_bIsOpenQueue = true;

//    m_pTimerQueue = new QTimer(this);
//    m_pTimerQueue->setInterval(m_nMsgSpan);

//    QObject::connect(m_pTimerQueue,&QTimer::timeout,[=]{
//        if(!m_queueMsg.isEmpty()){
//            m_pTcpSocket->write(m_queueMsg.dequeue().toUtf8());   //按条发送队列信息
//        }else{
//            m_pTimerQueue->stop(); //队列内容发送完毕
//        }
//    });
//}
