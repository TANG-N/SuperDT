#include "TLoopTextCardItem.h"
#include <QStyleOption>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>

TLoopTextCardItem::TLoopTextCardItem(QWidget *parent) : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initUI();
}

void TLoopTextCardItem::initUI()
{
    this->resize(285,35);
    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setMinimumWidth(150);
    m_pLineEdit->setFixedHeight(30);
    m_pLineEdit->setStyleSheet("background-color:#ffffff;color:#000000;border-radius:5px;");
    m_pComBox = new QComboBox(this);
    m_pComBox->setFixedHeight(30);
    //this->setAttribute(Qt::AA_AttributeCount);
    m_pComBox->setStyleSheet("QComboBox{background:#ffffff;"
                        "border-radius:5px;"
                        "padding:1px;"
                        "border: 4px solid #ffffff;"
                        "text-align:right;"
//                        "border-radius:5px;"
//                        "border-top-left-radius:5px;"
//                        "border-top-right-radius:5px;"
//                        "border-bottom-left-radius:5px;"
//                        "border-bottom-right-radius:5px;"
                        "color:#000000;"
                        "}"
                        "QComboBox::drop-down{"
                            "background-color:transparent;"
                            "width:20px;"
                            "top:1px;"
                            "height:20px;"
                            "left:0px;"
                        "}"
                        "QComboBox::down-arrow {"
                            "image:url(" + m_strAppPath + "image/form/combox-s.png);"
                        "}"
                        );

    QLineEdit* pTmpLineEdit = new QLineEdit();
    pTmpLineEdit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_pComBox->setLineEdit(pTmpLineEdit);

    m_pComBox->setEditable(true);
    m_pComBox->setMinimumWidth(65);
    m_pComBox->addItem("1");
    m_pComBox->addItem("2");


    m_pBtnDel = new QPushButton(this);
    m_pBtnDel->setFixedSize(28,28);
    m_pBtnDel->setStyleSheet("border-image:url("+ m_strAppPath + "image/setting/del.png);");

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pLineEdit);
    hLayout->addWidget(m_pComBox);
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
