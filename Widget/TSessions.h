#ifndef TSESSIONS_H
#define TSESSIONS_H

#include <QWidget>
#include <QList>
#include <QSplitter>
#include <QHBoxLayout>

#include "TSession.h"

class TSessions : public QWidget
{
    Q_OBJECT
public:
    explicit TSessions(QWidget *parent = 0);

    TSession *currentTextEditor(){return m_pNowFocusTextEditor;}
signals:
    void sigNewSession(TSession *newTextEditor); //新建了一个textedit
    void sigSelected(TSession *newTextEditor); //焦点textedit改变了
private:
    void initVal();
    void initUI();
    QSplitter *creatSplitter(Qt::Orientation orientation,QWidget *parent);
    void creatTextEditor(QWidget *parent);
    void removeTextEditor(TSession *rmTextEditor);
    void removeSplitter(QSplitter *rmSplitter);
    void removeLastTextEditor();
    void removeLastSplitter();

public slots:
    void slotVSplitScreen(); //垂直分屏
    void slotHSplitScreen(); //水平分屏
    void slotMergeScreen();  //并且
    void slotFocusChange(QWidget *old, QWidget *now);

public:
    QList<TSession *> m_listTextEditor;
private:
    QList<QSplitter *> m_plistSplitter;
    TSession *m_pOldFocusTextEditor;
    TSession *m_pNowFocusTextEditor;

    QWidget *m_pGrandgrandfather;
    QSplitter *m_pParentSplitter;
    QSplitter *m_pGrandpaSplitter;
    TSession *m_pBrotherTextEditor;
    QSplitter *m_pUncleSplitter;
    QSplitter *m_pSplitterMain;
    TSession *m_pTextEditorMain;
    QHBoxLayout *m_pHLayout;

};


#endif // TSESSIONS_H
