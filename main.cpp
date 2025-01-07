#include "mainwidget.h"
#include "musiclist.h"
#include "musicmetadata.h"
#include "settings.h"

#include <QApplication>
#include <QScreen>

MainWidget* pmainWidget;
MusicList* musiclist;
Settings* settings;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    musiclist=new MusicList;
    musiclist->loadFile();//加载播放列表

    settings=new Settings;
    settings->loadFile();//初始化设置

    QFont font("");
    a.setFont(font);
    MainWidget w;
    pmainWidget=&w;
    QScreen *screen =QGuiApplication::screens().at(0);
    w.resize(screen->geometry().width()*3/4,screen->geometry().height()*3/4);
    w.show();

    return a.exec();
}
