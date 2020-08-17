#include "MainWidget.h"
#include "TWindowLayoutDefine.h"
#include "clog.h"

#include <QVBoxLayout>
#include <QTimer>
#include <QApplication>
#include "TListCard.h"
#include "TCenterWidget.h"
#include <QGraphicsBlurEffect>
#include <QStackedLayout>


#include "TShadowEffect.h"

MainWidget::MainWidget(QWidget *parent)
    : QDialog(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";

    initUI();
}

MainWidget::~MainWidget()
{

}

void MainWidget::setBgImage(QString strUrl)
{

}

void MainWidget::initUI()
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);    // 设置尺寸属性
    this->setMouseTracking(true); //设置鼠标追踪  只要鼠标在本窗体内  就会触发MouseMoveEvent()
    this->resize(800,800);
    this->setWindowIcon(QIcon(m_strAppPath + "image/logo64.ico"));
    this->setObjectName("mainWidget");
    this->setStyleSheet("#mainWidget{border-radius:5px;}");
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);

    /*带阴影的透明背景*/



    /*模糊背景*/
    QGraphicsBlurEffect *pBlurEffect = new QGraphicsBlurEffect;
    pBlurEffect->setBlurRadius(30);

    m_pWidgetBg = new QWidget(this);
    m_pWidgetBg->setStyleSheet("QWidget{border-image:url(C:/Users/tang/Pictures/deepin/Flying_Whale_by_Shu_Le.jpg);}");
    m_pWidgetBg->setGraphicsEffect(pBlurEffect);

    QStackedLayout *pStackLayout = new QStackedLayout(this);
    pStackLayout->setContentsMargins(10,10,10,10);
    pStackLayout->setStackingMode(QStackedLayout::StackAll);
    pStackLayout->addWidget(m_pWidgetBg);
    pStackLayout->addWidget(createMainWidget());
    pStackLayout->setCurrentIndex(1);

//    layout();

//    /*窗口阴影效果*/
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(8);        // 阴影圆角的大小
//    effect->setColor(Qt::black);      //阴影的颜色
//    effect->setOffset(5,5);          //阴影的偏移量

//    TShadowEffect *pShadow = new TShadowEffect(this);
//    pShadow->setBlurRadius(20.0);
//    pShadow->setDistance(6.0);
//    pShadow->setColor(QColor(0, 0, 0, 80));
//    this->setGraphicsEffect(pShadow);
}

QWidget *MainWidget::createMainWidget()
{
    QWidget *pWidgetBg = new QWidget(this);

    /*标题栏*/
    m_pTitleBar = new TitleBar(pWidgetBg);
    m_pTitleBar->setWindowTitle("SuperDT");
    m_pTitleBar->setStyleSheet("TitleBar{background:#ffffff;}");

    TCenterWidget *pCenterWidget = new TCenterWidget(pWidgetBg);

    QSizeGrip *sizeGrip = new QSizeGrip(pWidgetBg);//拖拽

    QVBoxLayout *layout = new QVBoxLayout(pWidgetBg);
    layout->setSpacing(0); //设置间距
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_pTitleBar);
    layout->addWidget(pCenterWidget);
    layout->addWidget(sizeGrip);


    return pWidgetBg;
}
