#pragma once
#include "UDPClient.h"
namespace Inteligencia {

	class UDPClientIntSim : public UDPClient
	{
	public:
		UDPClientIntSim(void);
		~UDPClientIntSim(void);			//Parse the received string
	};

}