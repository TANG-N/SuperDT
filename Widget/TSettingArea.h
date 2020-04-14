#ifndef TSETTINGAREA_H
#define TSETTINGAREA_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

#include "TSettingBtnBar.h"
#include "TMsgArea.h"

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
    void slotButtonMain();
private:
    void initVal();
    void initUI();
    void initSettingArea();
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
    QPushButton *m_pButtonMain;
    QPushButton *m_pButtonUser;
    QPushButton *m_pButtonMenu;
    QPushButton *m_pButtonRecvSetting;
    QPushButton *m_pButtonCodec;
    QPushButton *m_pButtonSend;
    QPushButton *m_pButtonConnect;
};

#endif // TSETTINGAREA_H
