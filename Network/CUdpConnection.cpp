#include "CUdpConnection.h"
#include "CConnectTools.h"

CUdpConnection::CUdpConnection(QObject *parent)
    : AbsConnection(parent)
{
    init();
}

void CUdpConnection::connect(QString strIp,int nPort)
{
    if(!m_pUdpSocket->isOpen()){
        m_pUdpSocket->open(QIODevice::ReadWrite);
    }
    m_pUdpSocket->abort();//重置Socket 并丢弃数据

    m_strLIp = strIp;
    m_nLPort = nPort;

    if(nullptr != m_pUdpSocket){
        if(m_strLIp.isEmpty())
            m_pUdpSocket->bind(QHostAddress::Any,m_nLPort);
        else
            m_pUdpSocket->bind(QHostAddress(m_strLIp),m_nLPort);
    }

    emit sigConnectStateChanged(m_strLIp,m_nLPort,true);
}

void CUdpConnection::disConnect()
{
    m_pUdpSocket->abort();
    m_pUdpSocket->close(); //关闭IO  并会关闭连接
    emit sigConnectStateChanged(m_strLIp,m_nLPort,false);
}

void CUdpConnection::send(QString strMsg)
{
    QByteArray arrMsg = strMsg.toUtf8();
    m_pUdpSocket->writeDatagram(arrMsg,m_hostRemote,m_nRPort);
}


void CUdpConnection::send(QString strIp, int nPort, QString strMsg)
{

    QHostAddress hostRemote;
    bool bIsIp = hostRemote.setAddress(strIp);//可判断IP是否合法
    if(!bIsIp){
        qDebug()<<"CUdpConnection::send   IP非法："<<strIp;
        return;
    }

    QByteArray arrMsg = strMsg.toUtf8();
    m_pUdpSocket->writeDatagram(arrMsg,hostRemote,nPort);
}

void CUdpConnection::setRemoteAddress(QString strIp, int nPort)
{
    m_hostRemote = QHostAddress(strIp);
    m_nRPort = nPort;
}

void CUdpConnection::init()
{
    m_pUdpSocket = new QUdpSocket(this);

#if 1
    QStringList listIpv4 = CConnectTools::getLocalIPv4();

    if(!listIpv4.isEmpty()){
        m_strLIp = listIpv4.first();
    }


//    QObject::connect(m_pUdpSocket,&QUdpSocket::stateChanged,[=](QAbstractSocket state){
//        Q_UNUSED(state)
//    });
    QObject::connect(m_pUdpSocket,&QUdpSocket::readyRead,[=]{

        /*接收数据*/
        int nSize = m_pUdpSocket->pendingDatagramSize(); //数据报大小
        if(nSize > 0){
            QByteArray arrDatagrams;
            arrDatagrams.resize(nSize);

            QHostAddress hostPeerAddr;
            quint16 nPeerPort = 0;

            m_pUdpSocket->readDatagram(arrDatagrams.data(),arrDatagrams.size(),&hostPeerAddr,&nPeerPort);


            qDebug()<<"Udp 接收到来自："<<QString(hostPeerAddr.toString() + ":" + QString::number(nPeerPort))<<"的报文内容是:"<<QString(arrDatagrams).toUtf8();
            emit sigRecv(hostPeerAddr.toString(),nPeerPort,QString(arrDatagrams).toUtf8());
        }
//        /*接收一行 */
//        while(m_pUdpSocket->canReadLine()){

//            QByteArray arrLine = m_pUdpSocket->readLine();

//            emit sigRecvLine(m_hostRemote.toString(),m_nRPort,QString(arrLine).toUtf8());

//        }

    });

#endif
}
