#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QListWidget>

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);
public slots:
    void slotItemChange(QListWidgetItem*);
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);
        p.setPen(Qt::transparent);
        p.setBrush(QBrush(QColor(180,160,160,230)));
        int r=20;
        p.drawRoundedRect(rect(),r,r);
        QWidget::paintEvent(event);
    }
signals:
    void changeItem(int index);
private:
    QLabel *appTitleLabel;
    QListWidget *optionListWidget;
};

#endif // LEFTWIDGET_H
