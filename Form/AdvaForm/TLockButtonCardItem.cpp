#include "TLockButtonCardItem.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>

TLockButtonCardItem::TLockButtonCardItem(QString strText,QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    m_strText = strText;
    m_strBtnImgN = m_strAppPath + "image/setting/btn_n.png";
    m_strBtnImgC = m_strAppPath + "image/setting/btn_c.png";
    initUI();
}
//Qwidget 自身没有实现paintEvent  对setStyleSheet()无效 实现paintEvent即可
void TLockButtonCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TLockButtonCardItem::slotBtnClicked()
{
    emit sigBtnClicked(m_pLockBtn->isChecked());
}

void TLockButtonCardItem::initUI()
{
    m_pLabel = new QLabel(this);
    m_pLabel->setText(m_strText);

    m_pLockBtn = new TLockButton("BtnItem",m_strBtnImgN,m_strBtnImgC,this);
    m_pLockBtn->setFixedSize(32,20);
    connect(m_pLockBtn,SIGNAL(clicked(bool)),this,SLOT(slotBtnClicked()));
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabel);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pLockBtn);
    hLayout->setContentsMargins(5,2,5,2);
    this->setLayout(hLayout);
}
