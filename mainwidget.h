#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include "playerwidget.h"
#include "topwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        //设置圆角矩形半径
        int r=20;
        p.setPen(Qt::transparent);
        p.setBrush(QBrush(QColor(200,200,200,200)));
        p.drawRoundedRect(rect(),r,r);

        QWidget::paintEvent(event);
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        if(event->y()<30)//只在窗口顶部30个像素允许拖动
        {
            isPressed = true;
            dragPoint=event->globalPos()-this->geometry().topLeft();
        }
        QWidget::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        isPressed = false;
        QWidget::mouseReleaseEvent(event);
    }

     void mouseMoveEvent(QMouseEvent *event) override
     {
        if(isPressed)
        {
            move(event->globalPos()-dragPoint);
        }
        QWidget::mouseMoveEvent(event);
     }

signals:
private:
    PlayerWidget* playerWidget;
    TopWidget* topWidget;

    bool isPressed =false;
    QPoint dragPoint;
};

#endif // MAINWIDGET_H
