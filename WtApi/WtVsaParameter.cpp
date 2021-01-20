#include "Stdafx.h"
#include "WtVsaParameter.h"

using namespace AILinkFactoryAuto::Instrument::WtApi;

String^ WtVsaParameter::ToString()
{
	return String::Format("[Freq={0}, MaxPower={1}, SmpTime={2}, TrigType={3}, TrigLevel={4}, TrigTimeout={5}, TrigPretime={6}, Demod={7}, IqSwap={8}, PhCorr={9}, ChEstimate={10}, SymTimCorr={11}, FreqSync={12}, AmplTrack={13}, EvmMethod11b={14}, DcRemoval={15}, EqTaps={16}, CckPhCorr={17}, BtRate={18}, BtPacketType={19}, TimeoutWaiting={20}]",
		this->Freq,
		this->MaxPower,
		this->SmpTime,
		this->TrigType,
		this->TrigLevel,
		this->TrigTimeout,
		this->TrigPretime,
		this->Demod,
		this->IqSwap,
		this->PhCorr,
		this->ChEstimate,
		this->SymTimCorr,
		this->FreqSync,
		this->AmplTrack,
		this->EvmMethod11b,
		this->DcRemoval,
		this->EqTaps,
		this->CckPhCorr,
		this->BtRate,
		this->BtPacketType,
		this->TimeoutWaiting);
}