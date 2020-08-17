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
    m_pLabelIpPort->setToolTip("连接到的地址");
    m_pLabelIpPort->setStyleSheet("QLabel{background:#66d9ff;border-radius:2px;color:#ffffff;padding:3px;font:12px SimHei;}");

    m_pLabelState = new QLabel(this);
    m_pLabelState->setToolTip("连接状态");
    m_pLabelState->setAlignment(Qt::AlignCenter);

    m_pBtnClear = new QPushButton(this);
    m_pBtnClear->setText(CFaIcon::iconsQString(CFaIcon::Fa_trash));
    m_pBtnClear->setToolTip("清空显示");
    m_pBtnClear->setFixedSize(16,16);
    m_pBtnClear->setStyleSheet("QPushButton{background:#009900;color:#ffffff;font:12px FontAwesome;border-radius:2px;}"
                               "QPushButton:hover{background:#00b300;color:#ffffff;font:12px FontAwesome;border-radius:2px;}"
                               "QPushButton:pressed{background:#009900;color:#ffffff;font:12px FontAwesome;border-radius:2px;}");
    connect(m_pBtnClear,&QPushButton::clicked,[=]{
        m_pTextEditor->clear();
    });

    QHBoxLayout *pHLayout = new QHBoxLayout(m_pWidgetTopBar);
    pHLayout->setContentsMargins(5,2,5,2);
    pHLayout->setSpacing(3);
    pHLayout->addWidget(m_pLabelState);
    pHLayout->addWidget(m_pLabelIpPort);
    pHLayout->addWidget(m_pBtnClear);
    pHLayout->addStretch();

    m_pTextEditor = new TTextEditor(this);
    /*！！！重要设置*/
    this->setFocusPolicy(Qt::ClickFocus); //开启本widget点击焦点
    m_pTextEditor->setFocusProxy(this); //本widget代理焦点
//    m_pTextEditor->setFocus(Qt::MouseFocusReason);


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
        m_pLabelState->setStyleSheet("QLabel{background:#00e687;font:12px FontAwesome;color:#ffffff;border-radius:2px;padding:2px;}"); //绿色
    }else{
        m_pLabelState->setText(CFaIcon::iconsQString(CFaIcon::Fa_chain_broken));
         m_pLabelState->setStyleSheet("QLabel{background:#ff6666;font:12px FontAwesome;color:#ffffff;border-radius:2px;padding:2px;}"); //红色
    }

    if(strIp.isEmpty()){
        m_pLabelIpPort->hide();
    }else{
        m_pLabelIpPort->show();
        m_pLabelIpPort->setText(strIp + ":" + QString::number(nPort));
    }

}
