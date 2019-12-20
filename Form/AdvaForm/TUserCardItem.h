#ifndef TUserCardItem_H
#define TUserCardItem_H

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

class TUserCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TUserCardItem(QWidget *parent = 0);

    void initUI();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    QLabel *m_pLabelUserPicBg; // 头像背景
    QLabel *m_pLabelUserPic;   // 头像
    QLabel *m_pLabelUserName;  // 用户名


};

#endif // TUserCardItem_H
