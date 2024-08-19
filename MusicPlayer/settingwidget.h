#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include "settings.h"

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);


public slots:
    void slotVolumeSlider(int);
    void slotAutoNextCheckBox(int);
signals:
    void changeVolume();

private:
    QLabel *VolumeLabel;
    QSlider *VolumeSlider;//调整音量

    QLabel *AutoNextLabel;
    QCheckBox *AutoNextCheckBox;//是否自动播放下一首

    QLabel *InfoLabel;
};

#endif // SETTINGWIDGET_H
