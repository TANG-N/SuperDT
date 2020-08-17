#ifndef TLINEEDITCARDITEM_H
#define TLINEEDITCARDITEM_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLineEdit>

class TLineEditCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLineEditCardItem(QString strBtnText,QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    void init();
    void paintEvent(QPaintEvent *event);
private:
    QString m_strBtnText = "";
    QString m_strAppPath = "";
public:
    QLineEdit *m_pLineEdit = nullptr;
    QPushButton *m_pBtn = nullptr;
    QPushButton *m_pBtnDel;
    bool m_bOn = false; //表示鼠标是否在控件内
};

#endif // TLINEEDITCARDITEM_H
