﻿#ifndef TTRIGGERCARDITEM_H
#define TTRIGGERCARDITEM_H

#include <QWidget>
#include <QLineEdit>
#include "TComBox.h"
#include <QPushButton>
#include <QPainter>
#include <QLabel>

class TTriggerCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TTriggerCardItem(QWidget *parent = 0);

    QString recvText(){return m_pLineEditR->text();}
    QString sendText(){return m_pLineEditS->text();}
private:
    void initUI();
    void paintEvent(QPaintEvent *event);
signals:
    void sigSettingChanged();
    void sigDel(QWidget *pWidget);
private slots:
    void slotDel();
private:
    QString m_strAppPath;
    QLineEdit *m_pLineEditR;
    QLabel *m_pLabelIcon;
    QLineEdit *m_pLineEditS;
    QPushButton *m_pBtnDel;
};
#endif // TTRIGGERCARDITEM_H
