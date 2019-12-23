#include "TLoopTextCardItem.h"
#include <QStyleOption>
#include <QHBoxLayout>

TLoopTextCardItem::TLoopTextCardItem(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void TLoopTextCardItem::initUI()
{
    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setMinimumWidth(150);
    m_pLineEdit->setFixedHeight(30);
    m_pLineEdit->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");
    m_pComBox = new TComBox(this);
    m_pComBox->setMinimumWidth(65);
    m_pComBox->addItem("1s");
    m_pComBox->addItem("2s");

    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setStyleSheet("border-image:url(:image/icon/setting/del.png);");
    connect(m_pBtnDel,SIGNAL(clicked()),this,SLOT(slotDel()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLineEdit);
    hLayout->addWidget(m_pComBox);
    hLayout->addWidget(m_pBtnDel);
    hLayout->setContentsMargins(5,2,5,2);
    hLayout->setSpacing(2);

    this->setLayout(hLayout);
}

void TLoopTextCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TLoopTextCardItem::slotDel()
{
    emit sigDel(this);
}
