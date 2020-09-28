#ifndef CQUICKUI_H
#define CQUICKUI_H

#include <QObject>
#include <QApplication>
#include <QTimer>
#include <QDateTime>

//widgets
#include <QWidget>
#include <QLabel>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QFile>

class CQuickTools : public QObject
{
    Q_OBJECT
public:
    explicit CQuickTools(QObject *parent = 0);

public:
      //UI工具--------------------------------------------------------------------------------------------------------
      static void showUIBorder(QWidget *pObject,bool bShow = true); //界面上的基本控件显示边框 布局器也会显示
      static void widgetCenter(QWidget *pWidget,QWidget*parent = nullptr);

      //一个提示便签  会淡化消失 自动大小 字符串中加入\n可换行显示
      static void showHintLabel(QWidget *parent,QString strText,
                                QString strFontSize = "12px",
                                QString strColor = "#ffffff",
                                QString strBgColor = "#000000",
                                int nShowTime = 2*1000);
      static void installQss(QString strFile);

      //动画工具-------------------------------------------------------------------------------------------------------
      //控件抖动
      static void widgetShake(QWidget *pWidget,int nRange = 3);

      //基本工具-------------------------------------------------------------------------------------------------------

      //两个时间点之差转文本  如:3小时5分钟
      static QString subDateTime(QDateTime detmA,QDateTime detmB);
      //某个时间点与现在的时间差  转为文本  如:3分钟前 、 2小时5分钟后、 32秒后
      static QString toFutureDateTime(QDateTime detmFuture,bool *bIsFuture = nullptr); //是未来的时间点置true 否则为false
      //判断这个时间点是否在将来
      static bool isFutureDateTime(QDateTime detmFuture);
      //判断时间点是否已到 只精确到秒
      static bool isCurrentDateTime(QDateTime detm);

      /*进制转换*/
      static QByteArray hexStr2ByteArray(QString str);
      static QString byteArray2HexStr(QByteArray byteArr);
};

#endif // CQUICKUI_H
