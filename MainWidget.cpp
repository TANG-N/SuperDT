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
    //    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::Tool);

    /*模糊背景*/
    QGraphicsBlurEffect *pBlurEffect = new QGraphicsBlurEffect;
    pBlurEffect->setBlurRadius(30);

    m_pWidgetBg = new QWidget(this);
    m_pWidgetBg->setStyleSheet("QWidget{border-image:url(C:/Users/anfae/Pictures/deepin/luca-micheli-ruWkmt3nU58-unsplash.jpg);}");
    m_pWidgetBg->setGraphicsEffect(pBlurEffect);

    QStackedLayout *pStackLayout = new QStackedLayout(this);
    pStackLayout->setStackingMode(QStackedLayout::StackAll);
    pStackLayout->addWidget(m_pWidgetBg);
    pStackLayout->addWidget(createMainWidget());
    pStackLayout->setCurrentIndex(1);
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
