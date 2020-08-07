#include "TComBoxCardItem.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QGridLayout>
#include <QStyleOption>
#include <QApplication>

TComBoxCardItem::TComBoxCardItem(QString strText, QStringList strList, QWidget *parent)
    : QWidget(parent),m_strText(strText),m_strListItems(strList)
{
    m_strImgPath = QApplication::applicationDirPath() + "/";
    init();
}

void TComBoxCardItem::init()
{
    this->resize(285,35);
//    this->setMaximumHeight(35);

    m_pLabel = new QLabel(this);
    m_pComBox = new QComboBox(this);
    m_pComBox->setFixedSize(160,30);
    this->setStyleSheet("QComboBox{background:#ffffff;border-radius:5px;padding:1px;border: 4px solid #ffffff;color:#000000;}"
                             "QComboBox::drop-down{background-color:transparent;width:20px;top:4px;height:15px;right:4px;}"
                             "QComboBox::down-arrow {image:url(" + m_strImgPath + "image/form/combox-drop.png);}"
                             );


    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabel);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pComBox);
    hLayout->setContentsMargins(5,2,5,2);
    this->setLayout(hLayout);

    m_pLabel->setText(m_strText);
    m_pComBox->addItems(m_strListItems);
}

void TComBoxCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
