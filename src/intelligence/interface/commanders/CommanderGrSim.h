#pragma once
#ifndef COMMANDERGRSIM_H
#define COMMANDERGRSIM_H

#include "LibIntelligence.h"
#include "UdpServer.h"
#include "Commander.h"

#if defined(WIN32) && defined(_DEBUG)
	#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
	#define new DEBUG_NEW
#endif

namespace LibIntelligence
{
	class CommanderGrSim : public UdpServer, public Commander
	{
		Q_OBJECT
		
	public:
        CommanderGrSim(QObject* parent=0, const char* address="127.0.0.1", quint16 port=20011);

		void step();
	};
}

#endif // COMMANDERGRSIM_H
