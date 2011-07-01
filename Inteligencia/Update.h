#pragma once
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
namespace Inteligencia {

	class Update {
		friend class Updater;

	private:
	public:
		Update();
		~Update();
		virtual void apply(Updater*) = 0;
	};
}