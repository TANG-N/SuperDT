#include "TSettingBtnBar.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>
#include <QApplication>
#include <QStyleOption>

TSettingBtnBar::TSettingBtnBar(QWidget *parent)
    :QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    m_sIconSize = QSize(24,24);
    m_strImgUrl = m_strAppPath + "image/setting/";
    init();
}

void TSettingBtnBar::init()
{
    createView();
}

void TSettingBtnBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void TSettingBtnBar::createView()
{
    this->setFixedWidth(36);
    this->setStyleSheet("QWidget{background-color:#bebebe;}");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,10,0,10);
    layout->setSpacing(10);

    QButtonGroup *pBtnGroup = new QButtonGroup(this);
    pBtnGroup->setExclusive(true);

    QPushButton *pBtnCloset = new QPushButton(this);//壁橱键  打开像壁橱一样
    pBtnCloset->setStyleSheet("background-color:transparent;color:#ffffff;border:1px solid #ffffff;radius:10px;");
    pBtnCloset->setCheckable(true);
    pBtnCloset->setText(">");
    connect(pBtnCloset,&QPushButton::clicked,[=](bool bIsChecked){
        emit sigCloset(bIsChecked);
        if(bIsChecked)
            pBtnCloset->setText(">");
        else
            pBtnCloset->setText("<");
    });
    layout->addWidget(pBtnCloset);
    layout->addStretch(1);

    /*按模块划分的多个按钮*/
    QStringList listUrl;
    listUrl <<"menu"<<"user"<<"protocol"<<"download"<<"send";
    foreach(QString strUrl,listUrl){
        QPushButton *pSettingBtn = new QPushButton(this);
        pSettingBtn->setStyleSheet("QPushButton{border-image:url("+ m_strImgUrl + strUrl + "_n.png" +");}"
                                   "QPushButton:checked{border-image:url("+ m_strImgUrl + strUrl + "_c.png" +");}"
                                    //"QPushButton:hover{border-image:url("+ m_strImgUrlC +");color:"+ m_strTextColor +";}"
                                   );
        pSettingBtn->setFixedSize(m_sIconSize);
        pSettingBtn->setCheckable(true);
        pBtnGroup->addButton(pSettingBtn,listUrl.indexOf(strUrl));
        layout->addWidget(pSettingBtn);
    }
    layout->addStretch(1);
    this->setLayout(layout);
}

void TSettingBtnBar::slotBtnClicked(QString strId)
{
    emit sigSettingBtn(strId);
}
