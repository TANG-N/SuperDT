#ifndef TLockButtonCardItem_H
#define TLockButtonCardItem_H

#include <QWidget>
#include <QLabel>
#include "TLockButton.h"

class TLockButtonCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TLockButtonCardItem(QString strText,QWidget *parent = 0);

    bool currentState(){return m_pLockBtn->isChecked();}
private:
    void initUI();
    void paintEvent(QPaintEvent *event);
signals:
    void sigSettingChanged();
    void sigBtnClicked(bool bState);
private slots:
    void slotBtnClicked();
private:
    QString m_strAppPath;
    QString m_strText;
    QString m_strBtnImgN;
    QString m_strBtnImgC;
    QLabel *m_pLabel;
    TLockButton *m_pLockBtn;
};

#endif // TLockButtonCardItem_H
