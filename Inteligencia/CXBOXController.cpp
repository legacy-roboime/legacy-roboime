#include "CXBOXController.h"

CXBOXController::CXBOXController(int playerNumber) {
    // Set the Controller Number
    _controllerNum = playerNumber - 1;
}

XINPUT_STATE CXBOXController::GetState() {
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(_controllerNum, &_controllerState);

    return _controllerState;
}

bool CXBOXController::IsConnected() {
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(_controllerNum, &_controllerState);

    if(Result == ERROR_SUCCESS) {
        return true;
    } else {
        return false;
    }
}

void CXBOXController::Vibrate(int leftVal, int rightVal) {
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(_controllerNum, &Vibration);
}

real CXBOXController::ThumbRX() {
	return ((real)GetState().Gamepad.sThumbRX)/32768.0;
}

real CXBOXController::ThumbRY() {
	return ((real)GetState().Gamepad.sThumbRY)/32768.0;
}

real CXBOXController::ThumbLX() {
	return ((real)GetState().Gamepad.sThumbLX)/32768.0;
}

real CXBOXController::ThumbLY() {
	return ((real)GetState().Gamepad.sThumbLY)/32768.0;
}

real CXBOXController::TriggerR() {
	return ((real)GetState().Gamepad.bRightTrigger)/255.0;
}

real CXBOXController::TriggerL() {
	return ((real)GetState().Gamepad.bLeftTrigger)/255.0;
}

bool CXBOXController::ButtonPressed(WORD w) {
	return (GetState().Gamepad.wButtons & w) != 0;
}