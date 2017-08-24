//
//  structs.h
//  operateData
//
//  Created by PowerAuras on 15-8-13.
//  Copyright (c) 2015年 PowerAuras. All rights reserved.
//

#ifndef operateData_structs_h
#define operateData_structs_h





#pragma pack (1)
struct MapNode
{
    short x;
    short y;
    bool newNode;
};
struct MapNodeX {
    unsigned short level;
    short x;
    short y;
//    char name[6];
    char *name;
    ~MapNodeX(){
        
        
    }
};
//*************************************************************************
//Cinrad 地图结构
struct CINRADMAPMSGHEAD //新一代天气雷达地图信息头
{
    unsigned short flag1; //标志位1
    unsigned short flag2; //标志位2
    short x1;    //起始点x
    short y1;    //起始点y
    unsigned short bytes; //字节数
};

struct CINRADMAPTOWNNAME //新一代天气雷达地图信息头
{
    unsigned short flag1; //标志位1
    unsigned short flag2; //标志位2
    unsigned short flag3; //标志位3
    short x1;    //起始点x
    short y1;    //起始点y
    unsigned short bytes; //字节数
    char name[6];
};

struct MapHead
{
    unsigned short mapID;  //地图的类别ID
    unsigned short flag1;  //标志位1 (00或01)
    unsigned short flag2;  //标志位2 (01或17)
    unsigned int length; //长度字节
    unsigned short startpos; //开始的文件偏移量
    char unused[202];
};


//信息头块
struct BLOCKHEADMSG
{
    unsigned short productCode;
    unsigned short productDate;
    unsigned int productTime;
    unsigned int fileLength;
    unsigned short radarCode;
    unsigned short receiveCode;
    unsigned short blockCount;
};
//产品描述块
struct BLOCKDESCRIPTION {
    short blockSepSymbol;
    unsigned int latitude;//除以1000后为雷达站纬度，精确到0.001
    unsigned int longitude;
    unsigned short altitude;//雷达站海拔高度，单位为英尺(1 = 0.3048m)
    unsigned short productCode;//产品代号，和信息头块的相同
    unsigned short operationMode;//操作模式， 0维护模式，1晴空模式，2降雨模式
    unsigned short vscanMode;//体扫模式，如11、21、31
    unsigned short productSN;//请求RPG生成产品的序列号
    unsigned short vscanCode;//提扫号
    unsigned short vscanDate;
    unsigned int vscanTime;
    unsigned short createDate;
    unsigned int createTime;
    unsigned short dependence1;
    unsigned short dependence2;
    unsigned short elevationCode;
    unsigned short dependence3;
    unsigned short threshold1;
    unsigned short threshold2;
    unsigned short threshold3;
    unsigned short threshold4;
    unsigned short threshold5;
    unsigned short threshold6;
    unsigned short threshold7;
    unsigned short threshold8;
    unsigned short threshold9;
    unsigned short threshold10;
    unsigned short threshold11;
    unsigned short threshold12;
    unsigned short threshold13;
    unsigned short threshold14;
    unsigned short threshold15;
    unsigned short threshold16;
    unsigned short dependence4;
    unsigned short dependence5;
    unsigned short dependence6;
    unsigned short dependence7;
    unsigned short dependence8;
    unsigned short dependence9;
    unsigned short dependence10;
    unsigned short vision;
    unsigned int gapSymbology;
    unsigned int gapGraphic;
    unsigned int gapAlpanumeric;

};
//3.1 产品符号表示块
struct BLOCKLAYER;
struct BLOCKRADIAL;
struct BLOCKGRIDROW;
struct BLOCKLITTLEDATA;
struct BLOCKRADIALSTRIP;
//径向小块 同栅格小块
struct BLOCKLITTLEDATA
{
    unsigned char data;
};

//3.1121栅格行
struct BLOCKGRIDROW
{
    unsigned short byteCount;//行字节数32
    BLOCKLITTLEDATA *blockLittleDataAry;//32个栅格小块
    ~BLOCKGRIDROW(){
        delete [] blockLittleDataAry;
    }
};

struct BLOCKSYMBOL
{
    short blocksepSymbol;
    unsigned short blockCode;
    unsigned int blockLength;
    unsigned short layerCount;
};
//3.11 层
struct BLOCKLAYER
{
    short layersepSymbol;
    unsigned int layerLength;
};
//3.1111径向数据条
struct BLOCKRADIALSTRIP
{
    unsigned short byteCount;
    unsigned short angleStart;
    unsigned short angleDelta;
    BLOCKLITTLEDATA *blockLittleDataAry;//32个栅格小块
    ~BLOCKRADIALSTRIP(){
        delete []blockLittleDataAry;
    }
};

//3.111径向数据包
struct BLOCKRADIAL
{
    unsigned short packetCode;//0xAF1F
    unsigned short firstBin;
    unsigned short binCount;
    unsigned short xCenter;
    unsigned short yCenter;
    unsigned short scaleFactor;
    unsigned short radialCount;
    BLOCKRADIALSTRIP *radialStripAry;
    ~BLOCKRADIAL(){
        delete []radialStripAry;
    }
};


//3.112栅格数据包
struct BLOCKGRID
{
    unsigned short packetCode1;//0xBA0F/0xBA07
    unsigned short packetCode2;//0x8000
    unsigned short packetCode3;//0x00C0
    unsigned short xStart;
    unsigned short yStart;
    unsigned short xScale;
    unsigned short reserve1;
    unsigned short yScale;
    unsigned short reserve2;
    unsigned short rowCount;//有多少个 栅格行
    unsigned short packetFormat;
    BLOCKGRIDROW *blockGridRowAry;//464行
    ~BLOCKGRID(){
        delete []blockGridRowAry;
    }
};
#pragma pack ()
#endif