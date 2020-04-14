#ifndef TCOMBOXCARDITEM_H
#define TCOMBOXCARDITEM_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QVector>
#include <QPainter>

class TComBoxCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TComBoxCardItem(QString strText,QStringList strList,QWidget *parent = 0);

private:
    void init();
    void paintEvent(QPaintEvent *event);
private:
    QString m_strText = "新建Combox";
    QStringList m_strListItems;
    QString m_strImgPath = "";
public:
    QLabel *m_pLabel;
    QComboBox *m_pComBox;
};

#endif // TCOMBOXCARDITEM_H
