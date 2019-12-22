#ifndef TLOOPTEXTITEM_H
#define TLOOPTEXTITEM_H

#include <QWidget>
#include <QLineEdit>
#include "TComBox.h"
#include <QPushButton>
#include <QPainter>

class TLoopTextCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLoopTextCardItem(QWidget *parent = 0);

private:
    void initUI();
    void paintEvent(QPaintEvent *event);
signals:
private:
    QLineEdit *m_pLineEdit;
    TComBox *m_pComBox;
    QPushButton *m_pBtnDel;
};

#endif // TLOOPTEXTITEM_H
