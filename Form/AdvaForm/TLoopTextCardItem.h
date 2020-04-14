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

private:
    void initUI();
    void paintEvent(QPaintEvent *event);
private:
    QString m_strAppPath;
public:
    QLineEdit *m_pLineEdit;
    QComboBox *m_pComBox;
    QPushButton *m_pBtnDel;
};

#endif // TLOOPTEXTITEM_H
