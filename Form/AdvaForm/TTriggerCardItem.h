#ifndef TTRIGGERCARDITEM_H
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

private:
    void initUI();
    void paintEvent(QPaintEvent *event);
signals:
    void sigDel(QWidget *pWidget);
private slots:
    void slotDel();
private:
    QLineEdit *m_pLineEditR;
    QLabel *m_pLabelIcon;
    QLineEdit *m_pLineEditS;
    QPushButton *m_pBtnDel;
};
#endif // TTRIGGERCARDITEM_H
