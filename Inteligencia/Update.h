#pragma once
#include "Inteligencia.h"
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "Updater.h"

namespace Inteligencia {

	class Update {
		friend class Updater;//do not remove this

	protected:
		//fields:
		float _confidence;
		double _time_received;
		double _time_sent;
		double _time_capture;

	public:
		Update(float confidene, double time_sent, double time_capture);
		Update();
		~Update();

		//methods:
		virtual void apply(Updater*) = 0;//apply an update through an updater
		double time_sent();
		double time_received();
		double time_capture();

	};
}