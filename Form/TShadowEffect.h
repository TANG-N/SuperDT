#ifndef TSHADOWEFFECT_H
#define TSHADOWEFFECT_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsBlurEffect>

class TShadowEffect : public QWidget
{
    Q_OBJECT
 public:
     explicit TShadowEffect(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();

private:
    QGraphicsBlurEffect *m_pBlur = nullptr;

};

#endif // TSHADOWEFFECT_H
