#pragma once
#include "Inteligencia.h"

namespace Inteligencia {

	class Component {
		friend class Robot;

	private:
		//fields:
		bool _active, _working;

	public:
		Component(void);
		Component(bool active, bool working);
		~Component(void);

		//methods:
		bool is_broken(void);//returns the value of _working
		bool is_working(void);//returns the value of !_working
		void repair(void);//sets _working true
		void break_down(void);//sets _working false
		bool is_active(void);//returns the value of _active
		bool is_inactive(void);//returns the value of !_active
		void activate(void);//sets _active true
		void deactivate(void);//sets _active false

	};
}