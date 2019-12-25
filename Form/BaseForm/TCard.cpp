#include "TCard.h"
#include <QDebug>
#include <QApplication>
//父类最小宽度290

TCard::TCard(QWidget *parent) : QWidget(parent)
{
    m_nWidth = 260;
    initUI();
}

QWidget *TCard::addWidget(QWidget *pWidget, QString strColor,int nHeight)
{
    pWidget->setFixedWidth(m_nWidth);
    pWidget->setObjectName("CardWidgetItem");
    pWidget->setFixedHeight(nHeight);

    m_pVLayout->addWidget(pWidget);
    m_listWidget.append(pWidget);
    m_listColor.append(strColor);
    m_listHeight.append(nHeight);

    refreshStyle(); //设置样式
    return pWidget;
}

void TCard::insert(int nIndex,QWidget *pWidget, QString strColor, int nHeight)
{
    qDebug()<<"insert item 1" << nIndex;
    pWidget->setFixedWidth(m_nWidth);
    pWidget->setObjectName("CardWidgetItem");
    pWidget->setFixedHeight(nHeight);

    qDebug()<<"insert item 2" << nIndex;
    m_pVLayout->insertWidget(nIndex,pWidget);
    m_listWidget.insert(nIndex,pWidget);
    qDebug()<<"insert item 3" << nIndex;
    m_listColor.insert(nIndex,strColor);
    m_listHeight.insert(nIndex,nHeight);

    qDebug()<<"insert item 4" << nIndex;
    refreshStyle(); //设置样式
    qDebug()<<"insert item 5" << nIndex;
}

void TCard::bindDelSig(QWidget *pWidget)
{
    connect(pWidget,SIGNAL(sigDel(QWidget *)),this,SLOT(slotDelItem(QWidget *)));
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

void TCard::refreshStyle()
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

    int nGHeight = 0;
    foreach (int h, m_listHeight) {
         nGHeight += h;
    }
    this->setFixedHeight(nGHeight + (m_listHeight.count()-1)*2);


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

void TCard::slotDelItem(QWidget *pWidget)
{

    qDebug()<<"Card 删除Item";
    if(!m_listWidget.contains(pWidget))
        return;

    int nIndex = m_listWidget.indexOf(pWidget);

    m_listHeight.removeAt(nIndex);
    m_listColor.removeAt(nIndex);
    m_pVLayout->removeWidget(pWidget);
    m_listWidget.removeAt(nIndex);

    pWidget->deleteLater();

    refreshStyle(); //设置样式
}
