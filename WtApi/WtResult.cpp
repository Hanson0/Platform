#include "Stdafx.h"
#include "WtResult.h"

using namespace AILinkFactoryAuto::Instrument::WtApi;

String^ WtResult::ToString()
{
	return String::Format("[AnaParamString={0}, Result={1}, Description={2}, Unit={3}]",
		this->AnaParamString,
		this->Result,
		this->Description,
		this->Unit);
}