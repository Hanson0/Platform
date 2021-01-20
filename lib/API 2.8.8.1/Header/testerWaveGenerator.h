//******************************************************************************
//  Created:    2015/02/19   11:42
//  File base:  Tester Wave Generation
//  Copyright:  iTest
//  Version:
//
//  Purpose:    This header file defines the types and definitions used to
//              interface for Wave Generation.
//******************************************************************************

#ifndef __WT_PN_Generator_h__
#define __WT_PN_Generator_h__

#include "testerCommon.h"

#ifndef _Export
#ifdef _WIN32
#define _Export __declspec(dllexport)
#define _Import __declspec(dllimport)
#else
#define _Export
#define _Import
#endif
#endif

#ifdef WT_PN_GENERATOR_DLL_EXPORT

#define WT_PN_DLL_API extern _Export

#else

#ifdef WT_C
// Set this compile switch (WT_C) if running C (using plain export names).
#define WT_PN_DLL_API extern
#else
// Do not set this compile switch if running C++ (using decorated export names).
#define WT_PN_DLL_API extern "C" _Import
#endif

#endif

#define MAX_11AX_USER    74

typedef struct
{
	int psduLen;                            //psdu长度
	int psduType;                           //psdu类型. PSDU_TYPE_ENUM
	int scrambler;                          //加扰码
	int CRCCheckEnable;                     //CRC校验
	int MacHeaderEnable;                    //MAC头使能，决定psdu是否包含MAC
	unsigned char FrameControl[4];          //控制模式-用户项. 十六进制表示，共2个字节
	unsigned char DurationID[4];            //控制模式-延迟. 十六进制表示，共2个字节
	unsigned char SequenceControl[4];       //控制模式-序列. 十六进制表示，共2个字节
	unsigned char MacAddress1[12];          //Mac1.   十六进制表示，共6个字节
	unsigned char MacAddress2[12];          //Mac2.   十六进制表示，共6个字节
	unsigned char MacAddress3[12];          //Mac3.   十六进制表示，共6个字节
	unsigned char MacAddress4[12];          //Mac4.   十六进制表示，共6个字节
} PsduSettings;

typedef struct
{
	int dataRate11a;                        //11a信号类型. DATARATE_11A_ENUM
} Set11A;

typedef struct
{
	int dataRate11b;                        //11b信号类型. DATARATE_11B_ENUM
	int Preamble;                           //长短前导. 详细内容见enum PREAMBLE_TYPE
} Set11B;

typedef struct
{
	int mcs;                                //11n/11ac信号类型
	int htFrmType;                          //11n  GF/MF. HT_FRAME_TYPE_ENUM
	int streamsCnt;                         //空间流数量
	int soundingEnable;                     //加噪使能
	int smoothingEnable;
	int isAggregation;                      //是否开启集合，开启psdu前面会增加4字节的信息
	int isShortGI;                          //是否短GI
    int CodingType;                         //BCC/LDPC
} Set11N;

typedef struct
{
	int mcs;                                //11n/11ac信号类型
	int streamsCnt;                         //空间流数量
	int soundingEnable;                     //加噪使能
	int isAggregation;                      //是否开启集合，开启psdu前面会增加4字节的信息
	int isShortGI;                          //是否短GI
    int CodingType;                         //BCC/LDPC
} Set11AC;

typedef struct
{
    int PPDUFormat;                  // 11ax帧形式 SU MU Er_SU TB
    int StreamsCnt;                  //空间流数量
    int Aggregation;                 //是否开启集合，开启psdu前面会增加4字节的信息
    int UserNum;                     //MU用户个数
    int GILTFSize;                   //数据类型0~3
    int UL_DL;                       // 0:UL, 1:DL
	int PE;                          // 0/1
	int BeamChange;                  // 0/1
	int SpatialReuse[4];             // 4 bit, 0000~1111
	int SIGBMCS;
    int SIGBDCM;
    int SIGB_Compression;

    int CodingType[MAX_11AX_USER];   //BCC/LDPC
    int NSS[MAX_11AX_USER];          //用户流数
    int DataMcs[MAX_11AX_USER];      //用户mcs
    int DCM[MAX_11AX_USER];          //用户DCM

    int UserValidMap[MAX_11AX_USER]; //根据common8bit确定的Ru中用户占用情况Map
    unsigned char RuAllocMap[8];     //common8bit
    unsigned char RuAllocExtra[2];   // 80M中间26带宽
} Set11AX;

typedef struct
{
	int standard;                           //信号标准. WT_STANDARD_ENUM
	int bandwidth;                          //带宽, MHz (20:20M; 40:40M; 80:80M)
	int samplingRate;                       //采样速率, Hz
	int spatialExtension;                   //Spatial Extension, 1:Enable, 0:Disable

	Set11A PN11a;                           //需要生成11a的信号时，设置该项的内容
	Set11B PN11b;                           //需要生成11b的信号时，设置该项的内容
	Set11N PN11n;                           //需要生成11n的信号时，设置该项的内容
	Set11AC PN11ac;                         //需要生成11ac的信号时，设置该项的内容
	Set11AX PN11ax;                         //需要生成11ax的信号时，设置该项的内容

	PsduSettings psduSet;                   //psdu配置项
	PsduSettings psduSet11ax[MAX_11AX_USER];//11ax psdu配置项
} PNSettingParameter;

//******************************************************************************
// Name:      WT_GetDefaultWaveParameter
// Func:      获取默认的信号生成设置参数,默认生成11a的信号
// Path:      WT_GetDefaultWaveParameter
// Access:    public
// Returns:   int:
//               WT_ERR_CODE_OK: 操作成功
//               WT_ERR_CODE_UNKNOW_PARAMETER：参数无效
// Parameter: PNSettingParameter * pnParameters：波形生成配置参数
//******************************************************************************
WT_PN_DLL_API int WT_GetDefaultWaveParameterV2(PNSettingParameter *pnParameters);

//******************************************************************************
// Name:      WT_MIMO_WaveGenerate
// Func:      生成与配置参数相匹配的Wave数据，并保存成文件
// Path:      WT_MIMO_WaveGenerate
// Access:    public
// Returns:   int (WT_ERR_CODE_ENUM)
//            WT_ERR_CODE_OK:操作成功
//            WT_ERR_CODE_UNKNOW_PARAMETER: 参数指针为空或设置有误
//            WT_ERR_CODE_PSDU_ERROR：psdu设置有误
//            WT_ERR_CODE_PSDU_CONVERT_FAIL: psdu设置中的MAC部分配置的格式有误
//            WT_ERR_CODE_BANDWIDTH_ERROR: 带宽设置错误
//            WT_ERR_CODE_SIGNALTYPE_ERROR: 信号类型设置有误
//            WT_ERR_CODE_PARAMETER_MISMATCH: 流数量配置有误
//            WT_ERR_CODE_GENERATE_FAIL: 信号生成失败
//            WT_ERR_CODE_GENERAL_ERROR: 参数无效
// Parameter: char * filePath：保存的文件名（包含路径）
// Parameter: PNSettingParameter * pnParameters： 波形生成配置参数
//******************************************************************************
WT_PN_DLL_API int WT_MIMO_WaveGenerateV2(char *filePath, PNSettingParameter *pnParameters);
#endif