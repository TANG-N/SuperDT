#ifndef TSESSION_H
#define TSESSION_H

#include "TTextEditor.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TSession : public QWidget
{
    Q_OBJECT
public:
    explicit TSession(QWidget *parent = 0);

    void appendText(QString strText);
    void appendPlainText(QString strText);
private:
    void init();
public slots:
    void slotsStateChanged(QString strIp,int nPort,bool bState);

private:
    /*顶条*/
    QWidget *m_pWidgetTopBar = nullptr;
    QLabel *m_pLabelIpPort = nullptr;
    QLabel *m_pLabelState = nullptr;
    QPushButton *m_pBtnClear = nullptr;
    //
    TTextEditor *m_pTextEditor = nullptr;
};

#endif // TSESSION_H
