#ifndef NETWORKAPP_H
#define NETWORKAPP_H

#include <QWidget>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>

#include "TCardItem.h"
#include "TCard.h"
#include "TCardTitle.h"
#include <QDebug>
#include "TComBoxCardItem.h"
#include "TComBox.h"
#include "TLockButtonCardItem.h"
#include "TUserCardItem.h"
#include "TLoopTextCardItem.h"
#include "TTriggerCardItem.h"
#include <QList>

class NetworkApp : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkApp(QWidget *parent = 0);

    void initUI();
private:
    QString m_strAppPath;
    QScrollArea *m_pScrollArea;
    QTextEdit *m_pTextEdit;

    TCard *m_pCardUser;
    TCard *m_pCardProtocal;
    TCard *m_pCardRecv;
    TCard *m_pCardSend;
    TCard *m_pCardSendText;
    TCard *m_pCardTrig;
    TCard *m_pCardAdvaSend;

    QList<TCard *> m_listCard;
private slots:
    void slotAddTrig();
    void slotAddLoop();

    void slotChangeForProtocal();
    void slotChangeForRecv();
    void slotChangeForSend();
    void slotChangeForSendText();
    void slotChangeForTrig();
    void slotChangeForAdvaSend();
};

#endif // NETWORKAPP_H
