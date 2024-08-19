#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <vector>
#include <QObject>
#include <QImage>
#include "musicmetadata.h"

using std::vector;

class MusicList
{
public:
    MusicList();

    struct Music{
        QString filePath;
        MusicMetaData metaData;
    };

    void loadFile();
    void storeFile();


    vector<Music> list;
};

#endif // MUSICLIST_H
