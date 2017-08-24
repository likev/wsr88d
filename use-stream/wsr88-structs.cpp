// RecodeCompress.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "afxinet.h"
#include "shlwapi.h"

#include "structs.h"

#include <io.h>//struct fileInfo
#include <vector>

#define ZLIB_WINAPI
#include "zlib.h"
#include "zconf.h"
using namespace std;
CString NthInf(CString& strLine, int nIndex)
{
	CString strItem;
	strLine.TrimLeft();
	int nPosPre = 0,
		nPosCur = 0,
		nCount = 0;
	//����
	while(-1 != (nPosCur = strLine.Find('\\', nPosPre + 1)) )
	{

		if( nIndex == nCount)
		{
			strItem = strLine.Mid(nPosPre, nPosCur - nPosPre);
			return strItem;
		}
		nCount++;
		nPosPre = nPosCur;
		nPosPre++;

	}
	if(nIndex == nCount )
	{
		return strLine.Mid(nPosPre, strLine.GetLength() - nPosPre);
	}
	else
	{
		return "";
	}
}

bool recode(const char *_completeSourcePath,const char *_destinationPath){

	CString completeSourcePath;
	completeSourcePath.Format("%s",_completeSourcePath);

	CString destinationPath;
	destinationPath.Format("%s",_destinationPath);

	CString name;
	int pos = completeSourcePath.ReverseFind('\\');

	name = completeSourcePath.Mid(pos + 1);//name = 20160710.000143.01.19.398


	CString code = name.Mid(19,2);//code = 37
	CString date = NthInf(completeSourcePath,6);
	CString symbol = NthInf(completeSourcePath,7);

	CString appendNameDesPath;
	appendNameDesPath.Format("%s\\%s",destinationPath,name);//��code��ƴ��name

	FILE *dataFile = fopen (completeSourcePath, "rb");
	
	{
		//��Ϣͷ��
		BLOCKHEADMSG *blockHead = new BLOCKHEADMSG;
		{
			fread(&blockHead->productCode, sizeof(BLOCKHEADMSG), 1, dataFile);
			blockHead->productCode = ntohs(blockHead->productCode);//2���ֽڴ�С��ת��
			blockHead->productDate = ntohs(blockHead->productDate);
			//            NSDate *date = [NSDate dateWithTimeIntervalSince1970:blockHead->productDate * 24 *3600];
			//            NSDateFormatter *datefor = [[NSDateFormatter alloc] init];
			//            [datefor setDateFormat:@"yyyy-MM-dd"];
			//            NSString *string = [datefor stringFromDate:date];
			//            const char * string2c = [string UTF8String];

			blockHead->productTime = ntohl(blockHead->productTime);//4���ֽڴ�С��ת��
			//            unsigned int sec = (blockHead->productTime % 3600) %60;
			//            unsigned int min = (blockHead->productTime % 3600)/60;
			//            unsigned int hour = blockHead->productTime/3600;

			blockHead->fileLength = ntohl(blockHead->fileLength);
			blockHead->radarCode = ntohs(blockHead->radarCode);
			blockHead->receiveCode = ntohs(blockHead->receiveCode);
			blockHead->blockCount = ntohs(blockHead->blockCount);
			//            self.s_productCode = blockHead->productCode;
			//            (void)sec;(void)string2c;(void)min;(void)hour;
			//        cout << "��Ʒ���� " << blockHead.productCode << "\n";
			//        cout << "��Ʒ����ʱ�� " << string2c << "\n";
			//                cout << "��Ʒ����ʱ�� " << (hour/10>=1?"":"0") << hour <<":" << (min/10>1?"":"0") << min << ":" << (sec/10>1?"":"0") << sec <<"\n";
			//        cout << "�ļ������ֽ��� " << blockHead.fileLength << "\n";
			//        cout << "�״�վ���� " << blockHead.radarCode << "\n";
			//        cout << "����վ���� " << blockHead.receiveCode << "\n";
			//        cout << "�ļ��������ݿ���Ŀ " << blockHead.blockCount << "\n";
			delete blockHead;
		}
		//��Ʒ������
		BLOCKDESCRIPTION *descMsg = new BLOCKDESCRIPTION;
		{

			fread(descMsg, 102, 1, dataFile);
			descMsg->blockSepSymbol = ntohs(descMsg->blockSepSymbol);//blockSepSymbol
			descMsg->latitude = ntohl(descMsg->latitude);
			descMsg->longitude = ntohl(descMsg->longitude);
			descMsg->altitude = ntohs(descMsg->altitude);
			descMsg->productCode = ntohs(descMsg->productCode);
			descMsg->operationMode = ntohs(descMsg->operationMode);
			descMsg->vscanMode = ntohs(descMsg->vscanMode);
			descMsg->productSN = ntohs(descMsg->productSN);
			descMsg->vscanCode = ntohs(descMsg->vscanCode);
			descMsg->vscanDate = ntohs(descMsg->vscanDate);
			descMsg->vscanTime = ntohl(descMsg->vscanTime);
			descMsg->createDate = ntohs(descMsg->createDate);
			descMsg->createTime = ntohl(descMsg->createTime);
			descMsg->dependence1 = ntohs(descMsg->dependence1);
			descMsg->dependence2 = ntohs(descMsg->dependence2);
			descMsg->elevationCode = ntohs(descMsg->elevationCode);
			descMsg->dependence3 = ntohs(descMsg->dependence3);
			descMsg->threshold1 = ntohs(descMsg->threshold1);
			descMsg->threshold2 = ntohs(descMsg->threshold2);
			descMsg->threshold3 = ntohs(descMsg->threshold3);
			descMsg->threshold4 = ntohs(descMsg->threshold4);
			descMsg->threshold5 = ntohs(descMsg->threshold5);
			descMsg->threshold6 = ntohs(descMsg->threshold6);
			descMsg->threshold7 = ntohs(descMsg->threshold7);
			descMsg->threshold8 = ntohs(descMsg->threshold8);
			descMsg->threshold9 = ntohs(descMsg->threshold9);
			descMsg->threshold10 = ntohs(descMsg->threshold10);
			descMsg->threshold11 = ntohs(descMsg->threshold11);
			descMsg->threshold12 = ntohs(descMsg->threshold12);
			descMsg->threshold13 = ntohs(descMsg->threshold13);
			descMsg->threshold14 = ntohs(descMsg->threshold14);
			descMsg->threshold15 = ntohs(descMsg->threshold15);
			descMsg->threshold16 = ntohs(descMsg->threshold16);
			descMsg->dependence4 = ntohs(descMsg->dependence4);
			descMsg->dependence5 = ntohs(descMsg->dependence5);
			descMsg->dependence6 = ntohs(descMsg->dependence6);
			descMsg->dependence7 = ntohs(descMsg->dependence7);
			descMsg->dependence8 = ntohs(descMsg->dependence8);
			descMsg->dependence9 = ntohs(descMsg->dependence9);
			descMsg->dependence10 = ntohs(descMsg->dependence10);
			descMsg->vision = ntohs(descMsg->vision);
			descMsg->gapSymbology = ntohl(descMsg->gapSymbology);//60
			descMsg->gapGraphic = ntohl(descMsg->gapGraphic);//12450
			descMsg->gapAlpanumeric = ntohl(descMsg->gapAlpanumeric);
			delete descMsg;
		}

		//3.1��Ʒ���ſ�
		BLOCKSYMBOL *blockSymbol = new BLOCKSYMBOL;
		{
			//unsigned int ncount = (descMsg.gapGraphic - descMsg.gapSymbology )*2;//12450 - 60 = 24780��ʵӦ����-61 + 1
			fread(blockSymbol, 10, 1, dataFile);
			blockSymbol->blocksepSymbol = ntohs(blockSymbol->blocksepSymbol);//blockSepSymbol
			blockSymbol->blockCode = ntohs(blockSymbol->blockCode);
			blockSymbol->blockLength = ntohl(blockSymbol->blockLength);//24780
			blockSymbol->layerCount = ntohs(blockSymbol->layerCount);
		}
		//3.11��
		BLOCKLAYER *blockLayer = new BLOCKLAYER;
		{
			fread(blockLayer, 6, 1, dataFile);
			blockLayer->layersepSymbol = ntohs(blockLayer->layersepSymbol);
			blockLayer->layerLength = ntohl(blockLayer->layerLength);//24764
			//������������ݰ�Ҫ�����ͶԴ����ȶ�2���ֽڿ�����ʶ������ʲô
		}

		delete blockSymbol;
		//Ҫѭ����ȡ��ֱ�����������ݳ���== blockLayer.layerLength
		unsigned int readLength = 0;
		fpos_t gcurr;
		fgetpos(dataFile, &gcurr);
		while (readLength < blockLayer->layerLength)
		{
			unsigned short recogniseCode;
			fread(&recogniseCode, 2, 1, dataFile);
			recogniseCode = ntohs(recogniseCode);
			switch(recogniseCode)
			{
			case 0xBA0F:
			case 0xBA07:
				{
					unsigned int packageLength = 0;
					packageLength += 22;//դ�����ݰ�����

					//3.112դ�����ݰ�
					BLOCKGRID *blockGrid = new BLOCKGRID;
					fread(&blockGrid->packetCode2, sizeof(BLOCKGRID) - 2 - sizeof(blockGrid->blockGridRowAry), 1, dataFile);//ͷ�����Ѿ������� ���ָ�벻�ö�
					blockGrid->packetCode2 = ntohs(blockGrid->packetCode2);//1000000000000000  0x8000
					blockGrid->packetCode3 = ntohs(blockGrid->packetCode3);//11000000 0x00C0
					blockGrid->xStart = ntohs(blockGrid->xStart);
					blockGrid->yStart = ntohs(blockGrid->yStart);
					blockGrid->xScale = ntohs(blockGrid->xScale);
					blockGrid->reserve1 = ntohs(blockGrid->reserve1);
					blockGrid->yScale = ntohs(blockGrid->yScale);
					blockGrid->reserve2 = ntohs(blockGrid->reserve2);
					blockGrid->rowCount = ntohs(blockGrid->rowCount);//464
					blockGrid->packetFormat = ntohs(blockGrid->packetFormat);
					blockGrid->packetCode1 = recogniseCode;

					//����blockGrid.rowCount ����һ��ʢ��BLOCKGRIDROW������  464��դ����
					BLOCKGRIDROW *blockGridRowAry = new BLOCKGRIDROW[blockGrid->rowCount];
					vector<int> high464Row;
					vector<int> color464Row;
					for ( int i = 0 ; i < blockGrid->rowCount ; i++)
					{
						BLOCKGRIDROW *blockGridRow = blockGridRowAry + i;
						fread(&blockGridRow->byteCount, sizeof(unsigned short), 1, dataFile);
						//printf("%hu\n",blockGridRow->byteCount);
						blockGridRow->byteCount = ntohs(blockGridRow->byteCount);
						//դ���е����ֽ���Ӧ�ð��� �����ֽ���������ֽڰ�,�� դ�����ֽ��� = 2 + byteCount; 2�� 2 byteCount ���ֽ���
						packageLength += blockGridRow->byteCount + 2;

						//ÿ����n��դ��С�� 32��դ��С��
						BLOCKLITTLEDATA *blockLittleDataAry = new BLOCKLITTLEDATA[blockGridRow->byteCount];

						int lastColor = -1;
						//��blockGridRow������blockLittleData�ĸ�4֮�� = 464
						int mergeHigh = 0;
						int specifySum = 464;

						if(0 == code.Compare("41")||
							0 == code.Compare("57")){
								specifySum = 116;
						}
						vector<int> highs;
						vector<int> colors;
						for(int j = 0; j < blockGridRow->byteCount; j++)
						{
							BLOCKLITTLEDATA *blockLittleData = blockLittleDataAry + j;
							fread(&blockLittleData->data, 1, 1, dataFile);
							int high = (blockLittleData->data&240)>>4;
							int color = (blockLittleData->data&15);
							if (color == lastColor) {
								int sum = mergeHigh + high;
								//�������һ��һ��դ���е�դ��С�飬դ��С��֮�Ϳ��ܴ��ڳ������ڵ���255������һ���ֽڱ�ﷶΧ
								int largeSum = min(specifySum,255);
								//���ɣ�sumҲ���ܳ���specifySum����һ���ֽ���Ȼ�ܱ��255�������еĲ�Ʒһ��ֻ��116�����أ�������Ƚ�specifySum���ͻ������232�ϳ�һ��
								if (sum < largeSum) {
									mergeHigh = sum;
								}else{
									//����255��1111 1111��Ҳpushһ��
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
									mergeHigh = high;

								}
							}else{
								if (lastColor != -1) {
									//pushǰһ���ϲ�high��pushǰһ���ϲ�color
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
								}
								mergeHigh = high;
								lastColor = color;
							}
							if (j == blockGridRow->byteCount - 1) {
								highs.push_back(mergeHigh);
								colors.push_back(lastColor);
							}
						}
						//printf("%d\n",highs.size());
						high464Row.insert(high464Row.end(), highs.begin(),highs.end());
						color464Row.insert(color464Row.end(), colors.begin(),colors.end());

						blockGridRow->blockLittleDataAry = blockLittleDataAry;

					}

					high464Row.insert(high464Row.end(), color464Row.begin(),color464Row.end());

					string mudata(high464Row.begin(), high464Row.end());
					const char *source = mudata.c_str();

					unsigned char *comp = new unsigned char[1024*100];
					unsigned long compLen = 1024*100;;
					int err;
					err = compress(comp,&compLen,(const Bytef *)source,mudata.length());
					if(err == Z_OK){
						//printf("%lu\n",compLen);
					}else{
						printf("ѹ������ %d\n",err);
						return false;
					}

					//ѹ��������ݱ�����comp�У�������compLen��д���ļ�toPath��

					FILE *todest = fopen(appendNameDesPath,"wb");
					fwrite(comp,sizeof(char),compLen,todest);
					fclose(todest);
					todest = NULL;
					printf("���д��:%s\\%s\\%s\\%s\n",date,symbol,code,name);
					delete[] comp;

					/*
					��ѹ��
					unsigned char *uncomp = new unsigned char[1024*100];
					unsigned long uncompLen;
					uncompress(uncomp,&uncompLen,comp,compLen);
					printf("%lu",uncompLen);*/

					blockGrid->blockGridRowAry = blockGridRowAry;
					delete blockGrid;
					delete blockLayer;
					readLength += packageLength;

					fpos_t gcurr;
					fgetpos(dataFile, &gcurr);

					fclose(dataFile);
					dataFile = NULL;
					return true;
				}
				break;
			case 0xAF1F:
				{
					//3.111�������ݰ�
					unsigned int packageLength = 0;
					packageLength += 14;//���ݰ�����

					BLOCKRADIAL *blockRadial = new BLOCKRADIAL;
					fread(&blockRadial->firstBin, sizeof(BLOCKRADIAL) - 2 - sizeof(blockRadial->radialStripAry), 1, dataFile);
					blockRadial->firstBin = ntohs(blockRadial->firstBin);
					blockRadial->binCount = ntohs(blockRadial->binCount);
					blockRadial->xCenter = ntohs(blockRadial->xCenter);
					blockRadial->yCenter = ntohs(blockRadial->yCenter);
					blockRadial->scaleFactor = ntohs(blockRadial->scaleFactor);
					blockRadial->radialCount = ntohs(blockRadial->radialCount);
					blockRadial->packetCode = recogniseCode;

					BLOCKRADIALSTRIP *radialStripAry = new BLOCKRADIALSTRIP[blockRadial->radialCount];
					vector<int> high464Row;
					vector<int> color464Row;
					vector<int> delta464Row;//��Ʒ78����deltaΪ20��������˲�������Ϊ4��������λ����ʾ��������1���ֽ�
					unsigned short originAngle = -1;
					for (int i = 0 ; i < blockRadial->radialCount; i++) {
						BLOCKRADIALSTRIP *radialStip = radialStripAry + i;
						fread(&radialStip->byteCount, 6, 1, dataFile);
						radialStip->byteCount = ntohs(radialStip->byteCount) * 2;
						radialStip->angleStart = ntohs(radialStip->angleStart);
						if(i == 0){
							originAngle = radialStip->angleStart;
						}

						radialStip->angleDelta = ntohs(radialStip->angleDelta);
						delta464Row.push_back(radialStip->angleDelta);

						//դ���е����ֽ���Ӧ�ð��� �����ֽ���������ֽڰ�,�� դ�����ֽ��� = 2 + byteCount; 2�� 2 byteCount ���ֽ���
						packageLength += radialStip->byteCount + 6;

						//ÿ����n��դ��С�� 32��դ��С��
						BLOCKLITTLEDATA *blockLittleDataAry = new BLOCKLITTLEDATA[radialStip->byteCount];

						int lastColor = -1;
						int highSum = 0;
						int mergeHigh = 0;
						int specifySum = 230;

						if(0 == code.Compare("78")){
							specifySum = 115;
						}
						/*
						�����ɫ��ͬ���Һϲ�����<255��ϲ�
						����255��push
						*/
						vector<int> highs;
						vector<int> colors;
						for(int j = 0; j < radialStip->byteCount; j++)
						{
							BLOCKLITTLEDATA *blockLittleData = blockLittleDataAry + j;
							fread(&blockLittleData->data, 1, 1, dataFile);
							int high = (blockLittleData->data&240)>>4;
							int color = (blockLittleData->data&15);
							highSum += high;

							if (color == lastColor) {
								int sum = mergeHigh + high;
								int largeSum = min(specifySum,255);
								//���ɣ�sumҲ���ܳ���specifySum����һ���ֽ���Ȼ�ܱ��255�������еĲ�Ʒһ��ֻ��116�����أ�������Ƚ�specifySum���ͻ������232�ϳ�һ��
								if (sum < largeSum) {
									mergeHigh = sum;
								}else{
									//�������һ�������ľ���С�飬����������С��֮�Ͳ��ᳬ��230������С��255��1111 1111��,���Ա�֤1���ֽڱ����������������ִ��
									if(mergeHigh == 0){

									}
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
									mergeHigh = high;

								}
							}else{
								if (lastColor != -1) {
									//pushǰһ���ϲ�high��pushǰһ���ϲ�color
									if(mergeHigh == 0){

									}
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
								}
								mergeHigh = high;
								lastColor = color;
							}
							if (j == radialStip->byteCount - 1) {
								if(mergeHigh != 0){
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
								}

							}


						}
						high464Row.insert(high464Row.end(), highs.begin(),highs.end());
						color464Row.insert(color464Row.end(), colors.begin(),colors.end());

						radialStip->blockLittleDataAry = blockLittleDataAry;
					}
					//[mudata appendBytes:&originAngle length:2];
					//[mudata appendBytes:&(blockRadial->radialCount) length:2];
					//high464Row.insert(0,blockRadial->radialCount);
					//high464Row.insert(0,originAngle);
					//insert �����ֽڵ�blockRadial->radialCount 
					int radialCount = blockRadial->radialCount;
					if (radialCount <= 500){
						if (radialCount > 255){
						int over = radialCount - 255;
						high464Row.insert(high464Row.begin(),(int)255);
						high464Row.insert(high464Row.begin(),over);
					}else{
						high464Row.insert(high464Row.begin(),radialCount);
						high464Row.insert(high464Row.begin(),(int)0);
					}
					}else{
						printf("�������� %s \n",name);
						return false;
					}
					
					//insert �����ֽڵ�originAngle
					originAngle = originAngle/10;//171
					originAngle = originAngle%360;
					if (originAngle > 255){
						int over = originAngle - 255;
						high464Row.insert(high464Row.begin(),(int)255);
						high464Row.insert(high464Row.begin(),over);
					}else{
						high464Row.insert(high464Row.begin(),originAngle);
						high464Row.insert(high464Row.begin(),(int)0);
					}

					high464Row.insert(high464Row.end(), color464Row.begin(),color464Row.end());
					high464Row.insert(high464Row.end(), delta464Row.begin(),delta464Row.end());

					string mudata(high464Row.begin(), high464Row.end());
					const char *source = mudata.c_str();
					unsigned char *comp = new unsigned char[1024*100];
					unsigned long compLen = 1024*100;;
					int err;
					err = compress(comp,&compLen,(const Bytef *)source,mudata.length());
					if(err == Z_OK){
						//printf("%lu\n",compLen);
					}else{
						printf("ѹ������ %d\n",err);
						return false;
					}

					//ѹ��������ݱ�����comp�У�������compLen��д���ļ�toPath��

					FILE *todest = fopen(appendNameDesPath,"wb");
					fwrite(comp,sizeof(char),compLen,todest);
					fclose(todest);
					todest = NULL;
					printf("���д��:%s\\%s\\%s\\%s\n",date,symbol,code,name);
					delete[] comp;


					blockRadial->radialStripAry = radialStripAry;
					delete blockRadial;
					delete blockLayer;
					readLength += packageLength;
					fclose(dataFile);
					dataFile = NULL;
					return true;
					//                    self.m_blockRadial = blockRadial;
				}
				break;
			case 6:
			case 9:
				{
					//3.113�������ݰ�
				}
				break;
			case 1:
			case 2:
			case 8:
			case 15:
				{
					//3.114�ı����ݰ�
				}
				break;
				//3.115��ֵ�����ݰ�
			default:
				{

				}
				break;
			}
		}
		delete blockLayer;
	}
	fclose(dataFile);
	dataFile = NULL;
}

