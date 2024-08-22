#include "musiclist.h"

#include <fstream>
using std::fstream;
using std::string;

MusicList::MusicList()
{

}

void MusicList::loadFile()
{
    fstream f;
    f.open("musiclist",std::ios::in);
    if(!f.is_open())
    {
        qDebug("musiclist open error");
        return;
    }
    Music temp;
    string s;
    while(!f.eof())
    {
        std::getline(f,s);
        if(s=="")
            continue;
        temp.filePath=QString::fromStdString(s);
        if(temp.filePath.mid(temp.filePath.size()-3,3)=="mp3")//若是mp3文件
        {
            temp.metaData.GetFromMp3(temp.filePath.toStdString());
        }
        else if(temp.filePath.mid(temp.filePath.size()-4,4)=="flac")//若是flac文件
        {
            temp.metaData.GetFromFlac(temp.filePath.toStdString());
        }
        list.push_back(temp);
    }
    f.close();
}

void MusicList::storeFile()
{
    fstream f;
    f.open("musiclist",std::ios::out);
    if(!f.is_open())
    {
        qDebug("musiclist open error");
        return;
    }
    for(auto it=list.begin();it!=list.end();it++)
    {
        f<<it->filePath.toStdString();
        if((it+1)!=list.end())
            f<<'\n';
    }
    f.close();
}
