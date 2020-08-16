#ifndef TCARDTITLE_H
#define TCARDTITLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TCardTitle : public QWidget
{
    Q_OBJECT
public:
    explicit TCardTitle(QString strIcon = "",QString strText = "标题名称",QString strHelp = "这是个提示",QWidget *parent = 0);

    QLabel *m_pLabelIcon = nullptr;
    QLabel *m_pLabelText = nullptr;
    QLabel *m_pLabelHelp = nullptr;
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    void init();
private:
    QString m_strIcon;
    QString m_strText;
    QString m_strHelp;

};

#endif // TCARDTITLE_H
