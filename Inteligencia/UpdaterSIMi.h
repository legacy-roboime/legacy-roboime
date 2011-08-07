#pragma once
#include <deque>
#include "Updater.h"
#include "CommanderSIMi.h"

using namespace std;
namespace Inteligencia {

	class UpdaterSIMi : public Updater {
		friend class CommanderSIMi;

	private:
		int _scene;

	public:
		UpdaterSIMi();//scena padr�o 0
		UpdaterSIMi(int);
		~UpdaterSIMi();

		//methods:
		void receive();

	};
}