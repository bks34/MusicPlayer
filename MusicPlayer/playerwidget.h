#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QPainter>
#include <QPushButton>

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = nullptr);

public slots:
    void slotPlayBtn();
    void slotPlay(int);

    void slotNextBtn();
    void slotLastBtn();

    void updateSliderPosition(qint64);
    void updateSliderRange(qint64);
    void setPlayerPosition(int);
    void slotChangeVolume();
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(Qt::transparent);
        p.setBrush(QBrush(Qt::darkGray));
        int r=20;
        p.drawRoundedRect(rect(),r,r);
        QWidget::paintEvent(event);
    }

signals:
    void changeMusic(int);
private:
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *lastBtn;

    QMediaPlayer *player;
    QSlider *playSlider;
    QString filePath="D:\\CloudMusic\\麻枝准 - 渚.mp3";

    bool isplaying=false;

};

#endif // PLAYERWIDGET_H
