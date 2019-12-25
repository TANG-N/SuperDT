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

class NetworkApp : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkApp(QWidget *parent = 0);

    void initUI();
private:
    QScrollArea *m_pScrollArea;
    QTextEdit *m_pTextEdit;


    TCard *m_pCardTrig;
    TCard *m_pCardAdvaSend;
private slots:
    void slotAddTrig();
    void slotAddLoop();
};

#endif // NETWORKAPP_H
