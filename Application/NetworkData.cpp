#include "NetworkData.h"

NetworkData::NetworkData(QObject *parent) : QObject(parent)
{

}
void NetworkData::addLoopText(QString strText,int ns)
{
    QPair<QString,int> par;
    par.first = strText;
    par.second = ns;

    m_vecLoopText.append(par);
}
