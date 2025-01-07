#ifndef MYFAVORITEMUSICWIDGET_H
#define MYFAVORITEMUSICWIDGET_H

#include <QListWidget>

class MyFavoriteMusicWidget : public QListWidget
{
    Q_OBJECT
public:
    MyFavoriteMusicWidget(QListWidget *parent = nullptr);
};

#endif // MYFAVORITEMUSICWIDGET_H
