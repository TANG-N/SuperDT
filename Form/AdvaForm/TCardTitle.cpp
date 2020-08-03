#include "TCardTitle.h"
#include <QHBoxLayout>

TCardTitle::TCardTitle(QString strIconUrl, QString strText, QWidget *parent)
    : QWidget(parent),m_strIconUrl(strIconUrl),m_strText(strText)
{
    init();
}

void TCardTitle::init()
{
//    setStyleSheet("#this,QWidget,QLabel{border:1px solid red;}");
    this->setFixedHeight(35);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setMinimumSize(24,24);
    m_pLabelIcon->setMaximumSize(36,36);
    m_pLabelIcon->setStyleSheet("QLabel{border-image:url(" + m_strIconUrl + ");}");

    m_pLabelText = new QLabel(this);
    m_pLabelText->setMinimumHeight(24);
    m_pLabelText->setMaximumHeight(36);
    m_pLabelText->setWordWrap(true); //自动换行
    m_pLabelText->setText(m_strText);
    m_pLabelText->setStyleSheet("QLabel{background-color:transparent;color:#ffffff;}");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setSpacing(3);
    hLayout->addWidget(m_pLabelIcon);
    hLayout->addWidget(m_pLabelText);
    hLayout->addStretch();

    this->setLayout(hLayout);
}

