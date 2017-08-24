//
//  structs.h
//  operateData
//
//  Created by PowerAuras on 15-8-13.
//  Copyright (c) 2015�� PowerAuras. All rights reserved.
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
//Cinrad ��ͼ�ṹ
struct CINRADMAPMSGHEAD //��һ�������״��ͼ��Ϣͷ
{
    unsigned short flag1; //��־λ1
    unsigned short flag2; //��־λ2
    short x1;    //��ʼ��x
    short y1;    //��ʼ��y
    unsigned short bytes; //�ֽ���
};

struct CINRADMAPTOWNNAME //��һ�������״��ͼ��Ϣͷ
{
    unsigned short flag1; //��־λ1
    unsigned short flag2; //��־λ2
    unsigned short flag3; //��־λ3
    short x1;    //��ʼ��x
    short y1;    //��ʼ��y
    unsigned short bytes; //�ֽ���
    char name[6];
};

struct MapHead
{
    unsigned short mapID;  //��ͼ�����ID
    unsigned short flag1;  //��־λ1 (00��01)
    unsigned short flag2;  //��־λ2 (01��17)
    unsigned int length; //�����ֽ�
    unsigned short startpos; //��ʼ���ļ�ƫ����
    char unused[202];
};


//��Ϣͷ��
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
//��Ʒ������
struct BLOCKDESCRIPTION {
    short blockSepSymbol;
    unsigned int latitude;//����1000��Ϊ�״�վγ�ȣ���ȷ��0.001
    unsigned int longitude;
    unsigned short altitude;//�״�վ���θ߶ȣ���λΪӢ��(1 = 0.3048m)
    unsigned short productCode;//��Ʒ���ţ�����Ϣͷ�����ͬ
    unsigned short operationMode;//����ģʽ�� 0ά��ģʽ��1���ģʽ��2����ģʽ
    unsigned short vscanMode;//��ɨģʽ����11��21��31
    unsigned short productSN;//����RPG���ɲ�Ʒ�����к�
    unsigned short vscanCode;//��ɨ��
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
//3.1 ��Ʒ���ű�ʾ��
struct BLOCKLAYER;
struct BLOCKRADIAL;
struct BLOCKGRIDROW;
struct BLOCKLITTLEDATA;
struct BLOCKRADIALSTRIP;
//����С�� ͬդ��С��
struct BLOCKLITTLEDATA
{
    unsigned char data;
};

//3.1121դ����
struct BLOCKGRIDROW
{
    unsigned short byteCount;//���ֽ���32
    BLOCKLITTLEDATA *blockLittleDataAry;//32��դ��С��
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
//3.11 ��
struct BLOCKLAYER
{
    short layersepSymbol;
    unsigned int layerLength;
};
//3.1111����������
struct BLOCKRADIALSTRIP
{
    unsigned short byteCount;
    unsigned short angleStart;
    unsigned short angleDelta;
    BLOCKLITTLEDATA *blockLittleDataAry;//32��դ��С��
    ~BLOCKRADIALSTRIP(){
        delete []blockLittleDataAry;
    }
};

//3.111�������ݰ�
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


//3.112դ�����ݰ�
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
    unsigned short rowCount;//�ж��ٸ� դ����
    unsigned short packetFormat;
    BLOCKGRIDROW *blockGridRowAry;//464��
    ~BLOCKGRID(){
        delete []blockGridRowAry;
    }
};
#pragma pack ()
#endif