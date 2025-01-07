#include "musicmetadata.h"
#include <fstream>
#include <QDebug>
#include <QFile>

using std::fstream;

MusicMetaData::MusicMetaData()
{

}

void MusicMetaData::GetFromMp3(std::string filePath)
{
    ReadMp3File(filePath);
    if((mp3Info.pID3V1==NULL) || (mp3Info.pID3V2==NULL))
    {
        qDebug()<<"ReadMp3File error";
        return;
    }
    qDebug()<<"共有标签帧"<<mp3Info.pID3V2->tagFrames.size();
    //给需要的信息赋值
    title=QString::fromLatin1(mp3Info.pID3V1->Title,30);
    artist=QString::fromLatin1(mp3Info.pID3V1->Artist,30);


    for(auto it=mp3Info.pID3V2->tagFrames.begin();it!=mp3Info.pID3V2->tagFrames.end();++it)
    {
        qDebug()<<it->ID[0]<<it->ID[1]<<it->ID[2]<<it->ID[3];
        if((it->ID[0]=='A')&&(it->ID[1]=='P')&&(it->ID[2]=='I')&&(it->ID[3]=='C'))//得到封面图片
        {
            char *data=it->frameData;
            string tempfilename="temp";
            char type=*data;//看MIME是ANSIC还是unicode
            data++;
            int MIME_TYPE_SIZE;
            int imageBegin=1;
            if((int)type==0)
            {
                MIME_TYPE_SIZE=strlen(data);
                data+=MIME_TYPE_SIZE+1;
                imageBegin+=MIME_TYPE_SIZE+1;
            }
            else
            {
                while((*data!=0)||(*(data+1)!=0))
                    data++;
                MIME_TYPE_SIZE=(data-it->frameData-1)/2;
                data+=2;
                imageBegin+=(MIME_TYPE_SIZE+2);
            }
            if(*(data-2)=='g')//图片是jpeg或png
            {
                data+=2;
                imageBegin+=2;
            }
            else//图片是bmp
            {
                data+=5;
                imageBegin+=5;
            }
            qDebug()<<int(*data);
            fstream f;
            f.open(tempfilename,std::ios::out | std::ios::binary);
            if(!f.is_open()) qDebug()<<"temp file open error";
            qDebug()<<"framesize:"<<it->frameDataSize;
            f.write(data,it->frameDataSize-imageBegin+1);
            f.close();
            cover=QImage(QString::fromStdString(tempfilename));
            QFile::remove(QString::fromStdString("./"+tempfilename));

            qDebug()<<"get the image"<<cover.size().width()<<cover.size().height();
        }

        if((it->ID[0]=='T')&&(it->ID[1]=='I')&&(it->ID[2]=='T')&&(it->ID[3]=='2'))//获得标题
        {
            char *data=it->frameData;
            title=QString::fromUtf16((ushort*)(data+3),(it->frameDataSize-3)/2);
        }

        if((it->ID[0]=='T')&&(it->ID[1]=='P')&&(it->ID[2]=='E')&&(it->ID[3]=='1'))//获得作者
        {
            char *data=it->frameData;
            artist=QString::fromUtf16((ushort*)(data+3),(it->frameDataSize-3)/2);
        }

    }
    FreeMp3Data();
}

