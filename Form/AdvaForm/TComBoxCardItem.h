﻿#ifndef TCOMBOXCARDITEM_H
#define TCOMBOXCARDITEM_H

#include <QWidget>
#include "TComBox.h"
#include <QLabel>
#include <QVector>
#include <QPainter>

class TComBoxCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TComBoxCardItem(QString strText,QVector<QString> vecItems,QWidget *parent = 0);

    void addItems(QVector<QString> vecItem);
    void setText(QString strText){m_strText = strText;refreshStyle();}
    QString currentText(){return m_pComBox->currentText();}
    int currentIndex(){return m_pComBox->currentIndex();}
signals:
    void sigSettingChanged();
private:
    void init();
    void paintEvent(QPaintEvent *event);
    void refreshStyle();
private:
    QString m_strText;
    QVector<QString> m_vecItems;

public:
    QLabel *m_pLabel;
    TComBox *m_pComBox;
};

#endif // TCOMBOXCARDITEM_H
