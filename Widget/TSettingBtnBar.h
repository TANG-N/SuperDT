#ifndef TSETTINGBTNBAR_H
#define TSETTINGBTNBAR_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QStringList>
#include <QPainter>

class TSettingBtnBar:public QWidget
{
    Q_OBJECT
public:
    explicit TSettingBtnBar(QWidget *parent = 0);
private:
    void init();
    void createView();
    void paintEvent(QPaintEvent *event);
signals:
    void sigSettingBtn(QString strId);
    void sigCloset(bool bIsOpen); //设置页面开关
private slots:
    void slotBtnClicked(QString strId);
private:
    QString m_strAppPath;
    QVector<QPushButton *> m_vecBtn;
    QSize m_sIconSize;
    QString m_strImgUrl;
};

#endif // TSETTINGBTNBAR_H
