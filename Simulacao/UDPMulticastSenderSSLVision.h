#pragma once

#include "UDPMulticastSender.h"
#include "messages_robocup_ssl_refbox_log.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "Simulation.h"

class UDPMulticastSenderSSLVision : public UDPMulticastSender
{
public:
	UDPMulticastSenderSSLVision(void);
	~UDPMulticastSenderSSLVision(void);
	virtual void buildSendMessage();
};
