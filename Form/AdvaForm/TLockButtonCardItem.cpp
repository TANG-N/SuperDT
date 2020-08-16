#include "TLockButtonCardItem.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include "CFaIcon.h"

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

void TLockButtonCardItem::initUI()
{
    this->resize(285,35);

//    this->setObjectName("bg");
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setStyleSheet("#bg{background:transparents;}");

    m_pLabel = new QLabel(this);
    m_pLabel->setText(m_strText);
    m_pLabel->setStyleSheet("QLabel{background:transparent;}");

    m_pBtn = new QPushButton(this);
    m_pBtn->setCheckable(true);

//    m_pBtn->setStyleSheet("QPushButton{border-image:url("+ m_strBtnImgN +");}"
//                        "QPushButton:checked{border-image:url("+ m_strBtnImgC +");}"
////                        "QPushButton:hover{border-image:url("+ m_strImgUrlC +");color:"+ m_strTextColor +";}"
//                        );
    m_pBtn->setText(CFaIcon::iconsQString(CFaIcon::Fa_toggle_off));
    m_pBtn->setStyleSheet("QPushButton{background-color:transparent;color:#ffffff;font:28px FontAwesome;}"
                          "QPushButton::checked{color:#30A7F8;}"
                        );
    connect(m_pBtn,&QPushButton::clicked,[=](bool bIsChecked){
        if(bIsChecked){
            m_pBtn->setText(CFaIcon::iconsQString(CFaIcon::Fa_toggle_on));
        }else{
            m_pBtn->setText(CFaIcon::iconsQString(CFaIcon::Fa_toggle_off));
        }
    });

    m_pBtn->setFixedSize(32,20);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLabel);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pBtn);
    hLayout->setContentsMargins(5,2,5,2);
    this->setLayout(hLayout);

}
