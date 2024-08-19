#ifndef MUSICMETADATA_H
#define MUSICMETADATA_H

#include <QObject>
#include <QImage>
using std::string;
using std::vector;

class MusicMetaData
{
public:
    MusicMetaData();
    void GetFromMp3(string filePath);//从MP3文件读取信息

    //mp3文件的标签
    struct ID3V2
    {
        //标签头
        struct TagHead
        {
            char Header[3];//为"ID3"
            char Ver;//ID3v2.3就记录为二进制的3
            char Revision; //副版本号
            char Flag; //标志字节
            char Size[4]; //标签大小，包括标签头的10 个字节和所有的标签帧的大小，
                          //计算公式(Size[0]&0x7F)*0x200000+ (Size[1]&0x7F)*0x400 + (Size[2]&0x7F)*0x80 +(Size[3]&0x7F)
        };
        TagHead tagHead;

        //标签帧
        struct TagFrame
        {
            //标签帧头
            char ID[4];//用四个字符标识一个帧，说明其内容，如TIT2=标题，TPE1=作者
            char Size[4];//帧内容的大小，不包括帧头
                         //计算公式Size[0]*0x100000000 + Size[1]*0x10000+ Size[2]*0x100 + Size[3]
            char Flags[2];//存放标志，只定义了6 位

            //帧中的数据
            char *frameData;
            int frameDataSize;
        };
        vector<TagFrame> tagFrames;
    };

    //也是mp3文件的标签，一般位于文件末尾128个字节
    struct ID3V1
    {
        char Header[3];         /*标签头必须是"TAG"否则认为没有标签*/
        char Title[30];          /*标题*/
        char Artist[30];          /*作者*/
        char Album[30];        /*专集*/
        char Year[4];            /*出品年代*/
        char Comment[28];       /*备注*/
        char reserve;             /*保留*/
        char track;              /*音轨*/
        char Genre;              /*类型*/
    };

    struct Mp3Info //MP3文件的信息
    {
        ID3V2 *pID3V2=NULL;
        ID3V1 *pID3V1=NULL;
    };

    Mp3Info mp3Info;

    //将在页面显示的信息
    QString title;//标题
    QString artist;//作者
    QImage cover;//封面

private:
    void ReadMp3File(string filePath);//读取MP3文件
    void FreeMp3Data();//在获得需要的信息后free掉Mp3Info
};

#endif // MUSICMETADATA_H
