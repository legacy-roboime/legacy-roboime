#pragma once
#include "NxAllRobots.h"
#include "NxUserContactReport.h"

class MyContactReport : public NxUserContactReport
{
public:
	MyContactReport(void);
	~MyContactReport(void);
	virtual void  onContactNotify(NxContactPair& pair, NxU32 events);
}static robotContactReportObj;

static NxUserContactReport * robotContactReport = &robotContactReportObj;