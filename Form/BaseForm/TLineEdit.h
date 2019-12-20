#ifndef TLINEEDIT_H
#define TLINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class TLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit TLineEdit(QWidget *parent = 0);
};

#endif // TLINEEDIT_H
