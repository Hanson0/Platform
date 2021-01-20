#pragma once

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {

			public enum class WtErrCode
			{
				WT_ERR_CODE_OK,
				WT_ERR_CODE_CONNECT_FAIL,            //连接失败、未建立或已中断
				WT_ERR_CODE_UNKNOW_PARAMETER,        //参数有误
				WT_ERR_CODE_OUT_OF_MEMORY,           //内存不足
				WT_ERR_CODE_NO_DATA_CAPTURED,        //未抓取数据
				WT_ERR_CODE_TIMEOUT,                 //超时
				WT_ERR_CODE_VsgInaccuracy,           //指定的VSG功率不准确
				WT_ERR_CODE_GENERAL_ERROR,           //其他错误

				WT_ERR_CODE_BANDWIDTH_ERROR,         //带宽设置错误
				WT_ERR_CODE_SIGNALTYPE_ERROR,        //信号类型错误
				WT_ERR_CODE_FRM_ERROR,               //11n帧类型错误
				WT_ERR_CODE_PARAMETER_MISMATCH,      //参数关联错误
				WT_ERR_CODE_PSDU_ERROR,              //PSDU设置错误
				WT_ERR_CODE_PSDU_CONVERT_FAIL,       //Mac格式错误
				WT_ERR_CODE_OUTDATA_INVALID,         //存放输出数据的指针错误
				WT_ERR_CODE_GENERATE_FAIL,           //生成信号失败

				WT_ERR_CODE_TESTER_NO_WAVE,          //仪器没有指定的波形文件
				WT_ERR_CODE_NO_LICENSE_SUPPORT,      //没有对应的license支持

				WT_ERR_CODE_TX_WAIT_RESOURCE_TIMEOUT, //TX申请硬件资源失败
				WT_ERR_CODE_RX_WAIT_RESOURCE_TIMEOUT, //RX申请硬件资源失败

				WT_ERR_CODE_AUTHEN_FAIL,              //认证失败

				WT_ERR_CODE_LAST
			};
		}
	}
}