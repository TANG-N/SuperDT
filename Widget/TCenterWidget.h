#ifndef TCENTERWIDGET_H
#define TCENTERWIDGET_H

#include <QWidget>
#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include <QStackedWidget>
#include <QScrollArea>
#include "NetworkApp.h"
#include "TSettingBtnBar.h"
#include <QMap>
#include "TSessions.h"

class TCenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TCenterWidget(QWidget *parent = 0);

    void init();

private slots:
    void slotNewTextEditor(TSession *pTextEditor);
    void slotSelectedTextEditor(TSession *pTextEditor);
private:
    StatusBar *m_pStatusBar;


    TSessions *m_pMsgArea;
    QScrollArea *m_pSarea;
    NetworkApp *m_pNavigationBar = nullptr;
    QMap<TSession *,NetworkApp *> m_mapTextEdit_App;
    QStackedWidget *m_pStackWidget = nullptr;
};

#endif // TCENTERWIDGET_H
