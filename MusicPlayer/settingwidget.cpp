#include "settingwidget.h"
#include <QGridLayout>
#include <QVBoxLayout>

extern Settings* settings;//全局设置

SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("color: rgb(0,10,10)");

    //音量设置
    VolumeLabel= new QLabel(tr("音量"));
    VolumeSlider=new QSlider;
    VolumeSlider->setMinimum(0);
    VolumeSlider->setMaximum(100);
    VolumeSlider->setMaximumSize(20,200);
    VolumeSlider->setValue(settings->volume);
    connect(VolumeSlider,SIGNAL(valueChanged(int)),this,SLOT(slotVolumeSlider(int)));

    QVBoxLayout *volumeLayout=new QVBoxLayout;
    volumeLayout->addWidget(VolumeSlider);
    volumeLayout->addWidget(VolumeLabel);

    //是否自动播放下一首
    AutoNextLabel =new QLabel(tr("自动播放下一首"));
    AutoNextCheckBox =new QCheckBox;
    AutoNextCheckBox->setCheckState((Qt::CheckState)settings->autoNext);
    connect(AutoNextCheckBox,SIGNAL(stateChanged(int)),this,SLOT(slotAutoNextCheckBox(int)));

    QHBoxLayout *autoNextLayout=new QHBoxLayout;
    autoNextLayout->addWidget(AutoNextLabel);
    autoNextLayout->addWidget(AutoNextCheckBox);

    //一些信息
    InfoLabel=new QLabel(tr("软件名称：音乐播放器\n"
                            "\n"
                            "作者：何少泉\n"
                            "\n"
                            "\n"
                            "\n"
                            "简介：该软件是一个简单的音乐播放器，运用qt5制作而成，\n"
                            "支持mp3和flac格式文件\n"
                            "\n"
                            "源代码地址：https://github.com/bks34/MusicPlayer\n"
                            "\n"));
    InfoLabel->setStyleSheet("background-color: rgba(230,210,200,150);"
                             "color: rgb(0,10,10)");

    QGridLayout* mainLayout=new QGridLayout(this);
    mainLayout->addLayout(volumeLayout,1,1);
    mainLayout->addLayout(autoNextLayout,1,2);
    mainLayout->addWidget(InfoLabel,2,1,2,2);
    mainLayout->setRowStretch(1,1);
    mainLayout->setRowStretch(2,5);
    mainLayout->setColumnStretch(1,5);
    mainLayout->setColumnStretch(2,1);
}

void SettingWidget::slotVolumeSlider(int v)
{
    settings->volume=v;
    changeVolume();
}

void SettingWidget::slotAutoNextCheckBox(int state)
{
    settings->autoNext=(state>0)? true : false;
}
