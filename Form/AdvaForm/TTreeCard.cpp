#include "TTreeCard.h"
#include <QDebug>
#include <QLabel>
#include <QHeaderView>

TTreeCard::TTreeCard(QWidget *parent)
    : QTreeWidget(parent)
{
    init();
}

void TTreeCard::addWidget(QWidget *pWidget)
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem;

    this->addTopLevelItem(treeItem);
    this->setItemWidget(treeItem,0,pWidget);


    QTreeWidgetItem *ter = new QTreeWidgetItem;
    ter->setText(0,"aafdf");
    treeItem->addChild(ter);

    QTreeWidgetItem *te = new QTreeWidgetItem;
    te->setText(0,"cdcccc");
    treeItem->addChild(te);

    qDebug()<<"现有item:"<<this->topLevelItemCount();

    this->adjustSize();
}

void TTreeCard::init()
{
    this->header()->setVisible(false);

    this->setStyleSheet("QWidget{background-color:#ff0000;border-radius:10px;}"
                        "QTreeWidget{padding:10px;}"
                        "QTreeWidget::item{border-top:1px solid #ffffff; border-bottom: 1px solid #ffffff;}"
                        //"QTreeWidget::branch{background-color:#00ff00;border-top:1px solid #0000ff;border-bottom: 1px solid #ffffff;width:30px;}"
                        "QTreeWidget::branch:has-children{background-color:#00ff00;border-color:#0000f0; width:0;height:0; border-width:3px 3px 3px 0;position:relative;border-style:solid;}"
                        "QTreeWidget::branch{background-color:#00ff00;width:0px;}");

}
