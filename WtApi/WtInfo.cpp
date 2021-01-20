#include "Stdafx.h"
#include "WtInfo.h"

using namespace AILinkFactoryAuto::Instrument::WtApi;

String^ WtInfo::ToString()
{
	return String::Format("[ip={0}, SubMask={1}, GateAddr={2}, Sn={3}, Name={4}, MacAddr={5}, FwVersion={6}, HwVersion={7}, RfVersion={8}, CalDate={9}]", 
		this->Ip, 
		this->SubMask,
		this->GateAddr,
		this->Sn,
		this->Name,
		this->MacAddr,
		this->FwVersion,
		this->HwVersion,
		this->RfVersion,
		this->CalDate);
}