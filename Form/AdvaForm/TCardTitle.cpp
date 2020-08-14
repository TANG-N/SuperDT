#include "TCardTitle.h"
#include <QHBoxLayout>

TCardTitle::TCardTitle(QString strIcon, QString strText, QWidget *parent)
    : QWidget(parent),m_strIcon(strIcon),m_strText(strText)
{
    init();
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

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(3);
    hLayout->addWidget(m_pLabelIcon);
    hLayout->addSpacing(5);
    hLayout->addWidget(m_pLabelText);
    hLayout->addStretch();

    this->setLayout(hLayout);
}

