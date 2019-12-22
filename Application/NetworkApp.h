#ifndef NETWORKAPP_H
#define NETWORKAPP_H

#include <QWidget>
#include <QScrollArea>
#include <QTextEdit>

class NetworkApp : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkApp(QWidget *parent = 0);

    void initUI();
private:
    QScrollArea *m_pScrollArea;
    QTextEdit *m_pTextEdit;
};

#endif // NETWORKAPP_H
