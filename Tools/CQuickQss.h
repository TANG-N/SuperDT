#ifndef CQUICKQSS_H
#define CQUICKQSS_H

#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QSlider>
#include <QRadioButton>
#include <QScrollBar>
#include <QLabel>

class CQuickQss : public QObject
{
    Q_OBJECT
public:
    explicit CQuickQss(QObject *parent = nullptr);

    // !!!!必须设置ObejctName
    //用于 背景图的样式  需提前设置好任意的ObjectName可用QWidget QFrame QLabel等
    static QString setBgQss(QWidget *pWidget,
                            QString strBgImage);
    //用于文本显示的 QLabel
    static QString setTextLabelQss(QLabel *pLabel,
                               QString strColor,                                    //字体颜色
                               QString strFontSize,                                      //字体大小
                               QString strFont = "SimHei",                          //字体
                               QString strBgColor = "transparent");                 //背景颜色


    static QString setHoverBtnQss(QPushButton *pBtn,
                                  QString strNormalImage,             //默认、按下背景图
                                  QString strHoverImage = "");       //悬浮背景图

    static QString setHoverCheckBtnQss(QPushButton *pBtn,
                                  QString strNormalImage,
                                  QString strCheckedImage = "");     //被选中背景图

    static QString setCheckBtnQss(QPushButton *pBtn,
                                  QString strNormalImage,
                                  QString strCheckedImage = "");     //被选中背景图

    static QString setPressBtnQss(QPushButton *pBtn,
                                  QString strNormalImage,             //默认按钮背景图
                                  QString strPressedImage = "");       //高亮背景图









    //设置按钮样式
    static QString setPushButtonQss(QPushButton *btn,                               //按钮对象
                                    int radius = 5,                                 //圆角半径
                                    int padding = 8,                                //间距
                                    const QString &normalColor = "#34495E",         //正常颜色
                                    const QString &normalTextColor = "#FFFFFF",     //文字颜色
                                    const QString &hoverColor = "#4E6D8C",          //悬停颜色
                                    const QString &hoverTextColor = "#F0F0F0",      //悬停文字颜色
                                    const QString &pressedColor = "#2D3E50",        //按下颜色
                                    const QString &pressedTextColor = "#B8C6D1");   //按下文字颜色

    //设置文本框样式
    static QString setLineEditQss(QLineEdit *txt,                                   //文本框对象
                                  int radius = 3,                                   //圆角半径
                                  int borderWidth = 2,                              //边框大小
                                  const QString &normalColor = "#DCE4EC",           //正常颜色
                                  const QString &focusColor = "#34495E");           //选中颜色

    //设置进度条样式
    static QString setProgressBarQss(QProgressBar *bar,
                                     int barHeight = 8,                             //进度条高度
                                     int barRadius = 5,                             //进度条半径
                                     int fontSize = 9,                              //文字字号
                                     const QString &normalColor = "#E8EDF2",        //正常颜色
                                     const QString &chunkColor = "#E74C3C");        //进度颜色

    //设置滑块条样式
    static QString setSliderQss(QSlider *slider,                                    //滑动条对象
                                int sliderHeight = 8,                               //滑动条高度
                                const QString &normalColor = "#E8EDF2",             //正常颜色
                                const QString &grooveColor = "#1ABC9C",             //滑块颜色
                                const QString &handleBorderColor = "#1ABC9C",       //指示器边框颜色
                                const QString &handleColor = "#FFFFFF",             //指示器颜色
                                const QString &textColor = "#000000");              //文字颜色

    //设置单选框样式
    static QString setRadioButtonQss(QRadioButton *rbtn,                            //单选框对象
                                     int indicatorRadius = 8,                       //指示器圆角角度
                                     const QString &normalColor = "#D7DBDE",        //正常颜色
                                     const QString &checkColor = "#34495E");        //选中颜色

    //设置滚动条样式
    static QString setScrollBarQss(QWidget *scroll,                                 //滚动条对象
                                   int radius = 6,                                  //圆角角度
                                   int min = 120,                                   //指示器最小长度
                                   int max = 12,                                    //滚动条最大长度
                                   const QString &bgColor = "#606060",              //背景色
                                   const QString &handleNormalColor = "#34495E",    //指示器正常颜色
                                   const QString &handleHoverColor = "#1ABC9C",     //指示器悬停颜色
                                   const QString &handlePressedColor = "#E74C3C");  //指示器按下颜色

};

#endif // CQUICKQSS_H