void MusicMetaData::GetFromFlac(std::string filePath)
{
    ReadFlacFile(filePath);
    qDebug()<<"the metadatablock size:"<<flacInfo.metaDataBlocks.size();
    for(auto it=flacInfo.metaDataBlocks.begin(); it!=flacInfo.metaDataBlocks.end(); ++it)
    {
        if((int)((it->blockHeader.BlockType)&0x7f) == 6)//图片
        {
            qDebug()<<"a picture block";
            string tempfilename="temp";
            char* read=it->data;
            int ToRead=it->dataSize;

            int pictureType;//图片类型
            pictureType=(unsigned char)read[0]*0x1000000+(unsigned char)read[1]*0x10000+(unsigned char)read[2]*0x100+(unsigned char)read[3];
            read+=4;
            ToRead-=4;

            qDebug()<<"pictureType:"<<pictureType;

            int MIME_size=(unsigned char)read[0]*0x1000000+(unsigned char)read[1]*0x10000+(unsigned char)read[2]*0x100+(unsigned char)read[3];
            read+=4;
            ToRead-=4;

            read+=MIME_size;
            ToRead-=MIME_size;

            qDebug()<<"MIME_size:"<<MIME_size;

            int discribe_size=(unsigned char)read[0]*0x1000000+(unsigned char)read[1]*0x10000+(unsigned char)read[2]*0x100+(unsigned char)read[3];
            read+=4;
            ToRead-=4;

            read+=discribe_size;
            ToRead-=discribe_size;

            qDebug()<<"discribe_size"<<discribe_size;

            read+=16;
            ToRead-=16;

            int pictureSize=(unsigned char)read[0]*0x1000000+(unsigned char)read[1]*0x10000+(unsigned char)read[2]*0x100+(unsigned char)read[3];//图片大小
            read+=4;
            ToRead-=4;

            fstream f;
            f.open(tempfilename,std::ios::out | std::ios::binary);
            if(!f.is_open()) qDebug()<<"temp file open error";
            f.write(read,pictureSize);
            f.close();
            cover=QImage(QString::fromStdString(tempfilename));
            qDebug()<<"get the image"<<cover.size().width()<<cover.size().height();
        }

        if((int)(it->blockHeader.BlockType&0x7f) == 4)
        {
            qDebug()<<"a vorbis comment block";
            char* read=it->data;
            int ToRead=it->dataSize;
            string name(read,6);
            while((name!="TITLE=") && (ToRead>0))
            {
                read++;
                ToRead--;
                name=string(read,6);
            }
            qDebug()<<"ToRead:"<<ToRead;
            int titleSize=(unsigned char)read[-4]
                    +(unsigned char)read[-3]*0x100
                    +(unsigned char)read[-2]*0x10000
                    +(unsigned char)read[-1]*0x1000000-6;
            qDebug()<<"titleSize:"<<titleSize;
            read+=6;
            title=QString::fromUtf8(read,titleSize);//得到标题

            read=it->data;
            ToRead=it->dataSize;
            name=string(read,7);
            while((name!="ARTIST=") && (ToRead>0))
            {
                read++;
                ToRead--;
                name=string(read,7);
            }
            qDebug()<<"ToRead:"<<ToRead;
            int artistSize=(unsigned char)read[-4]
                    +(unsigned char)read[-3]*0x100
                    +(unsigned char)read[-2]*0x10000
                    +(unsigned char)read[-1]*0x1000000-7;
            qDebug()<<"artistSize:"<<artistSize;
            read+=7;
            artist=QString::fromUtf8(read,artistSize);//得到标题

        }
    }
    FreeFlacData();
}

void MusicMetaData::ReadMp3File(std::string filePath)
{
    QFile f(QString::fromStdString(filePath));

    if(!f.open(QIODevice::ReadOnly))
    {
        f.close();
        qDebug("GetMp3Info error,can't open %s %d",filePath.data(),(int)filePath.size());
        return;
    }
    ID3V2 *id3v2_temp=new ID3V2;
    ID3V2::TagFrame *tagframe;
    //读取标签头
    f.read(id3v2_temp->tagHead.Header,3);
    f.read(&(id3v2_temp->tagHead.Ver),1);
    f.read(&(id3v2_temp->tagHead.Revision),1);
    f.read(&(id3v2_temp->tagHead.Flag),1);
    f.read(id3v2_temp->tagHead.Size,4);

    int tagSize=(id3v2_temp->tagHead.Size[0]&0x7F)*0x200000+
            (id3v2_temp->tagHead.Size[1]&0x7F)*0x4000+
            (id3v2_temp->tagHead.Size[2]&0x7F)*0x80+
            (id3v2_temp->tagHead.Size[3]&0x7F);//ID3V2大小
    int i=tagSize-10;

    while(i>0)
    {
        tagframe=new ID3V2::TagFrame;
        f.read(tagframe->ID,4);
        f.read(tagframe->Size,4);
        f.read(tagframe->Flags,2);//标签帧头
        i-=10;
        if(tagframe->ID[0]==0)
        {
            delete tagframe;
            break;
        }
        int framedataSize =(unsigned char)tagframe->Size[0]*0x1000000
                +(unsigned char)tagframe->Size[1]*0x10000
                +(unsigned char)tagframe->Size[2]*0x100
                +(unsigned char)tagframe->Size[3];//这一帧的大小
        tagframe->frameData= new char[framedataSize];
        tagframe->frameDataSize=framedataSize;
        f.read(tagframe->frameData,framedataSize);
        id3v2_temp->tagFrames.push_back(*tagframe);//将得到的frame加入tagFrames
        delete tagframe;
        tagframe=NULL;
        i-=framedataSize;
    }
    mp3Info.pID3V2=id3v2_temp;//得到ID3V2

    ID3V1 *id3v1_temp =new ID3V1;

    f.seek(f.size()-128);

    f.read(id3v1_temp->Header,3);//读取ID3V1
    qDebug()<<id3v1_temp->Header;
    f.read(id3v1_temp->Title,30);
    f.read(id3v1_temp->Artist,30);
    f.read(id3v1_temp->Album,30);
    f.read(id3v1_temp->Year,4);
    f.read(id3v1_temp->Comment,28);
    f.read(&(id3v1_temp->reserve),1);
    f.read(&(id3v1_temp->track),1);
    f.read(&(id3v1_temp->Genre),1);
    f.close();

    mp3Info.pID3V1=id3v1_temp;//得到ID3V1
}

