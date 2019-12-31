#ifndef TCARD_H
#define TCARD_H

#include <QWidget>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QList>
#include <QVector>

enum EnmStyle{
    ENM_FIRST = 0,
    ENM_NORMAL,
    ENM_END,
    ENM_ONLY_ONE,
};

class TCard : public QWidget
{
    Q_OBJECT
public:
    explicit TCard(QWidget *parent = 0);

    QWidget *addWidget(QWidget *pWidget,QString strColor = "#b9b9b9",int nHeight = 40);// #30a7f8
    QWidget *addWidget(QWidget *pWidget,bool bHaveChange = false,bool bHaveDel = false,\
                       QString strColor = "#b9b9b9",int nHeight = 40);
    void insert(int nIndex,QWidget *pWidget,QString strColor = "#b9b9b9",int nHeight = 40);
    void bindSignals(QWidget *pWidget,bool bHaveChange = false,bool bHaveDel = false);
    void bindDelSig(QWidget *pWidget);
    QWidget *at(int i);
    int count(){return m_listWidget.count();}
signals:
    void sigSettingChanged();
protected:
    void paintEvent(QPaintEvent *event);
private:
    void initUI();
    void refreshStyle();
    QString getStyle(EnmStyle num,QString strColor);
    //QString getStyle(QString strColor,QString strRadius);
private:
    int m_nWidth;

    QVBoxLayout *m_pVLayout;
    QList<int> m_listHeight;
    QList<QString> m_listColor;
    QList<QWidget *> m_listWidget;
private slots:
    void slotDelItem(QWidget *pWidget);
};

#endif // TCARD_H
