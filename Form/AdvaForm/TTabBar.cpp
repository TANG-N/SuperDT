#include "TTabBar.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>


TTabBar::TTabBar(QWidget *parent)
    : QFrame(parent)
{
    initUI();
}

void TTabBar::addTab(QString strText, int nId)
{
    QPushButton *pBtn = new QPushButton(this);
    pBtn->setText(strText);
    pBtn->setCheckable(true);
    pBtn->setStyleSheet("QPushButton{background:transparent;color:#000000;}"
                        "QPushButton:checked{background-color:transparent;color:#ffffff;}"
                        );
    m_pBtnGp->addButton(pBtn,nId);

    m_pHLayout->addWidget(pBtn);

    if(m_bFirstButton){
        m_bFirstButton = false;
        pBtn->setChecked(true);

    }
//    this->show();
    qDebug()<<"rect:"<<m_pBtnGp->checkedButton()->geometry();
    m_pWidgetSelected->setGeometry(m_pBtnGp->checkedButton()->geometry()); //Layout会将button变形  所以每添加一个按钮  需要重新调整背景的大小
}

void TTabBar::setChecked(int nTabId)
{
    m_pBtnGp->button(nTabId)->setChecked(true);
}

void TTabBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
     m_pWidgetSelected->setGeometry(m_pBtnGp->checkedButton()->geometry());
     return QWidget::resizeEvent(event);
}

void TTabBar::initUI()
{
    this->setMinimumSize(285,35);
    this->setObjectName("bg");
    this->setStyleSheet("#bg{background:#88bebebe;border-radius:5px;}");
    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->setContentsMargins(3,2,3,2);
    m_pHLayout->setSpacing(3);

    m_pBtnGp = new QButtonGroup(this);
    m_pBtnGp->setExclusive(true);
    connect(m_pBtnGp,SIGNAL(buttonClicked(int)),this,SIGNAL(sigSelected(int)));
    connect(m_pBtnGp, static_cast<void(QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
         [=](QAbstractButton *button, bool checked){
        if(checked){
             qDebug()<<"checked*******8888888888888888888888"<<checked<<button->geometry()<<m_pBtnGp->id(button);
            m_pAnimation->setStartValue(m_pWidgetSelected->geometry());
            m_pAnimation->setEndValue(button->geometry());
            m_pAnimation->start();
        }
    });

    m_pWidgetSelected = new QWidget(this);
    m_pWidgetSelected->setObjectName("selected");
    m_pWidgetSelected->setStyleSheet("#selected{background:#33ccff;border-radius:5px;}");
    /*阴影效果*/
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(8);        // 阴影圆角的大小
    effect->setColor(Qt::darkGray);      //阴影的颜色
    effect->setOffset(2,2);          //阴影的偏移量
    m_pWidgetSelected->setGraphicsEffect(effect); //

    m_pAnimation = new QPropertyAnimation(m_pWidgetSelected,"geometry",this);
    m_pAnimation->setDuration(100);
//    connect(m_pAnimation,&QPropertyAnimation::finished,[=]{
//        m_pWidgetSelected->hide();
//    });
}
