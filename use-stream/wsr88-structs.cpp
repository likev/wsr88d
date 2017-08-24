// RecodeCompress.cpp : 定义控制台应用程序的入口点。
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
	//发现
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
	appendNameDesPath.Format("%s\\%s",destinationPath,name);//在code后拼接name

	FILE *dataFile = fopen (completeSourcePath, "rb");
	
	{
		//信息头块
		BLOCKHEADMSG *blockHead = new BLOCKHEADMSG;
		{
			fread(&blockHead->productCode, sizeof(BLOCKHEADMSG), 1, dataFile);
			blockHead->productCode = ntohs(blockHead->productCode);//2个字节大小端转换
			blockHead->productDate = ntohs(blockHead->productDate);
			//            NSDate *date = [NSDate dateWithTimeIntervalSince1970:blockHead->productDate * 24 *3600];
			//            NSDateFormatter *datefor = [[NSDateFormatter alloc] init];
			//            [datefor setDateFormat:@"yyyy-MM-dd"];
			//            NSString *string = [datefor stringFromDate:date];
			//            const char * string2c = [string UTF8String];

			blockHead->productTime = ntohl(blockHead->productTime);//4个字节大小端转换
			//            unsigned int sec = (blockHead->productTime % 3600) %60;
			//            unsigned int min = (blockHead->productTime % 3600)/60;
			//            unsigned int hour = blockHead->productTime/3600;

			blockHead->fileLength = ntohl(blockHead->fileLength);
			blockHead->radarCode = ntohs(blockHead->radarCode);
			blockHead->receiveCode = ntohs(blockHead->receiveCode);
			blockHead->blockCount = ntohs(blockHead->blockCount);
			//            self.s_productCode = blockHead->productCode;
			//            (void)sec;(void)string2c;(void)min;(void)hour;
			//        cout << "产品代号 " << blockHead.productCode << "\n";
			//        cout << "产品生成时期 " << string2c << "\n";
			//                cout << "产品生成时间 " << (hour/10>=1?"":"0") << hour <<":" << (min/10>1?"":"0") << min << ":" << (sec/10>1?"":"0") << sec <<"\n";
			//        cout << "文件包含字节数 " << blockHead.fileLength << "\n";
			//        cout << "雷达站代号 " << blockHead.radarCode << "\n";
			//        cout << "接收站代号 " << blockHead.receiveCode << "\n";
			//        cout << "文件包含数据块数目 " << blockHead.blockCount << "\n";
			delete blockHead;
		}
		//产品描述块
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

		//3.1产品符号块
		BLOCKSYMBOL *blockSymbol = new BLOCKSYMBOL;
		{
			//unsigned int ncount = (descMsg.gapGraphic - descMsg.gapSymbology )*2;//12450 - 60 = 24780其实应该是-61 + 1
			fread(blockSymbol, 10, 1, dataFile);
			blockSymbol->blocksepSymbol = ntohs(blockSymbol->blocksepSymbol);//blockSepSymbol
			blockSymbol->blockCode = ntohs(blockSymbol->blockCode);
			blockSymbol->blockLength = ntohl(blockSymbol->blockLength);//24780
			blockSymbol->layerCount = ntohs(blockSymbol->layerCount);
		}
		//3.11层
		BLOCKLAYER *blockLayer = new BLOCKLAYER;
		{
			fread(blockLayer, 6, 1, dataFile);
			blockLayer->layersepSymbol = ntohs(blockLayer->layersepSymbol);
			blockLayer->layerLength = ntohl(blockLayer->layerLength);//24764
			//层接下来的数据包要分类型对待，先读2个字节看看包识别码是什么
		}

		delete blockSymbol;
		//要循环读取，直到读到的数据长度== blockLayer.layerLength
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
					packageLength += 22;//栅格数据包长度

					//3.112栅格数据包
					BLOCKGRID *blockGrid = new BLOCKGRID;
					fread(&blockGrid->packetCode2, sizeof(BLOCKGRID) - 2 - sizeof(blockGrid->blockGridRowAry), 1, dataFile);//头两个已经读过， 最后指针不用读
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

					//根据blockGrid.rowCount 创建一个盛放BLOCKGRIDROW的数组  464个栅格行
					BLOCKGRIDROW *blockGridRowAry = new BLOCKGRIDROW[blockGrid->rowCount];
					vector<int> high464Row;
					vector<int> color464Row;
					for ( int i = 0 ; i < blockGrid->rowCount ; i++)
					{
						BLOCKGRIDROW *blockGridRow = blockGridRowAry + i;
						fread(&blockGridRow->byteCount, sizeof(unsigned short), 1, dataFile);
						//printf("%hu\n",blockGridRow->byteCount);
						blockGridRow->byteCount = ntohs(blockGridRow->byteCount);
						//栅格行的行字节数应该包含 “行字节数”这个字节吧,错 栅格行字节数 = 2 + byteCount; 2即 2 byteCount 行字节数
						packageLength += blockGridRow->byteCount + 2;

						//每行有n个栅格小块 32个栅格小块
						BLOCKLITTLEDATA *blockLittleDataAry = new BLOCKLITTLEDATA[blockGridRow->byteCount];

						int lastColor = -1;
						//本blockGridRow的所有blockLittleData的高4之和 = 464
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
								//这里遍历一个一个栅格行的栅格小块，栅格小块之和可能存在超过大于等于255，超过一个字节表达范围
								int largeSum = min(specifySum,255);
								//存疑，sum也可能超过specifySum，即一个字节虽然能表达255，但是有的产品一行只有116个像素，如果不比较specifySum，就会把两行232合成一行
								if (sum < largeSum) {
									mergeHigh = sum;
								}else{
									//超过255即1111 1111，也push一次
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
									mergeHigh = high;

								}
							}else{
								if (lastColor != -1) {
									//push前一个合并high，push前一个合并color
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
						printf("压缩错误 %d\n",err);
						return false;
					}

					//压缩后的数据保存在comp中，长度是compLen，写到文件toPath中

					FILE *todest = fopen(appendNameDesPath,"wb");
					fwrite(comp,sizeof(char),compLen,todest);
					fclose(todest);
					todest = NULL;
					printf("完成写入:%s\\%s\\%s\\%s\n",date,symbol,code,name);
					delete[] comp;

					/*
					解压缩
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
					//3.111径向数据包
					unsigned int packageLength = 0;
					packageLength += 14;//数据包长度

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
					vector<int> delta464Row;//产品78出现delta为20的情况，顾不能缩减为4个二进制位来表示，必须用1个字节
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

						//栅格行的行字节数应该包含 “行字节数”这个字节吧,错 栅格行字节数 = 2 + byteCount; 2即 2 byteCount 行字节数
						packageLength += radialStip->byteCount + 6;

						//每行有n个栅格小块 32个栅格小块
						BLOCKLITTLEDATA *blockLittleDataAry = new BLOCKLITTLEDATA[radialStip->byteCount];

						int lastColor = -1;
						int highSum = 0;
						int mergeHigh = 0;
						int specifySum = 230;

						if(0 == code.Compare("78")){
							specifySum = 115;
						}
						/*
						如果颜色相同并且合并长度<255则合并
						超过255就push
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
								//存疑，sum也可能超过specifySum，即一个字节虽然能表达255，但是有的产品一行只有116个像素，如果不比较specifySum，就会把两行232合成一行
								if (sum < largeSum) {
									mergeHigh = sum;
								}else{
									//这里遍历一个径条的径向小块，理论上所有小块之和不会超过230，即恒小于255（1111 1111）,可以保证1个字节表达，所以这里基本不会执行
									if(mergeHigh == 0){

									}
									highs.push_back(mergeHigh);
									colors.push_back(lastColor);
									mergeHigh = high;

								}
							}else{
								if (lastColor != -1) {
									//push前一个合并high，push前一个合并color
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
					//insert 两个字节的blockRadial->radialCount 
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
						printf("解析错误 %s \n",name);
						return false;
					}
					
					//insert 两个字节的originAngle
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
						printf("压缩错误 %d\n",err);
						return false;
					}

					//压缩后的数据保存在comp中，长度是compLen，写到文件toPath中

					FILE *todest = fopen(appendNameDesPath,"wb");
					fwrite(comp,sizeof(char),compLen,todest);
					fclose(todest);
					todest = NULL;
					printf("完成写入:%s\\%s\\%s\\%s\n",date,symbol,code,name);
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
					//3.113向量数据包
				}
				break;
			case 1:
			case 2:
			case 8:
			case 15:
				{
					//3.114文本数据包
				}
				break;
				//3.115等值线数据包
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

			CString desPathAppendDate;//目标目录+日期
			desPathAppendDate.Format("%s\\%s",desTmp,timeTemp);
			if(!PathFileExists(desPathAppendDate))
				CreateDirectory(desPathAppendDate,NULL);

			CString desPathAppendLog;//目标目录+日期+log
			desPathAppendLog.Format("%s\\%s\\log.txt",desTmp,timeTemp);
		
			//if(!PathFileExists(desPathAppendLog))
			//	CreateDirectory(desPathAppendLog,NULL);
			CString logStr;
			logStr.Format("*****************检测时间 %s*****************\n",checkTime);

			CString sourcePath;//源文件目录
			CString symbolName[6] = {"CR","R","V","ET","OHP","VIL"};
			CString codeName[6] = {"37","19","27","41","78","57"};
			for (int i = 0; i < 6 ; i ++)
			{
				sourcePath.Format("%s\\%s\\%s\\%s",cSourcePath,timeTemp,symbolName[i],codeName[i]);//拼接上日期、产品缩写、产品代号的完整的源文件目录
				logStr += "\n检索服务器产品目录：";
				logStr += sourcePath;
				logStr += "\n";
				printf("luoyang产品：%s\n",symbolName[i]);

				if(!PathFileExists(sourcePath))
				{
					logStr += "    该产品目录在服务器上不存在或出错!!!\n";
					
					continue;
				}
				else
				{
					logStr += "    已在服务器上检索到该产品目录\n";
				}


				CString desPathAppendDateSymbol;//目标目录+日期+产品缩写
				desPathAppendDateSymbol.Format("%s\\%s",desPathAppendDate,symbolName[i]);
				if(!PathFileExists(desPathAppendDateSymbol))
					CreateDirectory(desPathAppendDateSymbol,NULL);

				CString completeDesPath;//目标目录+日期+产品缩写+产品代号= 完整的目标目录路径
				completeDesPath.Format("%s\\%s",desPathAppendDateSymbol,codeName[i]);
				if(!PathFileExists(completeDesPath))
					CreateDirectory(completeDesPath,NULL);

				//对比completeDesPath与sourcePath
				long hFile = 0;
				struct _finddata_t fileInfo;
				string pathName;
				//遍历源文件目录
				vector<CString> sourceFiles;
				if ((hFile = _findfirst(pathName.assign(sourcePath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig这样赋值对吗
							//printf("源文件%s  %d\n",fileName,fileName.Find("ProductIndex"));
							if(fileName.Find("ProductIndex") == -1)
							{
								sourceFiles.push_back(fileName);
							}

						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);
				//遍历目标文件目录
				hFile = 0;
				vector<CString> desFiles;
				if ((hFile = _findfirst(pathName.assign(completeDesPath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig这样赋值对吗
							//printf("目标文件%s\n",fileName);
							desFiles.push_back(fileName);
						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);

				CString logTmpStr;
						logTmpStr.Format("    在服务器上检索到 %d 个文件，本地存在 %d 个文件，需同步 %d 个文件\n",sourceFiles.size(),desFiles.size(),sourceFiles.size()-desFiles.size());
				logStr += logTmpStr;

				if(sourceFiles.size()-desFiles.size() > 0){
					logStr += "    ----------------------------------\n";
				}
				//找不同
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
						//目标文件中没有，需要生成
						//printf("%d %s\n",idx,eachSource);

						CString completeSourcePath;
						completeSourcePath.Format("%s\\%s",sourcePath,eachSource);

						bool resul = recode(completeSourcePath,completeDesPath);

						CString logTmpStr2;
						logTmpStr2.Format("    %s  %s\n",completeSourcePath, resul?"成功":"失败!!!");
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

			CString desPathAppendDate;//目标目录+日期
			desPathAppendDate.Format("%s\\%s",desTmp,timeTemp);
			if(!PathFileExists(desPathAppendDate))
				CreateDirectory(desPathAppendDate,NULL);

			CString desPathAppendLog;//目标目录+日期+log
			desPathAppendLog.Format("%s\\%s\\log.txt",desTmp,timeTemp);
		
			//if(!PathFileExists(desPathAppendLog))
			//	CreateDirectory(desPathAppendLog,NULL);
			CString logStr;
			logStr.Format("*****************检测时间 %s*****************\n",checkTime);

			CString sourcePath;//源文件目录
			CString symbolName[6] = {"CR","R","V","ET","OHP","VIL"};
			CString codeName[6] = {"37","19","27","41","78","57"};
			for (int i = 0; i < 6 ; i ++)
			{
				sourcePath.Format("%s\\%s\\%s\\%s",cSourcePath,timeTemp,symbolName[i],codeName[i]);//拼接上日期、产品缩写、产品代号的完整的源文件目录
				logStr += "\n检索服务器产品目录：";
				logStr += sourcePath;
				logStr += "\n";
				printf("sanmenxia产品：%s\n",symbolName[i]);

				if(!PathFileExists(sourcePath))
				{
					logStr += "    该产品目录在服务器上不存在或出错!!!\n";
					
					continue;
				}
				else
				{
					logStr += "    已在服务器上检索到该产品目录\n";
				}


				CString desPathAppendDateSymbol;//目标目录+日期+产品缩写
				desPathAppendDateSymbol.Format("%s\\%s",desPathAppendDate,symbolName[i]);
				if(!PathFileExists(desPathAppendDateSymbol))
					CreateDirectory(desPathAppendDateSymbol,NULL);

				CString completeDesPath;//目标目录+日期+产品缩写+产品代号= 完整的目标目录路径
				completeDesPath.Format("%s\\%s",desPathAppendDateSymbol,codeName[i]);
				if(!PathFileExists(completeDesPath))
					CreateDirectory(completeDesPath,NULL);

				//对比completeDesPath与sourcePath
				long hFile = 0;
				struct _finddata_t fileInfo;
				string pathName;
				//遍历源文件目录
				vector<CString> sourceFiles;
				if ((hFile = _findfirst(pathName.assign(sourcePath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig这样赋值对吗
							//printf("源文件%s  %d\n",fileName,fileName.Find("ProductIndex"));
							if(fileName.Find("ProductIndex") == -1)
							{
								sourceFiles.push_back(fileName);
							}

						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);
				//遍历目标文件目录
				hFile = 0;
				vector<CString> desFiles;
				if ((hFile = _findfirst(pathName.assign(completeDesPath.GetBuffer()).append("\\*").c_str(), &fileInfo)) != -1) {
					do 
					{
						if(fileInfo.attrib&_A_SUBDIR){
							//folder
						}else{

							CString fileName = fileInfo.name;//CStrig这样赋值对吗
							//printf("目标文件%s\n",fileName);
							desFiles.push_back(fileName);
						}

					} while (_findnext(hFile, &fileInfo) == 0);
				}
				_findclose(hFile);

				CString logTmpStr;
						logTmpStr.Format("    在服务器上检索到 %d 个文件，本地存在 %d 个文件，需同步 %d 个文件\n",sourceFiles.size(),desFiles.size(),sourceFiles.size()-desFiles.size());
				logStr += logTmpStr;

				if(sourceFiles.size()-desFiles.size() > 0){
					logStr += "    ----------------------------------\n";
				}
				//找不同
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
						//目标文件中没有，需要生成
						//printf("%d %s\n",idx,eachSource);

						CString completeSourcePath;
						completeSourcePath.Format("%s\\%s",sourcePath,eachSource);

						bool resul = recode(completeSourcePath,completeDesPath);

						CString logTmpStr2;
						logTmpStr2.Format("    %s  %s\n",completeSourcePath, resul?"成功":"失败!!!");
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
		printf("压缩错误 %d\n",err);
	}

	//压缩后的数据保存在comp中，长度是compLen，写到文件toPath中

	FILE *todest = fopen("\\\\192.168.1.120\\临时场所\\牛一鸣\\test\\a","wb");
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

//查找字符"\\"的个数
do
{
nIndex = strPath.Find("\\",nIndex) + 1;
nCount++;
}while( (nIndex-1) != -1);
nIndex = 0;
//检查，并创建目录
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

	
	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		char cLuoyangPath[256] = {0};//源地址
		char cSanmenxiaPath[256] = {0};//源地址
		char cDesPath[256] = {0};//目的地址


		/*
		"CONFIG"section名
		"srcpath" 键名
		cSrcPath 存储变量
		".\\config.ini" 配置文件地址
		从配置文件中读取两个键值到变量中
		*/
		if (0 == GetPrivateProfileString("CONFIG","luoyang","",cLuoyangPath,sizeof(cLuoyangPath),".\\config.ini")||
			0 == GetPrivateProfileString("CONFIG","sanmenxia","",cSanmenxiaPath,sizeof(cSanmenxiaPath),".\\config.ini")||
			0 == GetPrivateProfileString("CONFIG","despath","",cDesPath,sizeof(cDesPath),".\\config.ini")
			)
		{
			printf("读取配置文件失败！\n");
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
			printf("检测时间：%s\n",printTime);

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

