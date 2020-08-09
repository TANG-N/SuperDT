#include "TSettingBtnBar.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QButtonGroup>
#include <QApplication>
#include <QStyleOption>
#include "CFaIcon.h"

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
    this->setStyleSheet("QWidget{background-color:#55bebebe;}");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,10,0,10);
    layout->setSpacing(10);

    QButtonGroup *pBtnGroup = new QButtonGroup(this);
    pBtnGroup->setExclusive(true);

    QString strRight = CFaIcon::iconsQString(CFaIcon::Fa_chevron_right);
    QString strLeft = CFaIcon::iconsQString(CFaIcon::Fa_chevron_left);
    QPushButton *pBtnCloset = new QPushButton(this);//壁橱键  打开像壁橱一样
    pBtnCloset->setStyleSheet("QPushButton{background-color:transparent;color:#ffffff;font:16px FontAwesome;}"
                              "QPushButton::hover{background:#bdbdbd;}");
    pBtnCloset->setCheckable(true);
    pBtnCloset->setChecked(false);
    pBtnCloset->setText(strRight);
    pBtnCloset->setMinimumHeight(15);

    connect(pBtnCloset,&QPushButton::clicked,[=](bool bIsChecked){
        emit sigCloset(bIsChecked);
        if(bIsChecked)
            pBtnCloset->setText(strLeft);
        else
            pBtnCloset->setText(strRight);
    });
    layout->addWidget(pBtnCloset);
    layout->addStretch(1);

    /*按模块划分的多个按钮*/
    QStringList strListIcon;
    strListIcon <<CFaIcon::iconsQString(CFaIcon::Fa_list_alt)
           <<CFaIcon::iconsQString(CFaIcon::Fa_user_circle_o)
          <<CFaIcon::iconsQString(CFaIcon::Fa_file_text_o)
         <<CFaIcon::iconsQString(CFaIcon::Fa_download)
        <<CFaIcon::iconsQString(CFaIcon::Fa_paper_plane_o);

    foreach(QString strUrl,strListIcon){
        QPushButton *pSettingBtn = new QPushButton(this);
        pSettingBtn->setText(strUrl);
        pSettingBtn->setStyleSheet("QPushButton{background-color:transparent;color:#ffffff;font:22px FontAwesome;}"
                                   "QPushButton::checked{color:#30A7F8;text-decoration:underline;}"
                                   "QPushButton::hover{color:#30A7F8;}"
                                   "QPushButton::pressed{color:#30A7F8;font-style:italic;}"
                                   );
        pSettingBtn->setMinimumSize(m_sIconSize);
        pSettingBtn->setCheckable(true);
        pBtnGroup->addButton(pSettingBtn,strListIcon.indexOf(strUrl));
        layout->addWidget(pSettingBtn);
    }
    layout->addStretch(1);
    this->setLayout(layout);
}

void TSettingBtnBar::slotBtnClicked(QString strId)
{
    emit sigSettingBtn(strId);
}
