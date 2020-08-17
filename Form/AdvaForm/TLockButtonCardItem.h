#ifndef TLockButtonCardItem_H
#define TLockButtonCardItem_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TLockButtonCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLockButtonCardItem(QString strText,QWidget *parent = 0);

public:
    QLabel *m_pLabel;
    QPushButton *m_pBtn;
private:
    void initUI();
    void paintEvent(QPaintEvent *event);

private:
    QString m_strAppPath;
    QString m_strText;
};

#endif // TLockButtonCardItem_H
