#include "TCardTitle.h"
#include <QHBoxLayout>
#include "CFaIcon.h"

TCardTitle::TCardTitle(QString strIcon, QString strText, QString strHelp,QWidget *parent)
    : QWidget(parent),m_strIcon(strIcon),m_strText(strText),m_strHelp(strHelp)
{
    init();
}

void TCardTitle::enterEvent(QEvent *event)
{
    m_pLabelHelp->setStyleSheet("QLabel{background:transparent;font:22px FontAwesome;color:#ffffff;}"
                              "QToolTip{background:#bbbbbb;color:#ffffff;border-radius:2px;}");
}

void TCardTitle::leaveEvent(QEvent *event)
{
    m_pLabelHelp->setStyleSheet("QLabel{background:transparent;font:22px FontAwesome;color:transparent;}"
                              "QToolTip{background:#bbbbbb;color:#ffffff;border-radius:2px;}");
}

void TCardTitle::init()
{
    this->resize(285,35);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setMinimumSize(24,24);
    m_pLabelIcon->setMaximumSize(36,36);
    m_pLabelIcon->setText(m_strIcon);
    m_pLabelIcon->setStyleSheet("QLabel{background:transparent;font:22px FontAwesome;color:#000000;}");

    m_pLabelText = new QLabel(this);
    m_pLabelText->setMinimumHeight(24);
    m_pLabelText->setMaximumHeight(36);
    m_pLabelText->setWordWrap(true); //自动换行
    m_pLabelText->setText(m_strText);
    m_pLabelText->setStyleSheet("QLabel{background-color:transparent;color:#000000;}");

    m_pLabelHelp = new QLabel(this);
    m_pLabelHelp->setFixedSize(24,24);
    m_pLabelHelp->setText(CFaIcon::iconsQString(CFaIcon::Fa_question_circle));
    m_pLabelHelp->setToolTip(m_strHelp);
    m_pLabelHelp->setStyleSheet("QLabel{background:transparent;font:22px FontAwesome;color:transparent;}"
                              "QToolTip{background:#bbbbbb;color:#ffffff;border-radius:5px;padding:5px;}");

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setContentsMargins(5,3,5,3);
    hLayout->setSpacing(3);
    hLayout->addWidget(m_pLabelIcon);
    hLayout->addSpacing(5);
    hLayout->addWidget(m_pLabelText);
    hLayout->addStretch();
    hLayout->addWidget(m_pLabelHelp);
}

