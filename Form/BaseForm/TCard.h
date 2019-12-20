#ifndef TCARD_H
#define TCARD_H

#include <QWidget>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QList>

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

    void addItem(int nHeight = 40,int nWidth = 266,QString strColor = "#c55ccc");
    QWidget *addWidget(QWidget *pWidget);
    QWidget *at(int i);
    void processStyle();
protected:
    void paintEvent(QPaintEvent *event);

private:
    void initUI();
    QString getStyle(EnmStyle num);
    QString getStyle(QString strColor,QString strRadius);
private:
    int m_nHeight;
    int m_nWidth;
    QVBoxLayout *m_pVLayout;
    QList<QWidget *> m_listWidget;

};

#endif // TCARD_H
