#ifndef TTRIGGERCARDITEM_H
#define TTRIGGERCARDITEM_H

#include <QWidget>
#include <QLineEdit>
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
public:
    QLineEdit *m_pLineEditR;
    QLineEdit *m_pLineEditS;
    QPushButton *m_pBtnDel;
private:
    QString m_strAppPath;
    QLabel *m_pLabelIcon;
};


                
#endif // TTRIGGERCARDITEM_H
