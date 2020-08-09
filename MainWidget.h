#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSizeGrip>
#include <QDialog>
#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include "TSettingArea.h"

class MainWidget : public QDialog
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
public:
    void setBgImage(QString strUrl);

private:
    void initUI();
    QWidget *createMainWidget();
private:
    QString m_strAppPath;
    QWidget *m_pWidgetBg = nullptr;
    TitleBar *m_pTitleBar;
    StatusBar *m_pStatusBar;
    TMsgArea *m_pMsgArea;
    TSettingArea *m_pSettingArea;
};

#endif // MAINWIDGET_H
