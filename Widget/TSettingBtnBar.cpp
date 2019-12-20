#include "TSettingBtnBar.h"
#include "TLockButton.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>

TSettingBtnBar::TSettingBtnBar(QWidget *parent)
    :QWidget(parent)
{
    m_sIconSize = QSize(24,24);
    m_strImgUrl = ":/image/icon/setting/";
    init();
}

void TSettingBtnBar::init()
{
    createView();
}

void TSettingBtnBar::createView()
{
    this->setFixedWidth(36);
    //this->setStyleSheet("QWidget{background-color:#bebebe;}");

    QStringList listUrl;
    listUrl <<"menu"<<"user"<<"protocol"<<"download"<<"send";

    QButtonGroup *pBtnGroup = new QButtonGroup(this);
    pBtnGroup->setExclusive(true);

    foreach(QString strUrl,listUrl){
        TLockButton *pSettingBtn = new TLockButton(strUrl,m_strImgUrl + strUrl + "_n.png",m_strImgUrl + strUrl + "_c.png",this);
        pSettingBtn->setFixedSize(m_sIconSize);
        pSettingBtn->setCheckable(true);
        connect(pSettingBtn,SIGNAL(sigClicked(QString)),this,SLOT(slotBtnClicked(QString)));
        m_vecBtn.push_back(pSettingBtn);
        pBtnGroup->addButton(pSettingBtn);
    }

    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addSpacing(5);
//    layout->addWidget(m_vecBtn.at(0));
    layout->addStretch(1);
    for(int i = 0; i < m_vecBtn.count(); i++){
        layout->addWidget(m_vecBtn.at(i));
        layout->addSpacing(10);
    }
    layout->addStretch(1);
    layout->setContentsMargins(2, 0, 2, 0);

    this->setLayout(layout);
}

void TSettingBtnBar::slotBtnClicked(QString strId)
{
    qDebug()<<"btn Id:"<<strId;
    emit sigSettingBtn(strId);
}
