#include "TCard.h"
#include <QDebug>

//父类最小宽度290

TCard::TCard(QWidget *parent) : QWidget(parent)
{
    m_nWidth = 260;
    initUI();
}

//void TCard::addItem(int nHeight, int nWidth, QString strColor)
//{
//    QWidget *pWidget = new QWidget(this);
//    pWidget->resize(nWidth,nHeight);
//    pWidget->setStyleSheet("background-color:" + strColor +";");

//    m_pVLayout->addWidget(pWidget);
//    m_listWidget.append(pWidget);

//    qDebug()<<"添加卡片条破"<<this->size();
//    processStyle(); //设置样式

//    this->setFixedHeight(m_listWidget.count()*40 + m_listWidget.count() - 1);

//}

QWidget *TCard::addWidget(QWidget *pWidget, QString strColor,int nHeight)
{
    pWidget->setFixedWidth(m_nWidth);
    pWidget->setObjectName("CardWidgetItem");
    pWidget->setFixedHeight(nHeight);

    m_pVLayout->addWidget(pWidget);
    m_listWidget.append(pWidget);
    m_listColor.append(strColor);
    m_listHeight.append(nHeight);

    processStyle(); //设置样式

    int nGHeight = 0;
    foreach (int h, m_listHeight) {
         nGHeight += h;
    }
    this->setFixedHeight(nGHeight + (m_listHeight.count()-1)*2);

    return pWidget;
}


QWidget *TCard::at(int i)
{
    return m_listWidget.at(i);
}

/******
 * Note:从 QWidget子类化  需要提供paintEvent
 * 详见 Qt Style Sheets Reference
 ******/
void TCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TCard::initUI()
{
    m_pVLayout = new QVBoxLayout(this);
    m_pVLayout->setSpacing(2);
    m_pVLayout->setContentsMargins(15,0,20,0);
}

void TCard::processStyle()
{
    int itemCount = m_listWidget.size();

    if(0 == itemCount)
        return ;

    /*只有一个  设置四角圆角*/
    if(1 == itemCount)
    {
        m_listWidget.at(0)->setStyleSheet(getStyle(ENM_ONLY_ONE,m_listColor.first()));
    }

    /*超过一个  设置第一个  和 最后一个圆角*/
    if(2 <= itemCount)
    {
        for(int i = 0; i < itemCount; i++){
            if(0 == i)
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_FIRST,m_listColor.first()));
            else if(i == (itemCount - 1))
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_END,m_listColor.last()));
            else
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_NORMAL,m_listColor.at(i)));
        }
    }

    foreach(QWidget* pWidget,m_listWidget){
        qDebug()<<"Height:"<<pWidget->height()<<"Stytle:"<<pWidget->styleSheet();
    }

    this->repaint();
}

QString TCard::getStyle(EnmStyle num, QString strColor)
{
    QString strStyle;

    switch (num) {
    case ENM_FIRST:
        strStyle = "background-color:" + strColor + ";border-top-left-radius:10px;"\
                   "border-top-right-radius:10px;color:#FFFFFF;";
        break;
    case ENM_NORMAL:
        strStyle = "background-color:"  + strColor + ";border-radius:0px;color:#FFFFFF;";
        break;
    case ENM_END:
        strStyle = "background-color:"  + strColor + ";border-bottom-left-radius:10px;"\
                   "border-bottom-right-radius:10px;color:#FFFFFF;";
        break;
    case ENM_ONLY_ONE:
        strStyle = "background-color:"  + strColor + ";"\
                   "border-radius:10px;color:#FFFFFF;";
        break;
    default:
        break;
    }

    return strStyle;
}
