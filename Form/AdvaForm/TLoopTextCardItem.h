#ifndef TLOOPTEXTITEM_H
#define TLOOPTEXTITEM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QComboBox>

class TLoopTextCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLoopTextCardItem(QWidget *parent = 0);
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    void initUI();
    void paintEvent(QPaintEvent *event);
private:
    QString m_strAppPath;
public:
    QLineEdit *m_pLineEdit;
    QPushButton *m_pBtnDel;
    bool m_bOn = false; //表示鼠标是否在控件内
};

#endif // TLOOPTEXTITEM_H
