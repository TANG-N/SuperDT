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

    void insert(QWidget *pWidget,QString strColor = "#b9b9b9",int nHeight = 40);
    void removeAt(int nIndex);
    QWidget *at(int i);
    void processStyle();
protected:
    void paintEvent(QPaintEvent *event);

private:
    void initUI();
    QString getStyle(EnmStyle num,QString strColor);
    QString getStyle(QString strColor,QString strRadius);
private:
    int m_nWidth;

    QVBoxLayout *m_pVLayout;
    QList<int> m_listHeight;
    QList<QString> m_listColor;
    QList<QWidget *> m_listWidget;

};

#endif // TCARD_H