void luoyang(LPCTSTR checkTime,LPCTSTR timeTemp,LPCTSTR cSourcePath,LPCTSTR cDesPath)
{
			CString desTmp;
			desTmp.Format("%s\\luoyang",cDesPath);
			if(!PathFileExists(desTmp))
				CreateDirectory(desTmp,NULL);

			CString desPathAppendDate;//Ŀ��Ŀ¼+����
			desPathAppendDate.Format("%s\\%s",desTmp,timeTemp);
			if(!PathFileExists(desPathAppendDate))
				CreateDirectory(desPathAppendDate,NULL);

			CString desPathAppendLog;//Ŀ��Ŀ¼+����+log
			desPathAppendLog.Format("%s\\%s\\log.txt",desTmp,timeTemp);
		
			//if(!PathFileExists(desPathAppendLog))
			//	CreateDirectory(desPathAppendLog,NULL);
			CString logStr;
			logStr.Format("*****************���ʱ�� %s*****************\n",checkTime);

			CString sourcePath;//Դ�ļ�Ŀ¼
			CString symbolName[6] = {"CR","R","V","ET","OHP","VIL"};
			CString codeName[6] = {"37","19","27","41","78","57"};
			for (int i = 0; i < 6 ; i ++)
			{
				sourcePath.Format("%s\\%s\\%s\\%s",cSourcePath,timeTemp,symbolName[i],codeName[i]);//ƴ�������ڡ���Ʒ��д����Ʒ���ŵ�������Դ�ļ�Ŀ¼
				logStr += "\n������������ƷĿ¼��";
				logStr += sourcePath;
				logStr += "\n";
				printf("luoyang��Ʒ��%s\n",symbolName[i]);

				if(!PathFileExists(sourcePath))
				{
					logStr += "    �ò�ƷĿ¼�ڷ������ϲ����ڻ����!!!\n";
					
					continue;
				}
				else
				{
					logStr += "    ���ڷ������ϼ������ò�ƷĿ¼\n";
				}


				CString desPathAppendDateSymbol;//Ŀ��Ŀ¼+����+��Ʒ��д
				desPathAppendDateSymbol.Format("%s\\%s",desPathAppendDate,symbolName[i]);
				if(!PathFileExists(desPathAppendDateSymbol))
					CreateDirectory(desPathAppendDateSymbol,NULL);

				CString completeDesPath;//Ŀ��Ŀ¼+����+��Ʒ��д+��Ʒ����= ������Ŀ��Ŀ¼·��
				completeDesPath.Format("%s\\%s",desPathAppendDateSymbol,codeName[i]);
				if(!PathFileExists(completeDesPath))
					CreateDirectory(completeDesPath,NULL);

				//�Ա�completeDesPath��sourcePath
				long hFile = 0;
				struct _finddata_t fileInfo;
				string pathName;
				//����Դ�ļ�Ŀ¼
				vector<CString> sourceFiles;
				if ((hFile = _findfirst(pathName.assign(sourcePath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig������ֵ����
							//printf("Դ�ļ�%s  %d\n",fileName,fileName.Find("ProductIndex"));
							if(fileName.Find("ProductIndex") == -1)
							{
								sourceFiles.push_back(fileName);
							}

						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);
				//����Ŀ���ļ�Ŀ¼
				hFile = 0;
				vector<CString> desFiles;
				if ((hFile = _findfirst(pathName.assign(completeDesPath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig������ֵ����
							//printf("Ŀ���ļ�%s\n",fileName);
							desFiles.push_back(fileName);
						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);

				CString logTmpStr;
						logTmpStr.Format("    �ڷ������ϼ����� %d ���ļ������ش��� %d ���ļ�����ͬ�� %d ���ļ�\n",sourceFiles.size(),desFiles.size(),sourceFiles.size()-desFiles.size());
				logStr += logTmpStr;

				if(sourceFiles.size()-desFiles.size() > 0){
					logStr += "    ----------------------------------\n";
				}
				//�Ҳ�ͬ
				vector<CString>::iterator iter;
				int idx = 0;
				for (iter=sourceFiles.begin();iter!=sourceFiles.end();iter++)
				{
					CString eachSource = *iter;
					BOOL finded = false;
					vector<CString>::iterator iter2;
					for (iter2=desFiles.begin();iter2!=desFiles.end();iter2++)
					{
						CString eachDes = *iter2;
						if(eachSource.Compare(eachDes) == 0){
							finded = true;
							break;
						}
					}

					if(!finded){
						//Ŀ���ļ���û�У���Ҫ����
						//printf("%d %s\n",idx,eachSource);

						CString completeSourcePath;
						completeSourcePath.Format("%s\\%s",sourcePath,eachSource);

						bool resul = recode(completeSourcePath,completeDesPath);

						CString logTmpStr2;
						logTmpStr2.Format("    %s  %s\n",completeSourcePath, resul?"�ɹ�":"ʧ��!!!");
						logStr += logTmpStr2;

					}

					idx++;
				}

			}

			logStr += "\n**********************************\n\n\n";
			FILE *logFile = fopen(desPathAppendLog,"a+");
			
			fwrite(logStr,1,logStr.GetLength(),logFile);
			fclose(logFile);
			logFile = NULL;

}

void sanmenxia(LPCTSTR checkTime,LPCTSTR timeTemp,LPCTSTR cSourcePath,LPCTSTR cDesPath)
{
			CString desTmp;
			desTmp.Format("%s\\sanmenxia",cDesPath);
			if(!PathFileExists(desTmp))
				CreateDirectory(desTmp,NULL);

			CString desPathAppendDate;//Ŀ��Ŀ¼+����
			desPathAppendDate.Format("%s\\%s",desTmp,timeTemp);
			if(!PathFileExists(desPathAppendDate))
				CreateDirectory(desPathAppendDate,NULL);

			CString desPathAppendLog;//Ŀ��Ŀ¼+����+log
			desPathAppendLog.Format("%s\\%s\\log.txt",desTmp,timeTemp);
		
			//if(!PathFileExists(desPathAppendLog))
			//	CreateDirectory(desPathAppendLog,NULL);
			CString logStr;
			logStr.Format("*****************���ʱ�� %s*****************\n",checkTime);

			CString sourcePath;//Դ�ļ�Ŀ¼
			CString symbolName[6] = {"CR","R","V","ET","OHP","VIL"};
			CString codeName[6] = {"37","19","27","41","78","57"};
			for (int i = 0; i < 6 ; i ++)
			{
				sourcePath.Format("%s\\%s\\%s\\%s",cSourcePath,timeTemp,symbolName[i],codeName[i]);//ƴ�������ڡ���Ʒ��д����Ʒ���ŵ�������Դ�ļ�Ŀ¼
				logStr += "\n������������ƷĿ¼��";
				logStr += sourcePath;
				logStr += "\n";
				printf("sanmenxia��Ʒ��%s\n",symbolName[i]);

				if(!PathFileExists(sourcePath))
				{
					logStr += "    �ò�ƷĿ¼�ڷ������ϲ����ڻ����!!!\n";
					
					continue;
				}
				else
				{
					logStr += "    ���ڷ������ϼ������ò�ƷĿ¼\n";
				}


				CString desPathAppendDateSymbol;//Ŀ��Ŀ¼+����+��Ʒ��д
				desPathAppendDateSymbol.Format("%s\\%s",desPathAppendDate,symbolName[i]);
				if(!PathFileExists(desPathAppendDateSymbol))
					CreateDirectory(desPathAppendDateSymbol,NULL);

				CString completeDesPath;//Ŀ��Ŀ¼+����+��Ʒ��д+��Ʒ����= ������Ŀ��Ŀ¼·��
				completeDesPath.Format("%s\\%s",desPathAppendDateSymbol,codeName[i]);
				if(!PathFileExists(completeDesPath))
					CreateDirectory(completeDesPath,NULL);

				//�Ա�completeDesPath��sourcePath
				long hFile = 0;
				struct _finddata_t fileInfo;
				string pathName;
				//����Դ�ļ�Ŀ¼
				vector<CString> sourceFiles;
				if ((hFile = _findfirst(pathName.assign(sourcePath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig������ֵ����
							//printf("Դ�ļ�%s  %d\n",fileName,fileName.Find("ProductIndex"));
							if(fileName.Find("ProductIndex") == -1)
							{
								sourceFiles.push_back(fileName);
							}

						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);
				//����Ŀ���ļ�Ŀ¼
				hFile = 0;
				vector<CString> desFiles;
				if ((hFile = _findfirst(pathName.assign(completeDesPath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig������ֵ����
							//printf("Ŀ���ļ�%s\n",fileName);
							desFiles.push_back(fileName);
						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);

				CString logTmpStr;
						logTmpStr.Format("    �ڷ������ϼ����� %d ���ļ������ش��� %d ���ļ�����ͬ�� %d ���ļ�\n",sourceFiles.size(),desFiles.size(),sourceFiles.size()-desFiles.size());
				logStr += logTmpStr;

				if(sourceFiles.size()-desFiles.size() > 0){
					logStr += "    ----------------------------------\n";
				}
				//�Ҳ�ͬ
				vector<CString>::iterator iter;
				int idx = 0;
				for (iter=sourceFiles.begin();iter!=sourceFiles.end();iter++)
				{
					CString eachSource = *iter;
					BOOL finded = false;
					vector<CString>::iterator iter2;
					for (iter2=desFiles.begin();iter2!=desFiles.end();iter2++)
					{
						CString eachDes = *iter2;
						if(eachSource.Compare(eachDes) == 0){
							finded = true;
							break;
						}
					}

					if(!finded){
						//Ŀ���ļ���û�У���Ҫ����
						//printf("%d %s\n",idx,eachSource);

						CString completeSourcePath;
						completeSourcePath.Format("%s\\%s",sourcePath,eachSource);

						bool resul = recode(completeSourcePath,completeDesPath);

						CString logTmpStr2;
						logTmpStr2.Format("    %s  %s\n",completeSourcePath, resul?"�ɹ�":"ʧ��!!!");
						logStr += logTmpStr2;

					}

					idx++;
				}

			}

			logStr += "\n**********************************\n\n\n";
			FILE *logFile = fopen(desPathAppendLog,"a+");
			
			fwrite(logStr,1,logStr.GetLength(),logFile);
			fclose(logFile);
			logFile = NULL;

}
void tests(){
	vector<int> highs;
	for (int i = 0 ; i < 255; i++){
		highs.push_back(i);
	}
	string mudata(highs.begin(), highs.end());

	const char *source = mudata.c_str();
	unsigned char *comp = new unsigned char[1024*100];
	unsigned long compLen = 1024*100;;
	int err;
	err = compress(comp,&compLen,(const Bytef *)source,mudata.length());
	if(err == Z_OK){
		//printf("%lu\n",compLen);
	}else{
		printf("ѹ������ %d\n",err);
	}

	//ѹ��������ݱ�����comp�У�������compLen��д���ļ�toPath��

	FILE *todest = fopen("\\\\192.168.1.120\\��ʱ����\\ţһ��\\test\\a","wb");
	fwrite(comp,sizeof(char),compLen,todest);
	fclose(todest);
	todest = NULL;
}
BOOL BuildDirectory(CString strPath)
{
CString strSubPath;
CString strInfo;
int nCount = 0; 
int nIndex = 0;

//�����ַ�"\\"�ĸ���
do
{
nIndex = strPath.Find("\\",nIndex) + 1;
nCount++;
}while( (nIndex-1) != -1);
nIndex = 0;
//��飬������Ŀ¼
while( (nCount-1) >= 0)
{
nIndex = strPath.Find("\\",nIndex) + 1;
if( (nIndex - 1) == -1)
{
strSubPath = strPath;
}
else
strSubPath = strPath.Left(nIndex);
if(!PathFileExists(strSubPath))
{
if(!::CreateDirectory(strSubPath,NULL))
{
strInfo = "Build Directory";
strInfo += strSubPath;
strInfo += " Fail!";
AfxMessageBox(strInfo,MB_OK);
return FALSE;
}
}
nCount--;
};
return TRUE;
}
int _tmain(int argc, _TCHAR* argv[])
{
	//tests();
	//return 0;
	int nRetCode = 0;

	
	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		char cLuoyangPath[256] = {0};//Դ��ַ
		char cSanmenxiaPath[256] = {0};//Դ��ַ
		char cDesPath[256] = {0};//Ŀ�ĵ�ַ


		/*
		"CONFIG"section��
		"srcpath" ����
		cSrcPath �洢����
		".\\config.ini" �����ļ���ַ
		�������ļ��ж�ȡ������ֵ��������
		*/
		if (0 == GetPrivateProfileString("CONFIG","luoyang","",cLuoyangPath,sizeof(cLuoyangPath),".\\config.ini")||
			0 == GetPrivateProfileString("CONFIG","sanmenxia","",cSanmenxiaPath,sizeof(cSanmenxiaPath),".\\config.ini")||
			0 == GetPrivateProfileString("CONFIG","despath","",cDesPath,sizeof(cDesPath),".\\config.ini")
			)
		{
			printf("��ȡ�����ļ�ʧ�ܣ�\n");
			Sleep(10000);
			return nRetCode;
		}

		while(TRUE)
		{

			SYSTEMTIME Time;
			GetLocalTime(&Time);
			CString TimeTemp;
			if (Time.wHour - 7 > 0)
			{
				TimeTemp.Format("%0.4d%0.2d%0.2d",Time.wYear,Time.wMonth,Time.wDay);
			}
			else
			{
				TimeTemp.Format("%0.4d%0.2d%0.2d",Time.wYear,Time.wMonth,(Time.wDay - 1));
			}
			//TimeTemp = "20160929";
			CString printTime;
			printTime.Format("%0.2d:%0.2d:%0.2d",Time.wHour,Time.wMinute,Time.wSecond);
			printf("���ʱ�䣺%s\n",printTime);

			CString luoyangPath;
			luoyangPath.Format("%s",cLuoyangPath);
			CString sanmenxiaPath;
			sanmenxiaPath.Format("%s",cSanmenxiaPath);
			CString desPath;
			desPath.Format("%s",cDesPath);

			BuildDirectory(cDesPath);
			luoyang(printTime.GetString(),TimeTemp.GetString(),luoyangPath.GetString(),desPath.GetString());
			sanmenxia(printTime.GetString(),TimeTemp.GetString(),sanmenxiaPath.GetString(),desPath.GetString());
			Sleep(1000*60);
		}


	}
		return 0;
}

