#include "musicinfowidget.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <musiclist.h>
#include "musicmetadata.h"

#include <QMediaMetaData>

extern MusicList* musiclist;
extern int musicIndex;

MusicInfoWidget::MusicInfoWidget(QWidget *parent) : QWidget(parent)
{
    musicNameLabel=new QLabel;
    authorLabel=new QLabel;
    coverLabel=new QLabel;

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(coverLabel);
    layout->setStretchFactor(coverLabel,6);
    layout->addWidget(musicNameLabel);
    layout->setStretchFactor(musicNameLabel,3);
    layout->addWidget(authorLabel);
    layout->setStretchFactor(authorLabel,1);

    initMetaData();
}

void MusicInfoWidget::initMetaData()
{
    musicNameLabel->setText(tr("名字：暂无"));
    authorLabel->setText(tr("作者：暂无"));
    QPixmap coverPixmap=QPixmap::fromImage(QImage(":/image/record.png"));
    coverLabel->setPixmap(coverPixmap);
}

void MusicInfoWidget::updateMetaData(int)
{
    initMetaData();

    QString filePath=musiclist->list.at(musicIndex).filePath;
    MusicMetaData metaData=musiclist->list.at(musicIndex).metaData;//获得文件元信息
    QString fileType=filePath.mid(filePath.size()-4,4);
    if(fileType==tr(".mp3"))
    {
        if(!metaData.title.isEmpty())
            musicNameLabel->setText(tr("名字：")+metaData.title);
        if(!metaData.artist.isEmpty())
            authorLabel->setText(tr("作者：")+metaData.artist);
        if(!metaData.cover.isNull())
        {
            QImage img= metaData.cover.scaled(580,581);
            coverLabel->setPixmap(QPixmap::fromImage(img));
        }
    }
    else if(fileType==tr("flac"))
    {
        if(!metaData.title.isEmpty())
            musicNameLabel->setText(tr("名字：")+metaData.title);
        if(!metaData.artist.isEmpty())
            authorLabel->setText(tr("作者：")+metaData.artist);
        if(!metaData.cover.isNull())
        {
            QImage img= metaData.cover.scaled(580,581);
            coverLabel->setPixmap(QPixmap::fromImage(img));
        }
    }

}
