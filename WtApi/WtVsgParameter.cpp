#include "Stdafx.h"
#include "WtVsgParameter.h"

using namespace AILinkFactoryAuto::Instrument::WtApi;

String^ WtVsgParameter::ToString()
{
	return String::Format("[Freq={0}, Power={1}, RfPort={2}, WaveType={3}, Wave={4}, Repeat={5}, WaveGap={6}, TimeoutWaiting={7}]",
		this->Freq,
		this->Power,
		this->RfPort,
		this->WaveType,
		this->Wave,
		this->Repeat,
		this->WaveGap,
		this->TimeoutWaiting);
}