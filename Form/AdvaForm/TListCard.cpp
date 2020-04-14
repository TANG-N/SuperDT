#include "TListCard.h"
#include <QHeaderView>
#include <QDebug>
#include <QScrollBar>

TListCard::TListCard(QWidget *parent)
    : QListWidget(parent)
{
    init();
}

QListWidgetItem *TListCard::addWidget(QWidget *pWidget)
{
    QListWidgetItem *pItem = new QListWidgetItem;
    pItem->setSizeHint(pWidget->size());
    this->addItem(pItem);
    this->setItemWidget(pItem,pWidget);

    if(pWidget->width() > m_nWidth)
        m_nWidth = pWidget->width();

    m_nHeight += pWidget->size().height();
    this->setFixedSize(m_nWidth,m_nHeight + 20); //加的20  是上下10 margin

    qDebug()<<"Card size:"<<this->size();
    return pItem;
}

QListWidgetItem *TListCard::insertWidget(int row, QWidget *pWidget)
{
    QListWidgetItem *pItem = new QListWidgetItem;
    pItem->setSizeHint(pWidget->size());
    this->insertItem(row,pItem);
    this->setItemWidget(pItem,pWidget);

    if(pWidget->width() > m_nWidth)
        m_nWidth = pWidget->width();

    m_nHeight += pWidget->size().height();
    this->setFixedSize(m_nWidth,m_nHeight + 20); //加的20  是上下10 margin

    return pItem;
}

void TListCard::removeItem(QListWidgetItem *pItem)
{
    if(nullptr == pItem)
        return ;

    this->removeItemWidget(pItem);
    delete  pItem;
//    QListWidgetItem *p = this->takeItem(this->row(pItem));


}

void TListCard::init()
{
    this->setStyleSheet("QWidget{background-color:#bbbbbe;border-radius:10px;}"
                        "TListCard{padding-top:10px;padding-bottom:10px;}"
                        "QListWidget::item{border-bottom:1px solid #ffffff;}"
//                        "QListWidget::item:hover{background:skyblue; }"
//                        "QListWidget::item:selected{background:lightgray; color:red; }"
//                        "QListWidget::item:selected:!active{border-width:0px; background:lightgreen; }"
                        );

    /*垂直滚动条*/
    this->verticalScrollBar()->setStyleSheet(
                         "QScrollBar {width:8px;background-color:transparent;}"
                         "QScrollBar::handle {background-color:rgb(204,204,204);border-radius:4px;}" //滑块样式
                         "QScrollBar::add-line {height: 0px;}"
                         "QScrollBar::sub-line {height: 0px;}"
                         "QScrollBar::add-page {background: none;}"
                         "QScrollBar::sub-page {background: none;}"
                          );
    /*水平滚动条*/
    this->horizontalScrollBar()->setStyleSheet(
                          "QScrollBar {height:8px;background-color:transparent;}"
                          "QScrollBar::handle {background-color:rgb(204,204,204);border-radius:4px;}" //滑块样式
                          "QScrollBar::add-line {height: 0px;}"
                          "QScrollBar::sub-line {height: 0px;}"
                          "QScrollBar::add-page {background: none;}"
                          "QScrollBar::sub-page {background: none;}"
                           );


}
