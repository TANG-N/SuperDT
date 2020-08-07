#ifndef TSETTINGAREA_H
#define TSETTINGAREA_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "TSettingBtnBar.h"
#include "TMsgArea.h"
#include "NetworkApp.h"

class TSettingArea : public QWidget
{
    Q_OBJECT
public:
    explicit TSettingArea(QWidget *parent = 0);


signals:
    void signalVSplitScreen();
    void signalHSplitScreen();
    void signalMergeScreen();
public slots:
   // void slotButtonMain();
private:
    void initVal();
    void initUI();

private:
    QString m_strAppPath;
    QString getImageStytle(QString strImage);
    TMsgArea *m_pMsgArea = nullptr;
    QScrollArea *m_pSarea;
    QWidget *m_pWidgetSettingArea;
    QWidget *m_pWidgetUserArea;
    QWidget *m_pWidgetMain;
    QSize m_sIconSize;
    int m_nWidgetMainWidth;
    int m_nButtonMainWidth;
    QHBoxLayout *m_pHLayout;
    NetworkApp *m_pNavigationBar = nullptr;  //导航栏
};

#endif // TSETTINGAREA_H
