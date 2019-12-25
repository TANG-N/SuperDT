#ifndef TUSERCARDITEM_H
#define TUSERCARDITEM_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class TUserCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TUserCardItem(QWidget *parent = 0);

    void initUI();
    void refreshStyle();
    void paintEvent(QPaintEvent *event);
public:

private:
    QString m_strAppPath;
    QString m_strImgPath;
    QString m_strIconPath;
    QString m_strUserName;
    int m_nDebugCount;

    QLabel *m_pLabelUserImg;
    QLabel *m_pLabelUserIcon;
    QLabel *m_pLabelUserName;
    QLabel *m_PLabelUserMsg;
};

#endif // TUSERCARDITEM_H
