#ifndef TSPLITTER_H
#define TSPLITTER_H

#include <QWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QList>

class TSplitter : public QWidget
{
    Q_OBJECT
public:
    explicit TSplitter(QWidget *parent = 0);
    QWidget *currentWidget(){return m_pNowFocusWidget;}
protected:
    virtual void addWidget(QWidget *parent);

signals:
    void sigNewWidget(QWidget *newWidget); //新建了一个textedit
    void sigCurrentWidget(QWidget *newWidget); //焦点textedit改变了
private:
    void initVal();
    void initUI();
    QSplitter *creatSplitter(Qt::Orientation orientation,QWidget *parent);
    void creatWidget(QWidget *parent);
    void removeWidget(QWidget *rmWidget);
    void removeSplitter(QSplitter *rmSplitter);
    void removeLastWidget();
    void removeLastSplitter();

public slots:
    void slotVSplitScreen(); //垂直分屏
    void slotHSplitScreen(); //水平分屏
    void slotMergeScreen();  //并且
    void slotFocusChange(QWidget *old, QWidget *now);

public:
    QList<QWidget *> m_listWidget;
private:
    QList<QSplitter *> m_plistSplitter;
    QWidget *m_pOldFocusWidget;
    QWidget *m_pNowFocusWidget;

    QWidget *m_pGrandgrandfather;
    QSplitter *m_pParentSplitter;
    QSplitter *m_pGrandpaSplitter;
    QWidget *m_pBrotherWidget;
    QSplitter *m_pUncleSplitter;
    QSplitter *m_pSplitterMain;
    QWidget *m_pWidgetMain;
    QHBoxLayout *m_pHLayout;
};


#endif // TSPLITTER_H
