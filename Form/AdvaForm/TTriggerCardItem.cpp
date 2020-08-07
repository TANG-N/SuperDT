#include "TTriggerCardItem.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QApplication>

TTriggerCardItem::TTriggerCardItem(QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initUI();
}

void TTriggerCardItem::initUI()
{
    this->resize(285,35);
//    this->setMaximumHeight(35);

    m_pLineEditR = new QLineEdit(this);
    m_pLineEditR->setMinimumWidth(90);
    m_pLineEditR->setFixedHeight(30);
    m_pLineEditR->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setStyleSheet("border-image:url(" + m_strAppPath + "image/setting/trig.png);");
    m_pLabelIcon->setFixedSize(28,28);

    m_pLineEditS = new QLineEdit(this);
    m_pLineEditS->setMinimumWidth(90);
    m_pLineEditS->setFixedHeight(30);
    m_pLineEditS->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");


    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setStyleSheet("border-image:url(" +m_strAppPath + "image/setting/del.png);");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLineEditR);
    hLayout->addWidget(m_pLabelIcon);
    hLayout->addWidget(m_pLineEditS);
    hLayout->addWidget(m_pBtnDel);
    hLayout->setContentsMargins(5,2,5,2);
    hLayout->setSpacing(2);

    this->setLayout(hLayout);
}

void TTriggerCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
