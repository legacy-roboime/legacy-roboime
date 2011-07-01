#pragma once
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
namespace Inteligencia {

	class Update {
		friend class Updater;//TODO: what's this for?

	private:
	public:
		Update();
		~Update();
		virtual void apply(Updater*) = 0;//apply an update through an updater
	};
}