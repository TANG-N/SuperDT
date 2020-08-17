#include "TLoopTextCardItem.h"
#include <QStyleOption>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include "CFaIcon.h"
#include <QTimer>

TLoopTextCardItem::TLoopTextCardItem(QWidget *parent) : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initUI();
}

void TLoopTextCardItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_bOn = true;
    QTimer::singleShot(500,[=]{
        if(m_bOn){
            m_pBtnDel->show();
        }
    });

}

void TLoopTextCardItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_bOn = false;
    m_pBtnDel->hide();
}

void TLoopTextCardItem::initUI()
{
    this->resize(285,35);
//    this->setMaximumHeight(35);

    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setMinimumWidth(150);
    m_pLineEdit->setFixedHeight(30);
    m_pLineEdit->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");

    QLineEdit* pTmpLineEdit = new QLineEdit();
    pTmpLineEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setText(CFaIcon::iconsQString(CFaIcon::Fa_times_circle_o));
    m_pBtnDel->setStyleSheet("QPushButton{color:#ff3333;font:22px FontAwesome;}");
    m_pBtnDel->hide();

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLineEdit);
//    hLayout->addWidget(m_pComBox);
    hLayout->addWidget(m_pBtnDel);
    hLayout->setContentsMargins(5,2,5,2);
    hLayout->setSpacing(2);

    this->setLayout(hLayout);
}

void TLoopTextCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
