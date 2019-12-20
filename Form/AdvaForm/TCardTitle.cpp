#include "TCardTitle.h"
#include <QHBoxLayout>

TCardTitle::TCardTitle(QString strIconUrl, QString strText, QWidget *parent)
    : QWidget(parent)
{
    m_strIconUrl = strIconUrl;
    m_strText = strText;
    m_strTextColor = "#ffffff";
    init();
}

void TCardTitle::init()
{
    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setFixedSize(24,24);

    m_pLabelText = new QLabel(this);
    m_pLabelText->setFixedHeight(24);
    m_pLabelText->adjustSize();
    m_pLabelText->setWordWrap(true); //自动换行
    refreshStyle();

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabelIcon);
    hLayout->addStretch();
    hLayout->addWidget(m_pLabelText);

    this->setLayout(hLayout);
}

void TCardTitle::refreshStyle()
{
    QString strStyle = "border-image:url(:" + m_strIconUrl + ");";
    m_pLabelIcon->setStyleSheet(strStyle);

    m_pLabelText->setText(m_strText);
    strStyle = "color:" + m_strTextColor + ";";
    m_pLabelText->setStyleSheet(strStyle);
}
