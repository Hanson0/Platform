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
				double		Freq;               //VSG�ز�Ƶ��,��λ��Hz
				double		Power;              //VSG����,dBm
				WtPort		RfPort;             //ָ��VSGʹ�õ�RF�˿�

				WtSignal	WaveType;			//Wave���ͣ�WT_SIGNAL_ENUM. SIG_USERFILE: ��ȡ����wave�ļ�; SIG_TESTERFILE: ʹ�������洢��wave�ļ�(WT-208�̼��汾���ڻ����3.0.1.10�Ĳ�֧�ָ���); (����ѡ���SIG_USERFILE��SIG_TESTERFILE�����ѡ�����WT-208����֧��)
				String^		Wave;				//VSG�����ļ�,���Ϊnull,ֻ�����豸���ã�������wave�ļ���������repeat��wave_gap
				int			Repeat;             //ѭ�����ʹ���
				double		WaveGap;            //���η��ͼ����us

				int			TimeoutWaiting;     //�ڶ���������£��ȴ������ʱ�䣬Ĭ��ֵΪ8�룬��λsec

			public:
				virtual String^ ToString() override;
			};
		}
	}
}