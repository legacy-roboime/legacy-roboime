#pragma once
#include <list>
#include <string.h>
#include "Stage.h"
#include "Tactic.h"
using namespace std;
namespace Inteligencia {

	class Play {

	private:
		//static fields:
		static list<unsigned int> __i;//internal use for internal index

		//fields:
		unsigned int _i;

	protected:
		Play(void);//must always be called on the constructor

		//static fields:
		static Stage __stage;
		static list<Play*> _play;

		//fields:	
		Stage _stage;
		int _steps;
		bool _active;
		string _name;

		//methods:
		void _take_step();
		void _init();

	public:
		Play(string name);
		Play(Stage stage);
		~Play(void);

		//methods:
		void change_stage(Stage stage);
		void set_global_stage(void);
		void take_step(void);

	};
}