#include "NxKicker.h"

NxKicker::NxKicker(void)
{
	speedToExecute = 0;
}

NxKicker::~NxKicker(void)
{
	delete kickerShapeDesc;
}
