#ifndef MUSICINFOWIDGET_H
#define MUSICINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMediaMetaData>

class MusicInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicInfoWidget(QWidget *parent = nullptr);
    void initMetaData();
public slots:
    void updateMetaData(int);
signals:

private:
    QLabel *musicNameLabel;
    QLabel *authorLabel;
    QLabel *coverLabel;

};

#endif // MUSICINFOWIDGET_H
