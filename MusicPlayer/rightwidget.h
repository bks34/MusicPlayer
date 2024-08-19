#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include "musicinfowidget.h"
#include "settingwidget.h"

class RightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightWidget(QWidget *parent = nullptr);
    void addMyFavorMusicWidge(QString);
public slots:
    void slotExit();
    void slotMin();

    void slotchangeWidget(int);
    void slotClickMyFavorMusicWidgetItem(QListWidgetItem*);
    void slotChangemusicInfoWidget(int);
signals:
    void changeMusic(int);
private:
    QPushButton *exitBtn;
    QPushButton *minBtn;

public:
    QStackedWidget *stackedWidget;
    QListWidget *playlistWidget;
    MusicInfoWidget *musicInfoWidget;
    SettingWidget *settingWidget;

    void initMyFavoriteMusicWidget();
};

#endif // RIGHTWIDGET_H
