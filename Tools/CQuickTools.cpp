#include "CQuickTools.h"
#include <QDebug>
CQuickTools::CQuickTools(QObject *parent) : QObject(parent)
{

}


void CQuickTools::showUIBorder(QWidget *pObject, bool bShow)
{
    if((nullptr == pObject) || (!bShow))
        return ;

//    /*清空子类的旧样式*/
//    foreach(QObject *pObject,pObject->children()){
//        QWidget *pWidget = qobject_cast<QWidget *>(pObject);
//        if(pWidget){
//            pWidget->setStyleSheet("");
//        }
//    }

    int nBoderWidth = 1;

    QString strWidgetColor = "#0dff80"; //浅绿 #0dff80
    QString strFrameColor = "#0bdedd";  //青色 #0bdedd
    QString strLabelColor = "0080f5";   //蓝色 0080f5
    //深蓝 #0B12DE
    QString strButtonColor = "#9234FA";//紫色 #9234FA

    QStringList strListStyle;
    strListStyle.append(QString("QWidget{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strWidgetColor));
    strListStyle.append(QString("QFrame{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strFrameColor));
    strListStyle.append(QString("QLabel{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strLabelColor));
    strListStyle.append(QString("QPushButton{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strButtonColor));


    pObject->setStyleSheet(strListStyle.join(""));
}

void CQuickTools::widgetCenter(QWidget *pWidget, QWidget *parent)
{
    QSize parentSize = (nullptr == parent) ? QApplication::desktop()->screenGeometry().size() : parent->size(); //双屏情况下在主屏幕上提示
    QSize subSize = parentSize - pWidget->size();

    pWidget->move(subSize.width()/2,subSize.height()/2);
}

void CQuickTools::showHintLabel(QWidget *parent, QString strText, QString strFontSize, QString strColor, QString strBgColor, int nShowTime)
{
    if(nullptr == parent){
        parent = QApplication::desktop()->screen();
    }

    QFrame *pFrmBg = new QFrame(parent); //为了兼容parent为nullptr时的圆角边框  方法是背景透明 上边叠加圆角控件

    QLabel *pHintLabel = new QLabel(pFrmBg);
    pHintLabel->setStyleSheet(QString("QLabel{background:%1;color:%2;font:%3 SimHei;border-radius:5px;}")
                              .arg(strBgColor).arg(strColor).arg(strFontSize));
    pHintLabel->setText(strText);
    pHintLabel->setAlignment(Qt::AlignCenter);
    pHintLabel->adjustSize();
    pHintLabel->resize(pHintLabel->size() + QSize(60,30));

    pFrmBg->resize(pHintLabel->size());
    pFrmBg->setWindowFlags(Qt::FramelessWindowHint);
    pFrmBg->setAttribute(Qt::WA_TranslucentBackground);
    CQuickTools::widgetCenter(pFrmBg,parent);
    pFrmBg->show();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(pFrmBg,"windowOpacity");
    pAnimation->setDuration(nShowTime);
    pAnimation->setEasingCurve(QEasingCurve::InCirc);
    pAnimation->setStartValue(1.0f);
    pAnimation->setEndValue(0.0f);
    pAnimation->start();
    connect(pAnimation,&QPropertyAnimation::finished,[=]{
        delete pAnimation;
        delete pFrmBg;
    });
}

void CQuickTools::installQss(QString strFile)
{
    QFile fileQss(strFile);
    if(fileQss.open(QFile::ReadOnly)){
        qApp->setStyleSheet(fileQss.readAll());
        fileQss.close();
    }else{
        qWarning()<<strFile<<";文件打开失败!";
    }
}

void CQuickTools::widgetShake(QWidget *pWidget, int nRange)
{
    int nX = pWidget->x();
    int nY = pWidget->y();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(pWidget,"geometry");
    pAnimation->setEasingCurve(QEasingCurve::InOutSine);
    pAnimation->setDuration(300);
    pAnimation->setStartValue(QRect(QPoint(nX,nY),pWidget->size()));

    int nShakeCount = 20; //抖动次数
    double nStep = 1.0/nShakeCount;
    for(int i = 1; i < nShakeCount; i++){
        nRange = i&1 ? -nRange : nRange;
        pAnimation->setKeyValueAt(nStep*i,QRect(QPoint(nX + nRange,nY),pWidget->size()));
    }

    pAnimation->setEndValue(QRect(QPoint(nX,nY),pWidget->size()));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

QString CQuickTools::subDateTime(QDateTime detmA, QDateTime detmB)
{
    qint64 secs = qAbs(detmA.secsTo(detmB)); //绝对值

    const int N_MINUTE = 60;
    const int N_HOUR = N_MINUTE * 60;
    const int N_DAY = N_HOUR * 24;
    QString strSubDetm = "";

    int nDays = secs/N_DAY;
    secs = secs%N_DAY;
    strSubDetm += nDays > 0 ? QString("%1天").arg(nDays) : "";

    int nHours = secs/N_HOUR;
    secs = secs%N_HOUR;
    strSubDetm += nHours > 0 ? QString("%1小时").arg(nHours) : "";

    int nMinutes = secs/N_MINUTE;
    secs = secs%N_MINUTE;
    strSubDetm += nMinutes > 0 ? QString("%1分钟").arg(nMinutes) : "";

    /*细化显示  显示秒*/
    int nSecond = secs;
    if((nDays == 0) && (0 == nHours) && (0 == nMinutes)){//其他值都为0显示秒数
        strSubDetm += nSecond > 0 ? QString("%1秒").arg(nSecond) : "";
    }

    return strSubDetm;
}

QString CQuickTools::toFutureDateTime(QDateTime detmFuture, bool *bIsFuture)
{
    if(nullptr == bIsFuture)
        bIsFuture = new bool;

    *bIsFuture = true;

    qint64 secs = QDateTime::currentDateTime().secsTo(detmFuture);

    if(secs <= 0){
        *bIsFuture = false;
        secs = qAbs(secs);
    }

    const int N_MINUTE = 60;
    const int N_HOUR = N_MINUTE * 60;
    const int N_DAY = N_HOUR * 24;
    QString strSubDetm = "";

    int nDays = secs/N_DAY;
    secs = secs%N_DAY;
    strSubDetm += nDays > 0 ? QString("%1天").arg(nDays) : "";

    int nHours = secs/N_HOUR;
    secs = secs%N_HOUR;
    strSubDetm += nHours > 0 ? QString("%1小时").arg(nHours) : "";

    int nMinutes = secs/N_MINUTE;
    secs = secs%N_MINUTE;
    strSubDetm += nMinutes > 0 ? QString("%1分钟").arg(nMinutes) : "";

    /*细化显示  显示秒*/
    int nSecond = secs;
    if((nDays == 0) && (0 == nHours) && (0 == nMinutes)){//其他值都为0显示秒数
        strSubDetm += nSecond > 0 ? QString("%1秒").arg(nSecond) : "";
    }

    return strSubDetm += strSubDetm.isEmpty() ? "现在" : (*bIsFuture == true) ? "后" : "前";
}

bool CQuickTools::isFutureDateTime(QDateTime detmFuture)
{
    qint64 nMsecs = QDateTime::currentDateTime().secsTo(detmFuture);

    return nMsecs <= 0 ? false : true;
}

bool CQuickTools::isCurrentDateTime(QDateTime detm)
{
    return (detm.toTime_t() == QDateTime::currentDateTime().toTime_t());
}
