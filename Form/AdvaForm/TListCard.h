#ifndef TLISTCARD_H
#define TLISTCARD_H

#include <QListWidget>

class TListCard : public QListWidget
{
    Q_OBJECT
public:
    explicit TListCard(QWidget *parent = nullptr);

    QListWidgetItem *addWidget(QWidget *pWidget);
    QListWidgetItem *insertWidget(int row,QWidget *pWidget);
    void removeItem(QListWidgetItem *pItem);
private:
    void init();

private:
    int m_nHeight = 0;
    int m_nWidth = 0;
};

#endif // TLISTCARD_H
