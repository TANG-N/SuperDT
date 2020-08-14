/************************************
            开发日志
2019/09/17
    实现功能：最小化、最大化、关闭窗口、左键点击移动窗口位置、双击最大化或默认大小

************************************/

#include "TitleBar.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QApplication>
#include "CFaIcon.h"
#include <QStyle>
#include <QApplication>


TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initVal();
    initUI();
}

void TitleBar::setWindowTitle(QString strTitle)
{
    m_pLabelTitle->setAlignment(Qt::AlignCenter);
    m_pLabelTitle->setText(strTitle);
}

void TitleBar::initVal()
{
    m_strIconPath = "/image/icon/";
    m_pParentWindow = this->window(); //获取本部件所处的窗口
}

void TitleBar::initUI()
{
    this->setFixedHeight(32);

    m_pMenu = new QMenu(this);
    m_pMenu->addAction("透明度设置");
    m_pMenu->addAction("背景设置");

    m_pBtnIcon = new QPushButton(this);
    m_pBtnIcon->setFixedSize(24,24);  //设置最大宽高和最小宽高固定  不再拉伸
    m_pBtnIcon->setStyleSheet("QPushButton {border-image:url("+ m_strAppPath + "image/logo32.png)}"
                              "QPushButton::hover{}");
    connect(m_pBtnIcon,&QPushButton::clicked,[=]{
        m_pMenu->exec(m_pBtnIcon->mapToGlobal(m_pBtnIcon->rect().bottomLeft()));
    });

    m_pLabelTitle = new QLabel(this);
    m_pLabelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pLabelTitle->setStyleSheet("color:#ffffff;");

    m_pMinButton = new QPushButton(this);
    m_pMinButton->setFixedSize(24,24);
    m_pMinButton->setStyleSheet(getImageStytle("min-gray.png"));
//    QIcon iconMini = QApplication::style()->standardIcon(QStyle::SP_TitleBarMinButton);
//    m_pMinButton->setIconSize(QSize(50,50));
//    m_pMinButton->setIcon(iconMini);
//    m_pMinButton->setText(CFaIcon::iconsQString(CFaIcon::Fa_minus_square_o));
//    m_pMinButton->setStyleSheet("QPushButton{background-color:transparent;color:#000000;font:22px FontAwesome;}"
//                               "QPushButton::checked{color:#30A7F8;text-decoration:underline;}"
//                               "QPushButton::hover{background-color:#B3C9D9;color:#30A7F8;}"
//                               "QPushButton::pressed{color:#30A7F8;font-style:italic;}"
//                               );
    connect(m_pMinButton,SIGNAL(clicked()),this,SLOT(slotMin()));

    m_pMaxButton = new QPushButton(this);
    m_pMaxButton->setFixedSize(24,24);
    m_pMaxButton->setStyleSheet(getImageStytle("max-gray.png"));
//    m_pMaxButton->setText(CFaIcon::iconsQString(CFaIcon::Fa_clone));
//    m_pMaxButton->setStyleSheet("QPushButton{background-color:transparent;color:#000000;font:22px FontAwesome;}"
//                               "QPushButton::checked{color:#30A7F8;text-decoration:underline;}"
//                               "QPushButton::hover{background-color:#B3C9D9;color:#30A7F8;}"
//                               "QPushButton::pressed{color:#30A7F8;font-style:italic;}"
//                               );
    connect(m_pMaxButton,SIGNAL(clicked()),this,SLOT(slotMax()));

    m_pExitButton = new QPushButton(this);
    m_pExitButton->setFixedSize(24,24);
    m_pExitButton->setStyleSheet(getImageStytle("exit-gray.png"));
//    m_pExitButton->setText(CFaIcon::iconsQString(CFaIcon::Fa_window_close_o));
//    m_pExitButton->setStyleSheet("QPushButton{background-color:transparent;color:#000000;font:22px FontAwesome;}"
//                               "QPushButton::checked{color:#30A7F8;text-decoration:underline;}"
//                               "QPushButton::hover{background-color:#FF2821;color:#ffffff;}"
//                               "QPushButton::pressed{color:#30A7F8;font-style:italic;}"
//                               );
    connect(m_pExitButton,SIGNAL(clicked()),this,SLOT(slotExit()));


    QHBoxLayout* layout = new QHBoxLayout;
    layout->addSpacing(5);
    layout->addWidget(m_pBtnIcon);
    layout->addStretch(1);  //中间添加一个拉伸量 空白区
    layout->addWidget(m_pLabelTitle);
    layout->addStretch(1);
    layout->addWidget(m_pMinButton);
    layout->addWidget(m_pMaxButton);
    layout->addWidget(m_pExitButton);
    layout->setContentsMargins(0, 0, 5, 0);//设置左、上、右、下 M argins

    setLayout(layout);
}

QString TitleBar::getImageStytle(QString strImage)
{
    return "QPushButton {border-image:url("+ m_strAppPath + "image/form/" + strImage + ")}";
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftButtonPressed)
    {
        m_pParentWindow->move(event->globalPos() - m_pointDPos);//鼠标松开的全局位置 - 鼠标位置与窗口位置差
    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = true;//记录按键按下

        m_pointWindowPos = m_pParentWindow->pos();
        m_pointMousePos = event->globalPos();                   // 获得鼠标在屏幕中的全局位置
        m_pointDPos = m_pointMousePos - m_pointWindowPos;       // 鼠标位置与窗口位置差
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)  // 鼠标左键释放
    {
        m_bLeftButtonPressed = false;       // 记录鼠标状态
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    slotMax();
}
void TitleBar::slotExit()
{
    m_pParentWindow->close();
}

void TitleBar::slotMax()
{
    if(m_pParentWindow->isMaximized())
        m_pParentWindow->showNormal();
    else
        m_pParentWindow->showMaximized();
}

void TitleBar::slotMin()
{
    m_pParentWindow->showMinimized();
}


