#include "TUserCardItem.h"

TUserCardItem::TUserCardItem(QWidget *parent)
    : QWidget(parent)
{

}

void TUserCardItem::initUI()
{
    m_pLabelUserPicBg = new QLabel(this);
    m_pLabelUserPicBg->setFixedSize(72,72);

    m_pLabelUserPic = new QLabel(m_pLabelUserPicBg);
    m_pLabelUserPic->setFixedSize(68,68);

    m_pLabelUserName = new QLabel(this);
}

void TUserCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
