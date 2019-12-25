#ifndef TCOMBOX_H
#define TCOMBOX_H

#include <QWidget>
#include <QComboBox>

class TComBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TComBox(QWidget *parent = 0);

private:
    QString m_strAppPath;
    void initUI();
};

#endif // TCOMBOX_H
