#ifndef TTREECARD_H
#define TTREECARD_H

#include <QTreeWidget>

class TTreeCard : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TTreeCard(QWidget *parent = nullptr);

    void addWidget(QWidget *pWidget);

private:
    void init();
};

#endif // TTREECARD_H
