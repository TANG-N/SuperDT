#ifndef TTABBAR_H
#define TTABBAR_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QResizeEvent>

class TTabBar : public QFrame
{
    Q_OBJECT
public:
    explicit TTabBar(QWidget *parent = 0);

    void addTab(QString strText,int nId);
    void setChecked(int nTabId);
signals:
    void sigSelected(int nSelectedId);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    void initUI();


private:
    bool m_bFirstButton = true;
    QHBoxLayout *m_pHLayout = nullptr;
    QWidget *m_pWidgetSelected = nullptr;
    QButtonGroup *m_pBtnGp = nullptr;
    QAbstractButton *m_pBtnOld = nullptr;
    QPropertyAnimation *m_pAnimation = nullptr;
};

#endif // TTABBAR_H
