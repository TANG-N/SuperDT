#ifndef CSERIALCONNECTION_H
#define CSERIALCONNECTION_H

#include <QObject>
#include <QWidget>

class CSerialConnection : public QObject
{
    Q_OBJECT
public:
    explicit CSerialConnection(QObject *parent = nullptr);

signals:

};

#endif // CSERIALCONNECTION_H
