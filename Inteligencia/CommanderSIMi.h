#pragma once
#include <deque>
#include "Commander.h"
#include "UpdaterSIMi.h"
#include "Simulation.h"

using namespace std;
namespace Inteligencia {

	class CommanderSIMi : public Commander {
		friend class UpdaterSIMi;

	private:
		int _scene;

	public:
		CommanderSIMi();
		CommanderSIMi(int);
		~CommanderSIMi();

		//methods:
		void send();

	};
}