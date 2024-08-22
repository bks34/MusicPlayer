#include "playerwidget.h"
#include <QHBoxLayout>
#include "musiclist.h"
#include "settings.h"

extern MusicList* musiclist;
extern Settings* settings;
int musicIndex;



PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    player=new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->setVolume(50);

    playSlider =new QSlider(Qt::Horizontal);
    playSlider->setMinimum(0);
    playSlider->setMaximum(1000);

    playBtn =new QPushButton(tr("Play"));
    nextBtn =new QPushButton(tr(">"));
    lastBtn =new QPushButton(tr("<"));

    QHBoxLayout *Toplayout =new QHBoxLayout;
    Toplayout->addStretch();
    Toplayout->addWidget(playSlider);
    Toplayout->addStretch();

    QHBoxLayout *Bottomlayout =new QHBoxLayout;
    Bottomlayout->addStretch();
    Bottomlayout->addWidget(lastBtn);
    Bottomlayout->addWidget(playBtn);
    Bottomlayout->addWidget(nextBtn);
    Bottomlayout->addStretch();

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(Toplayout);
    mainLayout->addLayout(Bottomlayout);

    connect(playBtn,SIGNAL(clicked()),this,SLOT(slotPlayBtn()));
    connect(nextBtn,SIGNAL(clicked()),this,SLOT(slotNextBtn()));
    connect(lastBtn,SIGNAL(clicked()),this,SLOT(slotLastBtn()));

    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updateSliderPosition(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(updateSliderRange(qint64)));
    connect(playSlider,SIGNAL(sliderMoved(int)),this,SLOT(setPlayerPosition(int))); //滑动进度条后同时改变音乐播放位置
}

void PlayerWidget::slotPlayBtn()
{
    if(!isplaying)
    {
        if(!(filePath.isEmpty()))
        {
            player->play();
            isplaying = true;
            playBtn->setText("pause");
        }
    }
    else
    {
        player->pause();
        isplaying=false;
        playBtn->setText("play");
    }

}

void PlayerWidget::slotPlay(int index)
{
    musicIndex =index-1;
    filePath = musiclist->list.at(musicIndex).filePath;
    qDebug()<<filePath;
    player->stop();
    isplaying=false;
    playBtn->setText("play");
    player->setMedia(QUrl::fromLocalFile(filePath));
    playBtn->clicked();
    changeMusic(index);
}

void PlayerWidget::slotNextBtn()
{
    int index=musicIndex;
    if((unsigned long long)index==musiclist->list.size()-1)
        slotPlay(1);
    else
        slotPlay(index+2);
}

void PlayerWidget::slotLastBtn()
{
    int index=musicIndex;
    if((unsigned long long)index==0)
        slotPlay(musiclist->list.size());
    else
        slotPlay(index);
}

void PlayerWidget::updateSliderPosition(qint64 pos)
{
    playSlider->setValue(static_cast<int>(pos));
    if(pos>0 && pos==player->duration() && settings->autoNext)
    {
        qDebug()<<"pos: "<<pos;
        slotNextBtn();
    }
}

void PlayerWidget::updateSliderRange(qint64 duration)
{
    playSlider->setMaximum(static_cast<int>(duration));
}

void PlayerWidget::setPlayerPosition(int value)
{
    qint64 postion =static_cast<qint64>(value);
    player->setPosition(postion);
}

void PlayerWidget::slotChangeVolume()
{
    player->setVolume(settings->volume);
}

