﻿#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSizeGrip>

#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include "TSettingArea.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initUI();

private:
    QString m_strAppPath;
    TitleBar *m_pTitleBar;
    StatusBar *m_pStatusBar;
    TMsgArea *m_pMsgArea;
    TSettingArea *m_pSettingArea;
};

#endif // MAINWIDGET_H
