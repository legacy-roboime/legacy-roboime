#pragma once
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
namespace Inteligencia {

	class Update {
		friend class Updater;//TODO: what's this for?

	private:
		//fields:
		int _timestamp;

	public:
		Update();//TODO: implement timestamping
		~Update();

		//methods:
		virtual void apply(Updater*) = 0;//apply an update through an updater
		int timestamp();

	};
}