#include <QVBoxLayout>

#include "NetworkApp.h"
#include "TCardItem.h"
#include "TCard.h"
#include "TCardTitle.h"
#include <QDebug>
#include "TComBoxCardItem.h"
#include "TComBox.h"

NetworkApp::NetworkApp(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void NetworkApp::initUI()
{
    TCardTitle *cardTitle = new TCardTitle(":/image/icon/setting/menu_n.png","协议设置",this);

    TCard *card1 = new TCard(this);
    card1->addItem();
    card1->addItem();
    card1->addItem();
//    card1->setFixedSize(265,120);
    qDebug()<<"Card 1size"<<card1->size();


    TCardItem *cardItem1 = new TCardItem("接收显示",ENM_TPUSHBUTTON,card1->at(0));
    TCardItem *cardItem2 = new TCardItem("十六进制显示",ENM_TPUSHBUTTON,card1->at(1));
//    TCardItem *cardItem3 = new TCardItem("保存到文件",ENM_TCOMBOX,card1->at(2));
//    cardItem3->addComBoxItem("192.168.1.1");
//    cardItem3->addComBoxItem("192.168.1.2");
//    cardItem3->addComBoxItem("192.168.1.3");

    QVector<QString> vecIpItem;
    vecIpItem<<"192.168.1.1"<<"192.168.1.2"<<"192.168.1.3";
    TComBoxCardItem *cardIpItem = new TComBoxCardItem("保存到文件",vecIpItem,card1->at(2));
    cardIpItem->resize(card1->at(2)->size());

    card1->show();
    qDebug()<<"Card 2size"<<card1->size();

    TComBox *cmbox = new TComBox(this);
    cmbox->resize(130,30);
    cmbox->move(50,300);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(cardTitle);
    layout->addWidget(card1);
    layout->addStretch(1);
    layout->setContentsMargins(2,0,2,0);

    qDebug()<<"Card 3size"<<card1->size();
    this->setLayout(layout);
}
