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
	int psduLen;                            //psdu����
	int psduType;                           //psdu����. PSDU_TYPE_ENUM
	int scrambler;                          //������
	int CRCCheckEnable;                     //CRCУ��
	int MacHeaderEnable;                    //MACͷʹ�ܣ�����psdu�Ƿ����MAC
	unsigned char FrameControl[4];          //����ģʽ-�û���. ʮ�����Ʊ�ʾ����2���ֽ�
	unsigned char DurationID[4];            //����ģʽ-�ӳ�. ʮ�����Ʊ�ʾ����2���ֽ�
	unsigned char SequenceControl[4];       //����ģʽ-����. ʮ�����Ʊ�ʾ����2���ֽ�
	unsigned char MacAddress1[12];          //Mac1.   ʮ�����Ʊ�ʾ����6���ֽ�
	unsigned char MacAddress2[12];          //Mac2.   ʮ�����Ʊ�ʾ����6���ֽ�
	unsigned char MacAddress3[12];          //Mac3.   ʮ�����Ʊ�ʾ����6���ֽ�
	unsigned char MacAddress4[12];          //Mac4.   ʮ�����Ʊ�ʾ����6���ֽ�
} PsduSettings;

typedef struct
{
	int dataRate11a;                        //11a�ź�����. DATARATE_11A_ENUM
} Set11A;

typedef struct
{
	int dataRate11b;                        //11b�ź�����. DATARATE_11B_ENUM
	int Preamble;                           //����ǰ��. ��ϸ���ݼ�enum PREAMBLE_TYPE
} Set11B;

typedef struct
{
	int mcs;                                //11n/11ac�ź�����
	int htFrmType;                          //11n  GF/MF. HT_FRAME_TYPE_ENUM
	int streamsCnt;                         //�ռ�������
	int soundingEnable;                     //����ʹ��
	int smoothingEnable;
	int isAggregation;                      //�Ƿ������ϣ�����psduǰ�������4�ֽڵ���Ϣ
	int isShortGI;                          //�Ƿ��GI
    int CodingType;                         //BCC/LDPC
} Set11N;

typedef struct
{
	int mcs;                                //11n/11ac�ź�����
	int streamsCnt;                         //�ռ�������
	int soundingEnable;                     //����ʹ��
	int isAggregation;                      //�Ƿ������ϣ�����psduǰ�������4�ֽڵ���Ϣ
	int isShortGI;                          //�Ƿ��GI
    int CodingType;                         //BCC/LDPC
} Set11AC;

typedef struct
{
    int PPDUFormat;                  // 11ax֡��ʽ SU MU Er_SU TB
    int StreamsCnt;                  //�ռ�������
    int Aggregation;                 //�Ƿ������ϣ�����psduǰ�������4�ֽڵ���Ϣ
    int UserNum;                     //MU�û�����
    int GILTFSize;                   //��������0~3
    int UL_DL;                       // 0:UL, 1:DL
	int PE;                          // 0/1
	int BeamChange;                  // 0/1
	int SpatialReuse[4];             // 4 bit, 0000~1111
	int SIGBMCS;
    int SIGBDCM;
    int SIGB_Compression;

    int CodingType[MAX_11AX_USER];   //BCC/LDPC
    int NSS[MAX_11AX_USER];          //�û�����
    int DataMcs[MAX_11AX_USER];      //�û�mcs
    int DCM[MAX_11AX_USER];          //�û�DCM

    int UserValidMap[MAX_11AX_USER]; //����common8bitȷ����Ru���û�ռ�����Map
    unsigned char RuAllocMap[8];     //common8bit
    unsigned char RuAllocExtra[2];   // 80M�м�26����
} Set11AX;

typedef struct
{
	int standard;                           //�źű�׼. WT_STANDARD_ENUM
	int bandwidth;                          //����, MHz (20:20M; 40:40M; 80:80M)
	int samplingRate;                       //��������, Hz
	int spatialExtension;                   //Spatial Extension, 1:Enable, 0:Disable

	Set11A PN11a;                           //��Ҫ����11a���ź�ʱ�����ø��������
	Set11B PN11b;                           //��Ҫ����11b���ź�ʱ�����ø��������
	Set11N PN11n;                           //��Ҫ����11n���ź�ʱ�����ø��������
	Set11AC PN11ac;                         //��Ҫ����11ac���ź�ʱ�����ø��������
	Set11AX PN11ax;                         //��Ҫ����11ax���ź�ʱ�����ø��������

	PsduSettings psduSet;                   //psdu������
	PsduSettings psduSet11ax[MAX_11AX_USER];//11ax psdu������
} PNSettingParameter;

//******************************************************************************
// Name:      WT_GetDefaultWaveParameter
// Func:      ��ȡĬ�ϵ��ź��������ò���,Ĭ������11a���ź�
// Path:      WT_GetDefaultWaveParameter
// Access:    public
// Returns:   int:
//               WT_ERR_CODE_OK: �����ɹ�
//               WT_ERR_CODE_UNKNOW_PARAMETER��������Ч
// Parameter: PNSettingParameter * pnParameters�������������ò���
//******************************************************************************
WT_PN_DLL_API int WT_GetDefaultWaveParameterV2(PNSettingParameter *pnParameters);

//******************************************************************************
// Name:      WT_MIMO_WaveGenerate
// Func:      ���������ò�����ƥ���Wave���ݣ���������ļ�
// Path:      WT_MIMO_WaveGenerate
// Access:    public
// Returns:   int (WT_ERR_CODE_ENUM)
//            WT_ERR_CODE_OK:�����ɹ�
//            WT_ERR_CODE_UNKNOW_PARAMETER: ����ָ��Ϊ�ջ���������
//            WT_ERR_CODE_PSDU_ERROR��psdu��������
//            WT_ERR_CODE_PSDU_CONVERT_FAIL: psdu�����е�MAC�������õĸ�ʽ����
//            WT_ERR_CODE_BANDWIDTH_ERROR: �������ô���
//            WT_ERR_CODE_SIGNALTYPE_ERROR: �ź�������������
//            WT_ERR_CODE_PARAMETER_MISMATCH: ��������������
//            WT_ERR_CODE_GENERATE_FAIL: �ź�����ʧ��
//            WT_ERR_CODE_GENERAL_ERROR: ������Ч
// Parameter: char * filePath��������ļ���������·����
// Parameter: PNSettingParameter * pnParameters�� �����������ò���
//******************************************************************************
WT_PN_DLL_API int WT_MIMO_WaveGenerateV2(char *filePath, PNSettingParameter *pnParameters);
#endif