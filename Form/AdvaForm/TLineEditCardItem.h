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
};

#endif // TLINEEDITCARDITEM_H
