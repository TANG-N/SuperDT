#ifndef TPushButton_H
#define TPushButton_H

#include <QPushButton>

class TPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TPushButton(QWidget *parent = 0,bool status = true);

    bool getStatus(){return m_bStatus;}
signals:
    void signalChanged(bool status);

public slots:
    void slotClicked();
private:
    void updateUI();
    void initUI();
    QString getImageStytle(QString strImage);
private:
    bool m_bStatus;
    QString m_strAppPath;
};

#endif // TPushButton_H
