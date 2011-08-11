#pragma once
#include "Inteligencia.h"
#include <deque>
#include "Updater.h"
#include "CommanderSIMi.h"

namespace Inteligencia {

	class UpdaterSIMi : public Updater {
		friend class CommanderSIMi;

	private:
		int _scene;

	public:
		UpdaterSIMi();//scena padrão 0
		UpdaterSIMi(int);
		~UpdaterSIMi();

		//methods:
		void receive();

	};
}