#include "Inteligencia.h"
#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <XInput.h>

// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

class CXBOXController
{
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    CXBOXController(int playerNumber);
    XINPUT_STATE GetState();
	real ThumbRX();
	real ThumbRY();
	real ThumbLX();
	real ThumbLY();
	real TriggerR();
	real TriggerL();
	bool ButtonPressed(WORD buttons);
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};
#endif