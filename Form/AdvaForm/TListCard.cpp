#include "TListCard.h"
#include <QHeaderView>
#include <QDebug>
#include <QScrollBar>
#include <QGraphicsDropShadowEffect>

TListCard::TListCard(QWidget *parent)
    : QListWidget(parent)
{
    init();
}

QListWidgetItem *TListCard::addWidget(QWidget *pWidget)
{
    QListWidgetItem *pItem = new QListWidgetItem;
    pItem->setSizeHint(pWidget->size()); //这个就能设置行高
    this->addItem(pItem);
    this->setItemWidget(pItem,pWidget);

//    qDebug()<<pWidget->objectName()<<":"<<pWidget->size();

    if(pWidget->width() > m_nWidth)
        m_nWidth = pWidget->width();

    m_nHeight += pWidget->size().height();
    this->setFixedSize(m_nWidth,m_nHeight + 20); //加的20  是上下10 margin
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
    this->setStyleSheet("QWidget{background-color:#88bebebe;border-radius:5px;}" //半透白
                        "TListCard{padding-top:10px;padding-bottom:10px;}"
                        "QListWidget::item{border-bottom:1px solid #ffffff;}"
                        "QListWidget::item:hover{background:#88bebebe; }"
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


    /*阴影效果*/
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(8);        // 阴影圆角的大小
//    effect->setColor(Qt::gray);      //阴影的颜色
//    effect->setOffset(5,5);          //阴影的偏移量
//    this->setGraphicsEffect(effect); //
}
