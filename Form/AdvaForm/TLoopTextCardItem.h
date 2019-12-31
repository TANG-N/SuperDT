#ifndef TLOOPTEXTITEM_H
#define TLOOPTEXTITEM_H

#include <QWidget>
#include <QLineEdit>
#include "TComBox.h"
#include <QPushButton>
#include <QPainter>

class TLoopTextCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLoopTextCardItem(QWidget *parent = 0);

    QString currentText(){return m_pLineEdit->text();}
    int pollTime(){return m_pComBox->currentText().toInt();}
private:
    void initUI();
    void paintEvent(QPaintEvent *event);
signals:
    void sigSettingChanged();
    void sigDel(QWidget *pWidget);
private slots:
    void slotDel();
private:
    QString m_strAppPath;
    QLineEdit *m_pLineEdit;
    TComBox *m_pComBox;
    QPushButton *m_pBtnDel;
};

#endif // TLOOPTEXTITEM_H
