#ifndef TCENTERWIDGET_H
#define TCENTERWIDGET_H

#include <QWidget>
#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include "TSettingArea.h"

class TCenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TCenterWidget(QWidget *parent = 0);

    void init();

private:
    StatusBar *m_pStatusBar;


    TMsgArea *m_pMsgArea;
    QScrollArea *m_pSarea;
    NetworkApp *m_pNavigationBar = nullptr;
};

#endif // TCENTERWIDGET_H
