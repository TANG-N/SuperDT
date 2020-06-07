#include "MainWidget.h"
#include "TWindowLayoutDefine.h"
#include "clog.h"

#include <QVBoxLayout>
#include <QTimer>
#include <QApplication>
#include "TListCard.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";

    initUI();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);    // 设置尺寸属性
    this->setMinimumSize(400,300);
    this->setMouseTracking(true); //设置鼠标追踪  只要鼠标在本窗体内  就会触发MouseMoveEvent()
    this->resize(800,400);
    this->setWindowIcon(QIcon(m_strAppPath + "image/logo64.ico"));
    /*标题栏*/
    m_pTitleBar = new TitleBar(this);
    m_pTitleBar->setWindowTitle("SuperDT");

    /*状态栏*/
    m_pStatusBar = new StatusBar(this);

    /*主区域*/
    /*Msg和Setting*/
    m_pSettingArea = new TSettingArea(this);
    connect(m_pStatusBar,SIGNAL(signalVSplitScreen()),m_pSettingArea,SIGNAL(signalVSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalHSplitScreen()),m_pSettingArea,SIGNAL(signalHSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalMergeScreen()),m_pSettingArea,SIGNAL(signalMergeScreen()));

    QSizeGrip *sizeGrip = new QSizeGrip(this);//拖拽


    QHBoxLayout *layoutMsgAndSetting = new QHBoxLayout;
    layoutMsgAndSetting->addWidget(m_pSettingArea);
    layoutMsgAndSetting->setSpacing(0); //设置间距
    layoutMsgAndSetting->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pTitleBar);
    layout->addWidget(m_pStatusBar);
    layout->addLayout(layoutMsgAndSetting);
    layout->addWidget(sizeGrip);
    layout->setSpacing(0); //设置间距
    layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(layout);




}
