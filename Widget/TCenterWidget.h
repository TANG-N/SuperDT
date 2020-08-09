#ifndef TCENTERWIDGET_H
#define TCENTERWIDGET_H

#include <QWidget>
#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include "TSettingArea.h"
#include <QStackedWidget>

class TCenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TCenterWidget(QWidget *parent = 0);

    void init();

private slots:
    void slotNewTextEditor(TTextEditor *pTextEditor);
    void slotSelectedTextEditor(TTextEditor *pTextEditor);
private:
    StatusBar *m_pStatusBar;


    TMsgArea *m_pMsgArea;
    QScrollArea *m_pSarea;
    NetworkApp *m_pNavigationBar = nullptr;
    QMap<TTextEditor *,NetworkApp *> m_mapTextEdit_App;
    QStackedWidget *m_pStackWidget = nullptr;
};

#endif // TCENTERWIDGET_H
