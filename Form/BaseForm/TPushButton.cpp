#include "TPushButton.h"

TPushButton::TPushButton(QWidget *parent, bool status) : QPushButton(parent),m_bStatus(status)
{
    this->initUI();
}

void TPushButton::initUI()
{
    this->updateUI();
    this->setMinimumSize(32,32);
    connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
}

void TPushButton::slotClicked()
{
    m_bStatus = !m_bStatus;
    this->updateUI();
    emit signalChanged(m_bStatus); //按钮状态改变信号
}

void TPushButton::updateUI()
{
    if(m_bStatus)
        this->setStyleSheet(getImageStytle("btn_c.png"));
    else
        this->setStyleSheet(getImageStytle("btn_n.png"));
}

QString TPushButton::getImageStytle(QString strImage)
{
    return "TPushButton {border-image:url(:/image/icon/" + strImage + ")}";
}
