#include "CConnectTools.h"

CConnectTools::CConnectTools(QObject *parent)
    : QObject(parent)
{

}

CConnectTools *CConnectTools::getInstance()
{
    static CConnectTools* pInstance = nullptr;
    if(nullptr == pInstance){
        pInstance = new CConnectTools();
    }
    return pInstance;
}

QStringList CConnectTools::getLocalIPv4()
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());

    QList<QHostAddress> listAddr = hostInfo.addresses();

    QStringList listIPv4;
    foreach(QHostAddress addr,listAddr){
        if(QAbstractSocket::IPv4Protocol == addr.protocol()){
            listIPv4.append(addr.toString());
        }
    }

    return listIPv4;
}
