#ifndef TCARDTITLE_H
#define TCARDTITLE_H

#include <QWidget>
#include <QLabel>

class TCardTitle : public QWidget
{
    Q_OBJECT
public:
    explicit TCardTitle(QString strIconUrl = "",QString strText = "标题名称",QWidget *parent = 0);

    void setIcon(QString strIcon){m_strIconUrl = strIcon;refreshStyle();}
    void setText(QString strText){m_strText = strText;refreshStyle();}
    void setTextColor(QString strTextColor){m_strTextColor = strTextColor;refreshStyle();}
private:
    void init();
    void refreshStyle();
private:
    QString m_strIconUrl;
    QString m_strText;
    QString m_strTextColor;

    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
};

#endif // TCARDTITLE_H
