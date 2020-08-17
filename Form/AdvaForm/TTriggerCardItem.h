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

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
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
    bool m_bOn = false; //表示鼠标是否在控件内
};


                
#endif // TTRIGGERCARDITEM_H
