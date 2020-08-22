#ifndef TTABBAR_H
#define TTABBAR_H

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QResizeEvent>

/*Layout 会在this PaintEvent之前调整好子部件的所有位置 而不一定是在this showEvent
    手动show() 后布局没有立即调整好  ，
而系统默认调用show，那时布局已经都调整好了，可以在showEvent之后认为布局已调整好*/

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
    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent *event);
private:
    void initUI();


private:
    bool m_bFirstButton = true;
    QHBoxLayout *m_pHLayout = nullptr;
    QWidget *m_pWidgetSelected = nullptr;
    QButtonGroup *m_pBtnGp = nullptr;
    QAbstractButton *m_pBtnOld = nullptr;
    QPropertyAnimation *m_pAnimation = nullptr;
    bool m_bIsOk = false; //所有位置布局ok
};

#endif // TTABBAR_H
