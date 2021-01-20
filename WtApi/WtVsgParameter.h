#pragma once

#include "WtDemo.h"
#include "WtPort.h"
#include "WtSignal.h"

using namespace System;

namespace AILinkFactoryAuto {
	namespace Instrument {
		namespace WtApi {
			public ref class WtVsgParameter
			{
			public:
				double		Freq;               //VSG载波频率,单位：Hz
				double		Power;              //VSG功率,dBm
				WtPort		RfPort;             //指定VSG使用的RF端口

				WtSignal	WaveType;			//Wave类型，WT_SIGNAL_ENUM. SIG_USERFILE: 读取本地wave文件; SIG_TESTERFILE: 使用仪器存储的wave文件(WT-208固件版本低于或等于3.0.1.10的不支持该项); (其余选项（除SIG_USERFILE和SIG_TESTERFILE以外的选项）：仅WT-208仪器支持)
				String^		Wave;				//VSG数据文件,如果为null,只更新设备配置，不更新wave文件，不配置repeat和wave_gap
				int			Repeat;             //循环发送次数
				double		WaveGap;            //两次发送间隔，us

				int			TimeoutWaiting;     //在多连接情况下，等待的最大时间，默认值为8秒，单位sec

			public:
				virtual String^ ToString() override;
			};
		}
	}
}