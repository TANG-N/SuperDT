#include "TComBoxCardItem.h"
#include <QHBoxLayout>

TComBoxCardItem::TComBoxCardItem(QString strText, QVector<QString> vecItems, QWidget *parent)
    : QWidget(parent)
{
    m_strText = strText;
    m_vecItems = vecItems;

    init();
}

void TComBoxCardItem::addItems(QVector<QString> vecItem)
{
    foreach(QString strItem,vecItem){
        m_pComBox->addItem(strItem);
    }
}

void TComBoxCardItem::init()
{
    m_pLabel = new QLabel(this);
    m_pComBox = new TComBox(this);
    m_pComBox->setFixedWidth(120);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabel);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pComBox);

    this->setLayout(hLayout);
    refreshStyle();
}

void TComBoxCardItem::refreshStyle()
{
    m_pLabel->setText(m_strText);
    addItems(m_vecItems);
}
