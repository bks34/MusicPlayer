#include "rightwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "mainwidget.h"
#include "musiclist.h"
#include "settings.h"
extern MainWidget* pmainWidget;
extern MusicList* musiclist;
extern Settings* settings;

RightWidget::RightWidget(QWidget *parent) : QWidget(parent)
{
    exitBtn =new QPushButton("exit");
    connect(exitBtn,SIGNAL(clicked()),this,SLOT(slotExit()));

    minBtn =new QPushButton("min");
    connect(minBtn,SIGNAL(clicked()),this,SLOT(slotMin()));

    QHBoxLayout *topLayout= new QHBoxLayout;
    topLayout->addStretch();
    topLayout->addWidget(minBtn);
    topLayout->addWidget(exitBtn);//右上角的退出最小化按钮

    stackedWidget = new QStackedWidget;
    playlistWidget = new QListWidget;
    musicInfoWidget = new MusicInfoWidget;
    settingWidget =new SettingWidget;

    connect(this,SIGNAL(changeMusic(int)),musicInfoWidget,SLOT(updateMetaData(int)));


    initMyFavoriteMusicWidget();


    stackedWidget->addWidget(playlistWidget);
    stackedWidget->addWidget(musicInfoWidget);
    stackedWidget->addWidget(settingWidget);

    QVBoxLayout *mainLayout =new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(stackedWidget);
}

void RightWidget::addMyFavorMusicWidge(QString filePath)
{
    QListWidgetItem *item=new QListWidgetItem(filePath);
    QFont font=item->font();
    font.setPointSize(20);
    item->setFont(font);
    playlistWidget->addItem(item);
}

void RightWidget::slotExit()
{
    musiclist->storeFile();
    settings->storeFile();
    exit(0);
}

void RightWidget::slotMin()
{
    pmainWidget->showMinimized();
}

void RightWidget::slotchangeWidget(int index)
{
    stackedWidget->setCurrentIndex(index);
}

void RightWidget::slotClickMyFavorMusicWidgetItem(QListWidgetItem *item)
{
    int index=playlistWidget->row(item);
    if(index==0)
    {
        QString s;
        MusicList::Music m;
        s= QFileDialog::getOpenFileName(pmainWidget,tr("请选择要添加的音乐"),tr("."),"*.mp3;*.flac");

        bool exist=false;
        for(auto it=musiclist->list.begin();it!=musiclist->list.end();it++)
        {
            if(s==it->filePath)
            {
                exist=true;
                break;
            }
        }
        if((!s.isEmpty())&&(!exist))
        {
            m.filePath=s;
            if(m.filePath.mid(m.filePath.size()-3,3)=="mp3")
            {
                m.metaData.GetFromMp3(m.filePath.toStdString());
            }
            musiclist->list.push_back(m);
            addMyFavorMusicWidge(m.filePath);
        }
    }
    else
    {
        changeMusic(index);
    }
}

void RightWidget::slotChangemusicInfoWidget(int index)
{
    musicInfoWidget->updateMetaData(index);
}

void RightWidget::initMyFavoriteMusicWidget()
{
    playlistWidget->setStyleSheet("background-color: rgba(230,210,200,150);"
                                         "color: rgb(0,10,10)");
    //设置颜色

    QListWidgetItem *firstItem=new QListWidgetItem(tr("添加音乐"));
    firstItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QFont font=firstItem->font();
    font.setPointSize(30);
    firstItem->setFont(font);//设置第一个item的字体

    playlistWidget->addItem(firstItem);
    for(auto it=musiclist->list.begin();it!=musiclist->list.end();it++)
    {
        QListWidgetItem *item=new QListWidgetItem(it->filePath);
        QFont font=item->font();
        font.setPointSize(20);
        item->setFont(font);
        playlistWidget->addItem(item);
    }

    connect(playlistWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(slotClickMyFavorMusicWidgetItem(QListWidgetItem*)));
}

