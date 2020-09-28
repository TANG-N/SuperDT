#include "TLineEditCardItem.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QStyleOption>
#include <QApplication>
#include "CFaIcon.h"
#include <QTimer>

TLineEditCardItem::TLineEditCardItem(QString strBtnText,QWidget *parent)
    : QWidget(parent),m_strBtnText(strBtnText)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    init();
}

void TLineEditCardItem::init()
{
    this->resize(285,35);

    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setFixedHeight(30);
    m_pLineEdit->setStyleSheet("QLineEdit{background:#ffffff;border-radius:5px;padding:1px;"
                               "border: 4px solid #ffffff;color:#000000;}");

    m_pBtn = new QPushButton(this);
    m_pBtn->setText(m_strBtnText);
    m_pBtn->setFixedSize(40,30);
    m_pBtn->setStyleSheet("QPushButton{background:#ffffff;border-radius:5px;padding:1px;"
                          "border:4px solid #ffffff;color:#000000;}");
    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setText(CFaIcon::iconsQString(CFaIcon::Fa_times_circle_o));
    m_pBtnDel->setStyleSheet("QPushButton{color:#ff3333;font:22px FontAwesome;}");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLineEdit);
    hLayout->addWidget(m_pBtn);
    hLayout->addWidget(m_pBtnDel);
    hLayout->setContentsMargins(5,2,5,2);
    this->setLayout(hLayout);
}

void TLineEditCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
