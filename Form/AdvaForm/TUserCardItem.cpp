#include "TUserCardItem.h"
#include <QStyleOption>
#include <QPainter>

TUserCardItem::TUserCardItem(QWidget *parent) : QWidget(parent)
{
    m_strImgPath = ":image/icon/setting/user1.jpg";
    m_strIconPath = ":image/icon/setting/user_n.png";
    m_strUserName = "TANG";
    m_nDebugCount = 23467;
    initUI();
}

void TUserCardItem::initUI()
{
    m_pLabelUserImg = new QLabel(this);
    m_pLabelUserImg->setFixedSize(80,80);

    m_pLabelUserIcon = new QLabel(this);
    m_pLabelUserIcon->setFixedSize(32,32);

    m_pLabelUserName = new QLabel(this);
    m_pLabelUserName->setFixedHeight(32);

    m_PLabelUserMsg = new QLabel(this);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(m_pLabelUserImg,0,0,3,3);
    gLayout->addWidget(m_pLabelUserIcon,1,4,1,1);
    gLayout->addWidget(m_pLabelUserName,1,6,1,2);
    gLayout->addWidget(m_PLabelUserMsg,2,4,1,5);

    this->setLayout(gLayout);
    refreshStyle();
}

void TUserCardItem::refreshStyle()
{
    m_pLabelUserImg->setStyleSheet("border-image:url("+ m_strImgPath + ");");
    m_pLabelUserIcon->setPixmap(QPixmap(m_strIconPath));
    m_pLabelUserName->setText(m_strUserName);
    m_PLabelUserMsg->setText("第" + QString::number(m_nDebugCount) + "次调试");
}

void TUserCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
