#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QObject>
#include <QVector>
#include <QPair>
#include <QMap>

class NetworkData : public QObject
{
    Q_OBJECT
public:
    explicit NetworkData(QObject *parent = 0);

    QString getId(){return m_strId;}
    void addLoopText(QString strText,int ns);
    void removeLoopText(int nIndex){m_vecLoopText.removeAt(nIndex);}
public:
    /*会话Id*/
    QString m_strId;

    /*协议参数*/
    QString m_strProcoalType;
    QString m_strIp;
    int m_strPort;
    int m_nNetState;

    /*接收设置*/
    bool m_bSaveAble;
    QString m_strLogFileName;
    QString m_strFilePath;
    bool m_bRecvAble;
    bool m_bRecvHexAble;

    /*发送设置*/
    bool m_bSendAble;
    bool m_bSendHexAble;

    /*高级设置*/
    bool m_bLoopSendAble;
    QVector<QPair<QString,int>> m_vecLoopText; //循环文本条目 <文本，n秒后发送> 不自动排序

    /*触发器*/
    bool m_bTriggerAble; //触发器开关
    QMap<QString,QString> m_mapTrg; //触发列表 <接收文本，发送文本>

};


#endif // NETWORKDATA_H
