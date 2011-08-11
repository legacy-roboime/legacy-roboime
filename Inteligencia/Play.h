#pragma once
#include "Inteligencia.h"
#include <list>
#include <string.h>
#include "Stage.h"
#include "Tactic.h"

using namespace std;

namespace Inteligencia {

	class Play {

	protected:
		Play(void);//must always be called on the constructor

		//fields:	
		Stage* _stage;
		Team* _team;
		bool _active;

		//methods:
		void _take_step();
		void _init();

	public:
		Play(Team*,Stage*);
		~Play(void);

		//methods:
		void stage(Stage*);
		void step(void);

	};
}