#ifndef CCONNECTTOOLS_H
#define CCONNECTTOOLS_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>

class CConnectTools:public QObject
{
    Q_OBJECT
private:
    explicit CConnectTools(QObject *parent = 0);
public:
    static CConnectTools* getInstance();

    static QStringList getLocalIPv4();

};

#endif // CCONNECTTOOLS_H