void MusicMetaData::FreeMp3Data()
{
    ID3V1 *id3v1= mp3Info.pID3V1;
    ID3V2 *id3v2= mp3Info.pID3V2;

    free(id3v1);
    for(auto it=id3v2->tagFrames.begin(); it!=id3v2->tagFrames.end();it++)
    {
        delete [] it->frameData;
    }
    free(id3v2);

    mp3Info.pID3V1=NULL;
    mp3Info.pID3V2=NULL;
}

void MusicMetaData::ReadFlacFile(std::string filePath)
{
    QFile f(QString::fromStdString(filePath));

    if(!f.open(QIODevice::ReadOnly))
    {
        f.close();
        qDebug("GetFromFlac error,can't open %s %d",filePath.data(),(int)filePath.size());
        return;
    }
    qDebug()<<"文件大小"<<f.size();
    char fLaCTag[4];//fLaC标志
    f.read(fLaCTag,4);

    MetaDataBlock *metaDataBlock_temp;
    bool isEnd=false;
    do
    {
        metaDataBlock_temp=new MetaDataBlock;

        f.read(&(metaDataBlock_temp->blockHeader.BlockType),1);
        f.read(metaDataBlock_temp->blockHeader.BlockSize,3);//读取block头

        isEnd=metaDataBlock_temp->blockHeader.BlockType<0;//判断是否是最后一个
        qDebug()<<"isEnd:"<<isEnd;
        qDebug()<<"blockType:"<<(metaDataBlock_temp->blockHeader.BlockType&0x7f);

        metaDataBlock_temp->dataSize=(unsigned char)(metaDataBlock_temp->blockHeader.BlockSize[0])*0x10000+
                (unsigned char)(metaDataBlock_temp->blockHeader.BlockSize[1])*0x100+
                (unsigned char)(metaDataBlock_temp->blockHeader.BlockSize[2]);
        qDebug()<<"dataSize:"<<metaDataBlock_temp->dataSize;

        metaDataBlock_temp->data=new char[metaDataBlock_temp->dataSize];
        f.read(metaDataBlock_temp->data,metaDataBlock_temp->dataSize);

        flacInfo.metaDataBlocks.push_back(*metaDataBlock_temp);//将读取到的metaDataBlock加到flacInfo
        delete metaDataBlock_temp;
        metaDataBlock_temp=NULL;
        qDebug()<<"read a metadata block\n";
    }
    while(!isEnd);
    qDebug()<<"end while";
    f.close();
}

void MusicMetaData::FreeFlacData()
{
    for(auto it=flacInfo.metaDataBlocks.begin(); it!=flacInfo.metaDataBlocks.end(); ++it)
    {
        delete [] it->data;
    }
    flacInfo.metaDataBlocks.clear();
    flacInfo.metaDataBlocks.shrink_to_fit();
}
