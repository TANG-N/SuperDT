#include "TShadowEffect.h"
#include <QPainter>
#include <QApplication>
#include <QScreen>

TShadowEffect::TShadowEffect(QWidget *parent)
    :QWidget(parent)
{
    init();
}

void TShadowEffect::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);


    QScreen *pScreen = QApplication::primaryScreen();

//    painter.drawPixmap(QRect(0,0,100,100),pScreen->grabWindow(0),QRect(0,0,100,100));

    painter.drawPixmap(rect(),pScreen->grabWindow(0),QRect(pos().x(),pos().y(),width(),height()));
}

void TShadowEffect::init()
{
//    update();
    m_pBlur = new QGraphicsBlurEffect(this);
    this->setGraphicsEffect(m_pBlur);
}
