#ifndef TCARDTITLE_H
#define TCARDTITLE_H

#include <QWidget>
#include <QLabel>

class TCardTitle : public QWidget
{
    Q_OBJECT
public:
    explicit TCardTitle(QString strIcon = "",QString strText = "标题名称",QWidget *parent = 0);

    QLabel *m_pLabelIcon = nullptr;
    QLabel *m_pLabelText = nullptr;
private:
    void init();
private:
    QString m_strIcon;
    QString m_strText;

};

#endif // TCARDTITLE_H
