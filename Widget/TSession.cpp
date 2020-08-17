#include "TSession.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CFaIcon.h"

TSession::TSession(QWidget *parent)
    : QWidget(parent)
{
    init();
}

void TSession::appendText(QString strText)
{
    m_pTextEditor->appendPlainText(strText);
}

void TSession::appendPlainText(QString strText)
{
     m_pTextEditor->appendPlainText(strText);
}

void TSession::init()
{
    m_pWidgetTopBar = new QWidget(this);
    m_pWidgetTopBar->setFixedHeight(20);
    m_pLabelIpPort = new QLabel(this);
    m_pLabelIpPort->adjustSize();
    m_pLabelIpPort->setStyleSheet("QLabel{background:#66d9ff;border-radius:5px;color:#ffffff;padding:3px;}");

    m_pLabelState = new QLabel(this);
//    m_pLabelState->setFixedSize(15,15);
    m_pLabelState->setAlignment(Qt::AlignCenter);

    QHBoxLayout *pHLayout = new QHBoxLayout(m_pWidgetTopBar);
    pHLayout->setContentsMargins(5,2,5,2);
    pHLayout->setSpacing(3);
    pHLayout->addWidget(m_pLabelState);
    pHLayout->addWidget(m_pLabelIpPort);
    pHLayout->addStretch();

    m_pTextEditor = new TTextEditor(this);

    /*总布局*/
    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->setSpacing(0);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->addWidget(m_pWidgetTopBar);
    pVLayout->addWidget(m_pTextEditor);


    /*初始化状态栏*/
    slotsStateChanged("",0,false);
}

void TSession::slotsStateChanged(QString strIp, int nPort, bool bState)
{
    if(bState){
        m_pLabelState->setText(CFaIcon::iconsQString(CFaIcon::Fa_link));
        m_pLabelState->setStyleSheet("QLabel{background:#00e687;font:12px FontAwesome;color:#ffffff;border-radius:5px;padding:2px;}"); //绿色
    }else{
        m_pLabelState->setText(CFaIcon::iconsQString(CFaIcon::Fa_chain_broken));
         m_pLabelState->setStyleSheet("QLabel{background:#ff6666;font:12px FontAwesome;color:#ffffff;border-radius:5px;padding:2px;}"); //红色
    }

    if(strIp.isEmpty()){
        m_pLabelIpPort->hide();
    }else{
        m_pLabelIpPort->show();
        m_pLabelIpPort->setText(strIp + ":" + QString::number(nPort));
    }

}
