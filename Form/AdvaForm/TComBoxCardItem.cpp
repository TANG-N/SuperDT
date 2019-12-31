#include "TComBoxCardItem.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QGridLayout>
#include <QStyleOption>

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
    m_pComBox->setFixedWidth(160);
    connect(m_pComBox,SIGNAL(currentTextChanged(QString)),this,SIGNAL(sigSettingChanged()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabel);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pComBox);
    hLayout->setContentsMargins(5,2,5,2);
    this->setLayout(hLayout);
    refreshStyle();
}

void TComBoxCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TComBoxCardItem::refreshStyle()
{
    m_pLabel->setText(m_strText);
    addItems(m_vecItems);
}
