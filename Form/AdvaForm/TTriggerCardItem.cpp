#include "TTriggerCardItem.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QApplication>
#include "CFaIcon.h"
#include <QTimer>
TTriggerCardItem::TTriggerCardItem(QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initUI();
}

void TTriggerCardItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_bOn = true;
    QTimer::singleShot(500,[=]{
        if(m_bOn){
            m_pBtnDel->show();
        }
    });
}

void TTriggerCardItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_bOn = false;
    m_pBtnDel->hide();
}

void TTriggerCardItem::initUI()
{
    this->resize(285,35);

    m_pLineEditR = new QLineEdit(this);
    m_pLineEditR->setMinimumWidth(90);
    m_pLineEditR->setFixedHeight(30);
    m_pLineEditR->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setText(CFaIcon::iconsQString(CFaIcon::Fa_filter));
    m_pLabelIcon->setStyleSheet("QLabel{color:#33ccff;font:22px FontAwesome;}");
    m_pLabelIcon->setFixedSize(28,28);
    m_pLabelIcon->setAlignment(Qt::AlignCenter);

    m_pLineEditS = new QLineEdit(this);
    m_pLineEditS->setMinimumWidth(90);
    m_pLineEditS->setFixedHeight(30);
    m_pLineEditS->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");


    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setText(CFaIcon::iconsQString(CFaIcon::Fa_times_circle_o));
    m_pBtnDel->setStyleSheet("QPushButton{color:#ff3333;font:22px FontAwesome;}");
    m_pBtnDel->hide();

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
