 #include "CTcpServerConnection.h"

CTcpServerConnection::CTcpServerConnection(QObject *parent)
    : AbsConnection(parent)
{
    init();
}

void CTcpServerConnection::disConnect()
{
    m_pTcpServer->close();
}

void CTcpServerConnection::connect(QString strIp, int nPort)
{ 
    m_nPort = nPort;

    if(m_pTcpServer != nullptr){
        if(strIp.isEmpty()){
            m_pTcpServer->listen(QHostAddress::Any,m_nPort); //监听所有Ip
        }else{
            m_pTcpServer->listen(QHostAddress(strIp),m_nPort);
        }
    }

}

void CTcpServerConnection::send(QString strIp, int nPort, QString strMsg)
{
    QString strKey = toIpPort(strIp,nPort);

    if(m_mapConnections.contains(strKey)){
        QTcpSocket *pTcpSocket = m_mapConnections.value(strKey);
        pTcpSocket->write(strMsg.toUtf8());
    }
}

void CTcpServerConnection::sendAll(QString strMsg)
{
    QMapIterator<QString,QTcpSocket *> mapIterator(m_mapConnections);
    while(mapIterator.hasNext()){
        mapIterator.next();

        QTcpSocket *pTcpSocket = mapIterator.value();
        pTcpSocket->write(strMsg.toUtf8());

    }
}


void CTcpServerConnection::init()
{
    m_pTcpServer = new QTcpServer(this);
    QObject::connect(m_pTcpServer,&QTcpServer::newConnection,[=]{
        QTcpSocket *pTcpSocket = m_pTcpServer->nextPendingConnection();
        QString strIp = pTcpSocket->peerAddress().toString();
        int nPort = pTcpSocket->peerPort();
        QString strKey = toIpPort(strIp,nPort);
        m_mapConnections.insert(strKey,pTcpSocket); //将连接加入map
        /*通知新的连接*/
        emit sigConnectStateChanged(strIp,nPort,true);

        /*连接断开*/
        QObject::connect(pTcpSocket,&QTcpSocket::disconnected,[=]{
            if(m_mapConnections.contains(strKey)){
                QTcpSocket *pTmp = m_mapConnections.value(strKey);
                pTmp->deleteLater();
                pTmp = nullptr;
                m_mapConnections.remove(strKey);
            }

            emit sigConnectStateChanged(strIp,nPort,false);
        });
        QObject::connect(pTcpSocket,&QTcpSocket::stateChanged,[=]{

        });
        /*接收到数据*/
        QObject::connect(pTcpSocket,&QTcpSocket::readyRead,[=]{
            if(pTcpSocket != nullptr){
                /*基于行协议*/

                while(pTcpSocket->canReadLine()){
                    QByteArray arrLine = pTcpSocket->readLine(m_nMaxReadSize);
                    emit sigRecvLine(strIp,nPort,QString(arrLine).toUtf8());
                }

                /*有数据就读*/
                QByteArray arr = pTcpSocket->readAll();

                QString strMsg(arr);

                emit sigRecv(strIp,nPort,strMsg.toUtf8());

            }
        });
    });

}
