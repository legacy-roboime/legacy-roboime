#pragma once
#include "Inteligencia.h"
#include "Play.h"

namespace Inteligencia {

	class PlayX : public Play {

		//protected:
	public:
		PlayX(void);//must always be called on the constructor

		//public:
		PlayX(char name[40]);
		PlayX(Stage stage);
		~PlayX(void);

		//methods:
		//TODO: add commonly used methods;

	};
}