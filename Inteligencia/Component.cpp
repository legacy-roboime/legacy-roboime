#include "Component.h"

Component::Component() {
	_active = true;
	_working = true;
}

Component::Component(bool active, bool working) {
	_active = active;
	_working = working;
}

Component::~Component() {
}

bool Component::is_broken() {
	return _working;
}

bool Component::is_working() {
	return _working;
}

void Component::repair() {
	_working = true;
}

void Component::break_down() {
	_working = false;
}

bool Component::is_active() {
	return _active;
}

bool Component::is_inactive() {
	return !_active;
}

void Component::activate() {
	_active = true;
}

void Component::deactivate() {
	_active = false;
}
